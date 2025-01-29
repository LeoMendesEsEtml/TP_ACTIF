// Mc32Gest_RS232.C
// Canevas manipulatio TP2 RS232 SLO2 2017-18
// Fonctions d'�mission et de r�ception des message
// CHR 20.12.2016 ajout traitement int error
// CHR 22.12.2016 evolution des marquers observation int Usart
// SCA 03.01.2018 nettoy� r�ponse interrupt pour ne laisser que les 3 ifs

// ======= Inclusions des biblioth�ques standard et sp�cifiques au microcontr�leur =======
#include <xc.h>                // Biblioth�que sp�cifique au compilateur XC pour le PIC32
#include <sys/attribs.h>       // Gestion des attributs d'interruptions et de priorit�
#include <stdbool.h>           // D�finition du type bool�en standard (true/false)
#include <stdlib.h>            // Fonctions standards de gestion m�moire et conversion

// ======= Inclusions li�es � la configuration syst�me et aux d�finitions globales =======
#include "system_definitions.h" // D�finitions sp�cifiques au projet et configuration syst�me
#include <GenericTypeDefs.h>     // D�finitions de types g�n�riques pour le d�veloppement embarqu�

// ======= Inclusions des modules applicatifs sp�cifiques =======
#include "app.h"               // Fichier principal de l'application
#include "GesFifoTh32.h"       // Gestion des files FIFO pour le traitement des donn�es
#include "Mc32gest_RS232.h"    // Gestion de la communication s�rie RS232
#include "gestPWM.h"           // Gestion du signal PWM pour les moteurs et servomoteurs
#include "Mc32CalCrc16.h"      // Calcul de CRC16 pour validation des transmissions


/// ======= Structures pour la gestion des messages =======
// Structure pour l'�mission des messages
StruMess TxMess;

// Structure pour la r�ception des messages
StruMess RxMess;

// ======= FIFO de r�ception =======
int8_t fifoRX[FIFO_RX_SIZE];  // Buffer FIFO pour la r�ception des messages
S_fifo descrFifoRX;           // Descripteur du FIFO de r�ception

// ======= FIFO d'�mission =======
int8_t fifoTX[FIFO_TX_SIZE];  // Buffer FIFO pour l'�mission des messages
S_fifo descrFifoTX;           // Descripteur du FIFO d'�mission

/**
 * @brief Initialise les FIFO de communication et configure le signal RTS.
 * 
 * Cette fonction initialise :
 * - Le FIFO de r�ception avec son descripteur et son buffer associ�.
 * - Le FIFO d'�mission avec son descripteur et son buffer associ�.
 * - Le signal RTS pour interdire temporairement l'�mission par l'autre p�riph�rique.
 * 
 * @return void Aucune valeur de retour.
 */
void InitFifoComm(void) {
    // Initialisation du FIFO de r�ception
    InitFifo(&descrFifoRX, FIFO_RX_SIZE, fifoRX, 0);

    // Initialisation du FIFO d'�mission
    InitFifo(&descrFifoTX, FIFO_TX_SIZE, fifoTX, 0);

    // Initialisation du signal RTS
    RS232_RTS = 1; // Interdit l'�mission par l'autre p�riph�rique

} // Fin InitFifoComm

/**
 * @brief G�re la d�connexion du c�ble s�rie en r�initialisant les FIFO et le signal RTS.
 * 
 * Cette fonction effectue les actions suivantes :
 * - R�initialisation du FIFO de r�ception.
 * - R�initialisation du FIFO d'�mission.
 * - Configuration du signal RTS pour autoriser l'�mission du p�riph�rique distant.
 * 
 * @return void Aucune valeur de retour.
 */
void HandleCableDisconnection(void) {
    // R�initialisation du FIFO de r�ception
    ResetFifo(&descrFifoRX);

    // R�initialisation du FIFO d'�mission
    ResetFifo(&descrFifoTX);

    // Configuration du signal RTS pour autoriser l'�mission du p�riph�rique distant
    RS232_RTS = 0;

} // Fin HandleCableDisconnection


/**
 * @brief Traite la r�ception de messages et met � jour les donn�es si un message valide est re�u.
 * 
 * @param[in,out] pData Pointeur vers la structure contenant les param�tres de configuration PWM.
 * @return int Statut de la communication :
 *             - 0 : Pas de message re�u (local, donn�es non modifi�es).
 *             - 1 : Message re�u (remote, donn�es mises � jour).
 */
int GetMessage(S_pwmSettings *pData) {
    static bool wasCableConnected = true; // Indique si le c�ble �tait connect� pr�c�demment

    // Initialise le statut de la communication (local par d�faut)
    static int CommStatus = 0;

    // Compteur statique pour le nombre d'erreurs cons�cutives dans les messages
    static uint8_t NbMessError = 0;

    // Nombre de caract�res � lire depuis la FIFO RX
    static uint8_t NbCharToRead = 0;

    // Union pour le calcul et la validation du CRC
    U_manip16 Crc;

    // Initialise la valeur du CRC avec une constante pr�d�finie
    uint16_t CrcVal = CRCINIT;

    // Obtient le nombre de caract�res disponibles dans la FIFO RX
    NbCharToRead = GetReadSize(&descrFifoRX);
    // V�rifie si le nombre de caract�res disponibles correspond � un message complet
    if (NbCharToRead >= MESS_SIZE) {
        // Lit le premier caract�re de la FIFO et le stocke dans la structure RxMess
        GetCharFromFifo(&descrFifoRX, &RxMess.Start);

        // V�rifie si le caract�re re�u est un code de d�but valide
        if (RxMess.Start == STX_CODE) {
            // Lit le param�tre de vitesse depuis la FIFO RX
            GetCharFromFifo(&descrFifoRX, &RxMess.Speed);

            // Lit le param�tre d'angle depuis la FIFO RX
            GetCharFromFifo(&descrFifoRX, &RxMess.Angle);

            // Lit le MSB (octet sup�rieur) du CRC re�u depuis la FIFO RX
            GetCharFromFifo(&descrFifoRX, &RxMess.MsbCrc);

            // Stocke le MSB dans l'union Crc
            Crc.shl.Msb = RxMess.MsbCrc;

            // Lit le LSB (octet inf�rieur) du CRC re�u depuis la FIFO RX
            GetCharFromFifo(&descrFifoRX, &RxMess.LsbCrc);

            // Stocke le LSB dans l'union Crc
            Crc.shl.Lsb = RxMess.LsbCrc;

            // Met � jour le CRC calcul� avec le code de d�but
            CrcVal = updateCRC16(CrcVal, STX_CODE);

            // Met � jour le CRC calcul� avec la valeur de la vitesse
            CrcVal = updateCRC16(CrcVal, RxMess.Speed);

            // Met � jour le CRC calcul� avec la valeur de l'angle
            CrcVal = updateCRC16(CrcVal, RxMess.Angle);

            // Compare le CRC calcul� avec celui re�u
            if (Crc.Val == CrcVal) {
                // Met � jour la vitesse dans les param�tres PWM
                pData->SpeedSetting = RxMess.Speed;
                pData->absSpeed = abs(RxMess.Speed);

                // Met � jour l'angle dans les param�tres PWM
                pData->AngleSetting = RxMess.Angle;
                pData->absAngle = abs(RxMess.Angle - 90);

                // R�initialise le nombre de caract�res � lire
                NbCharToRead = 0;

                // R�initialise le compteur d'erreurs de message
                NbMessError = 0;
            } else {
                // Incr�mente le compteur d'erreurs de message
                NbMessError++;
                /* Indique que le CRC est faux */
                BSP_LEDToggle(BSP_LED_6);
            }
        }

    } else {
        NbMessError++;
    }



    // ---- D�tection de la perte de connexion ----
    if (NbMessError >= NBR_MESS_ERROR) {
        if (wasCableConnected) { // Si le c�ble vient d'�tre d�branch�
            //HandleCableDisconnection(); // Reset FIFO et stop RS232
            wasCableConnected = false; // Marque le c�ble comme d�branch�
        }
        CommStatus = LOCAL;
        if (NbMessError == 0xFF) {
            NbMessError = NBR_MESS_ERROR;
        }
    }        // ---- D�tection de la reconnexion ----
    else if (!wasCableConnected) { // Si les messages reviennent, le c�ble est reconnect�
        wasCableConnected = true; // Marque le c�ble comme connect�
        CommStatus = REMOTE;
    } else {
        CommStatus = REMOTE;
    }

    // V�rifie l'espace disponible dans la FIFO RX pour g�rer le contr�le de flux
    if (GetWriteSpace(&descrFifoRX) >= (2 * MESS_SIZE)) {
        // Active le signal RTS pour autoriser l'�mission par l'autre appareil
        RS232_RTS = 0;
    }

    // Retourne le statut de la communication
    return CommStatus;
}

/**
 * @brief Envoie un message contenant les param�tres PWM via une FIFO de transmission.
 *
 * @param[in] pData Pointeur vers la structure contenant les param�tres de configuration PWM.
 */
void SendMessage(S_pwmSettings *pData) {
    // Variable locale pour stocker la taille libre dans la FIFO de transmission
    int16_t FreeSize;

    // Initialisation de la valeur CRC avec une constante pr�d�finie
    uint16_t CrcVal = CRCINIT;

    // Union pour le calcul et la validation du CRC
    U_manip16 Crc;

    // Obtient l'espace libre disponible dans la FIFO TX
    FreeSize = GetWriteSpace(&descrFifoTX);

    // V�rifie si l'espace libre est suffisant pour un message complet
    if (FreeSize >= MESS_SIZE) {
        // Met � jour le CRC avec le code de d�marrage du message
        CrcVal = updateCRC16(CrcVal, STX_CODE);

        // Met � jour le CRC avec la valeur de la vitesse
        CrcVal = updateCRC16(CrcVal, pData->SpeedSetting);

        // Met � jour le CRC avec la valeur de l'angle
        CrcVal = updateCRC16(CrcVal, pData->AngleSetting);

        // Affecte le crc caculer � l'union local CRC
        Crc.Val = CrcVal;

        // Affecte le code de d�marrage dans la structure TxMess
        TxMess.Start = STX_CODE;

        // Affecte la vitesse dans la structure TxMess
        TxMess.Speed = pData->SpeedSetting;

        // Affecte l'angle dans la structure TxMess
        TxMess.Angle = pData->AngleSetting;

        // Affecte le MSB du CRC dans la structure TxMess
        TxMess.MsbCrc = Crc.shl.Msb;

        // Affecte le LSB du CRC dans la structure TxMess
        TxMess.LsbCrc = Crc.shl.Lsb;

        // D�pose le code de d�marrage dans la FIFO TX
        PutCharInFifo(&descrFifoTX, TxMess.Start);

        // D�pose la vitesse dans la FIFO TX
        PutCharInFifo(&descrFifoTX, TxMess.Speed);

        // D�pose l'angle dans la FIFO TX
        PutCharInFifo(&descrFifoTX, TxMess.Angle);

        // D�pose le MSB du CRC dans la FIFO TX
        PutCharInFifo(&descrFifoTX, TxMess.MsbCrc);

        // D�pose le LSB du CRC dans la FIFO TX
        PutCharInFifo(&descrFifoTX, TxMess.LsbCrc);
    }

    // Met � jour la taille libre disponible dans la FIFO TX
    FreeSize = GetWriteSpace(&descrFifoTX);

    if (GetReadSize(&descrFifoTX) > 0) {
        PLIB_INT_SourceEnable(INT_ID_0, INT_SOURCE_USART_1_TRANSMIT);
    }

}

/**
 * @brief Interruption pour la gestion de l'USART (RX, TX, erreurs).
 * 
 * @details Cette fonction g�re les interruptions li�es � l'USART 1.
 * Elle couvre :
 * 1. Le traitement des erreurs de r�ception.
 * 2. La r�ception des donn�es (FIFO hardware -> FIFO software).
 * 3. La transmission des donn�es (FIFO software -> FIFO hardware).
 */
void __ISR(_UART_1_VECTOR, ipl5AUTO) _IntHandlerDrvUsartInstance0(void) {
    // D�claration pour g�rer les erreurs USART
    USART_ERROR UsartStatus;
    uint8_t nDataBefore = GetReadSize(&descrFifoTX);
    uint8_t nDataAfter = nDataBefore;
    bool hwFull = false;
    bool sentSomething = false;
    static int8_t CharUsartToFifo; // Donn�e re�ue depuis le UART � transf�rer dans la FIFO


    // Allume LED3 pour indiquer le d�but de l'interruption
    LED3_W = 1;

    // 1. Gestion des erreurs UART
    if (PLIB_INT_SourceFlagGet(INT_ID_0, INT_SOURCE_USART_1_ERROR) &&
            PLIB_INT_SourceIsEnabled(INT_ID_0, INT_SOURCE_USART_1_ERROR)) {
        // Efface le drapeau d'interruption d'erreur
        PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_USART_1_ERROR);

        // Vidange le buffer hardware pour supprimer les erreurs restantes
        while (PLIB_USART_ReceiverDataIsAvailable(USART_ID_1)) {
            PLIB_USART_ReceiverByteReceive(USART_ID_1);
        }
    }

    // 2. Gestion des donn�es RX (r�ception)
    if (PLIB_INT_SourceFlagGet(INT_ID_0, INT_SOURCE_USART_1_RECEIVE) &&
            PLIB_INT_SourceIsEnabled(INT_ID_0, INT_SOURCE_USART_1_RECEIVE)) {

        // V�rifie s'il y a des erreurs de r�ception (parit�, framing, overrun)
        UsartStatus = PLIB_USART_ErrorsGet(USART_ID_1);

        if ((UsartStatus & (USART_ERROR_PARITY | USART_ERROR_FRAMING | USART_ERROR_RECEIVER_OVERRUN)) == 0) {
            // Lecture des donn�es tant qu'elles sont disponibles dans le buffer hardware RX
            while (PLIB_USART_ReceiverDataIsAvailable(USART_ID_1)) {
                // R�cup�re un caract�re du buffer hardware
                CharUsartToFifo = PLIB_USART_ReceiverByteReceive(USART_ID_1);
                // Ajoute ce caract�re dans la FIFO software RX
                PutCharInFifo(&descrFifoRX, CharUsartToFifo);
            }

            // --- Flow control update: if we have plenty of space, allow more data ---
            if (GetWriteSpace(&descrFifoRX) >= 2 * MESS_SIZE) {
                RS232_RTS = 0; // Enough space, let the other side send
            } else {
                RS232_RTS = 1; // Getting full, block the other side
            }
            LED4_W = !LED4_R; // Toggle Led4
            // Efface le drapeau d'interruption RX (plus de donn�es � lire)
            PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_USART_1_RECEIVE);
        }
        else {
            // Suppression des erreurs sp�cifiques (notamment overrun)
            if ((UsartStatus & USART_ERROR_RECEIVER_OVERRUN) == USART_ERROR_RECEIVER_OVERRUN) {
                PLIB_USART_ReceiverOverrunErrorClear(USART_ID_1);
            }
        }
    }

    if (PLIB_INT_SourceFlagGet(INT_ID_0, INT_SOURCE_USART_1_TRANSMIT) &&
            PLIB_INT_SourceIsEnabled(INT_ID_0, INT_SOURCE_USART_1_TRANSMIT)) {

        // While there's data AND CTS=0 AND hardware TX buffer not full
        while ((nDataAfter > 0) && (RS232_CTS == 0) && !hwFull) {
            int8_t toSend;
            GetCharFromFifo(&descrFifoTX, &toSend);
            PLIB_USART_TransmitterByteSend(USART_ID_1, toSend);

            nDataAfter = GetReadSize(&descrFifoTX);
            hwFull = PLIB_USART_TransmitterBufferIsFull(USART_ID_1);
            sentSomething = true;
        }

        // If we are completely out of data, disable TX interrupt
        if (nDataAfter == 0) {
            // No more data to send
            PLIB_INT_SourceDisable(INT_ID_0, INT_SOURCE_USART_1_TRANSMIT);
        } else if (!sentSomething) {
            // We have data, but we couldn't send any because CTS=1 or something else.
            // If we stay enabled, hardware remains "empty" => infinite interrupts.
            // So we disable for now:
            PLIB_INT_SourceDisable(INT_ID_0, INT_SOURCE_USART_1_TRANSMIT);
            // Then, in your main code or on a CTS pin change, re-enable when possible.
        }
        LED5_W = !LED5_R; // Toggle Led5
        // Clear the TX interrupt flag
        PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_USART_1_TRANSMIT);
    }
    // �teint LED3 pour indiquer la fin de l'interruption
    LED3_W = 0;
}