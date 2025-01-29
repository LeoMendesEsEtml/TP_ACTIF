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
 * Cette fonction effectue les actions suivantes :
 * - Initialise le FIFO de r�ception avec son descripteur et son buffer d�di� pour stocker les donn�es entrantes.
 * - Initialise le FIFO d'�mission avec son descripteur et son buffer d�di� pour stocker les donn�es � envoyer.
 * - Configure le signal RTS (Request to Send) � l'�tat **haut** pour bloquer temporairement l'�mission du p�riph�rique distant.
 * 
 * @return void Aucune valeur de retour.
 */
void InitFifoComm(void) {
    // Initialise le FIFO de r�ception pour stocker les messages entrants
    InitFifo(&descrFifoRX, FIFO_RX_SIZE, fifoRX, 0);

    // Initialise le FIFO d'�mission pour stocker les messages � transmettre
    InitFifo(&descrFifoTX, FIFO_TX_SIZE, fifoTX, 0);

    // Place RTS � 1 pour interdire temporairement l'envoi par le p�riph�rique distant
    RS232_RTS = 1;
} // Fin de InitFifoComm


/**
 * @brief R�initialise l'�tat de la communication s�rie apr�s une d�connexion.
 * 
 * Cette fonction effectue les actions suivantes :
 * - Vide le FIFO de r�ception pour �viter les donn�es corrompues apr�s la perte de connexion.
 * - Vide le FIFO d'�mission pour �viter l'envoi de messages obsol�tes.
 * - Abaisse le signal RTS afin d'indiquer au p�riph�rique distant qu'il peut �mettre de nouvelles donn�es.
 * 
 * @return void Aucune valeur de retour.
 */
void HandleCableDisconnection(void) {
    // R�initialise le FIFO de r�ception pour �viter toute donn�e r�siduelle erron�e
    ResetFifo(&descrFifoRX);

    // R�initialise le FIFO d'�mission pour �viter l'envoi de donn�es obsol�tes
    ResetFifo(&descrFifoTX);

    // Abaisse le signal RTS (Request to Send) pour permettre au p�riph�rique distant d'envoyer des messages
    RS232_RTS = 0;
} // Fin de HandleCableDisconnection




/**
 * @brief Traite la r�ception de messages et met � jour les donn�es si un message valide est re�u.
 * 
 * @param[in,out] pData Pointeur vers la structure contenant les param�tres de configuration PWM.
 * @return int Statut de la communication :
 *             - 0 : Aucun message valide re�u (mode local activ�).
 *             - 1 : Message valide re�u (mode distant activ�).
 */
int GetMessage(S_pwmSettings *pData) {
    static bool wasCableConnected = true; // Indique si le c�ble �tait connect� lors du dernier appel

    static int CommStatus = 0; // Initialise le statut de la communication � LOCAL

    static uint8_t NbMessError = 0; // Initialise le compteur d'erreurs de r�ception

    static uint8_t NbCharToRead = 0; // Initialise le nombre de caract�res � lire dans le FIFO RX

    U_manip16 Crc; // D�clare une union pour stocker le CRC

    uint16_t CrcVal = CRCINIT; // Initialise la valeur du CRC avec la valeur pr�d�finie

    NbCharToRead = GetReadSize(&descrFifoRX); // V�rifie combien de caract�res sont disponibles dans le FIFO RX

    if (NbCharToRead >= MESS_SIZE) { // V�rifie si un message complet est disponible
        GetCharFromFifo(&descrFifoRX, &RxMess.Start); // R�cup�re le premier caract�re du message

        if (RxMess.Start == STX_CODE) { // V�rifie si le message commence bien par l'identifiant attendu
            GetCharFromFifo(&descrFifoRX, &RxMess.Speed); // R�cup�re la vitesse du message

            GetCharFromFifo(&descrFifoRX, &RxMess.Angle); // R�cup�re l'angle du message

            GetCharFromFifo(&descrFifoRX, &RxMess.MsbCrc); // R�cup�re le MSB du CRC

            Crc.shl.Msb = RxMess.MsbCrc; // Stocke le MSB du CRC dans la structure

            GetCharFromFifo(&descrFifoRX, &RxMess.LsbCrc); // R�cup�re le LSB du CRC

            Crc.shl.Lsb = RxMess.LsbCrc; // Stocke le LSB du CRC dans la structure

            CrcVal = updateCRC16(CrcVal, STX_CODE); // Met � jour le CRC avec le code de d�but

            CrcVal = updateCRC16(CrcVal, RxMess.Speed); // Met � jour le CRC avec la vitesse

            CrcVal = updateCRC16(CrcVal, RxMess.Angle); // Met � jour le CRC avec l'angle

            if (Crc.Val == CrcVal) { // V�rifie si le CRC calcul� correspond au CRC re�u
                pData->SpeedSetting = RxMess.Speed; // Met � jour la vitesse du PWM

                pData->absSpeed = abs(RxMess.Speed); // Met � jour la vitesse absolue

                pData->AngleSetting = RxMess.Angle; // Met � jour l'angle du PWM

                pData->absAngle = abs(RxMess.Angle - 90); // Met � jour l'angle absolu en appliquant un d�calage

                NbCharToRead = 0; // R�initialise le nombre de caract�res � lire

                NbMessError = 0; // R�initialise le compteur d'erreurs
            } else { // Si le CRC est invalide
                NbMessError++; // Incr�mente le compteur d'erreurs

                BSP_LEDToggle(BSP_LED_6); // Bascule la LED 6 pour indiquer une erreur CRC
            }
        }
    } else { // Si un message complet n'est pas disponible
        NbMessError++; // Incr�mente le compteur d'erreurs
    }

    if (NbMessError >= NBR_MESS_ERROR) { // V�rifie si le nombre d'erreurs atteint la limite
        if (wasCableConnected) { // V�rifie si le c�ble �tait pr�c�demment connect�
            //HandleCableDisconnection(); // R�initialise les FIFO et arr�te le RS232

            wasCableConnected = false; // Marque le c�ble comme d�connect�
        }

        CommStatus = LOCAL; // Passe en mode local

        if (NbMessError == 0xFF) { // V�rifie si le compteur d'erreurs atteint sa valeur maximale
            NbMessError = NBR_MESS_ERROR; // R�initialise � la valeur limite pour �viter un d�passement
        }
    } else if (!wasCableConnected) { // V�rifie si le c�ble a �t� reconnect� apr�s une perte de connexion
        wasCableConnected = true; // Marque le c�ble comme reconnect�

        CommStatus = REMOTE; // Passe en mode distant
    } else { // Si aucune erreur critique n'a �t� d�tect�e
        CommStatus = REMOTE; // Reste en mode distant
    }

    if (GetWriteSpace(&descrFifoRX) >= (2 * MESS_SIZE)) { // V�rifie l'espace disponible dans la FIFO RX
        RS232_RTS = 0; // Active le signal RTS pour autoriser l'�mission du p�riph�rique distant
    }

    return CommStatus; // Retourne le statut de la communication
}

/**
 * @brief Envoie un message contenant les param�tres PWM via une FIFO de transmission.
 *
 * @param[in] pData Pointeur vers la structure contenant les param�tres de configuration PWM.
 */
void SendMessage(S_pwmSettings *pData) {
    int16_t FreeSize; // Variable locale pour stocker la taille libre dans la FIFO de transmission

    uint16_t CrcVal = CRCINIT; // Initialise le CRC avec la valeur par d�faut d�finie pour le protocole

    U_manip16 Crc; // Union permettant de manipuler le CRC sous forme d'octets s�par�s

    FreeSize = GetWriteSpace(&descrFifoTX); // V�rifie l'espace libre disponible dans la FIFO TX

    if (FreeSize >= MESS_SIZE) { // V�rifie si un message complet peut �tre stock� dans la FIFO
        CrcVal = updateCRC16(CrcVal, STX_CODE); // Ajoute le code de d�but au calcul du CRC
        CrcVal = updateCRC16(CrcVal, pData->SpeedSetting); // Ajoute la vitesse au calcul du CRC
        CrcVal = updateCRC16(CrcVal, pData->AngleSetting); // Ajoute l'angle au calcul du CRC

        Crc.Val = CrcVal; // Stocke le CRC calcul� dans l'union pour une manipulation plus simple

        TxMess.Start = STX_CODE; // Initialise l'identifiant de d�but du message
        TxMess.Speed = pData->SpeedSetting; // Stocke la vitesse actuelle dans le message
        TxMess.Angle = pData->AngleSetting; // Stocke l'angle actuel dans le message
        TxMess.MsbCrc = Crc.shl.Msb; // Stocke le MSB du CRC dans la structure du message
        TxMess.LsbCrc = Crc.shl.Lsb; // Stocke le LSB du CRC dans la structure du message

        PutCharInFifo(&descrFifoTX, TxMess.Start); // Ajoute le code de d�but du message dans la FIFO TX
        PutCharInFifo(&descrFifoTX, TxMess.Speed); // Ajoute la vitesse dans la FIFO TX
        PutCharInFifo(&descrFifoTX, TxMess.Angle); // Ajoute l'angle dans la FIFO TX
        PutCharInFifo(&descrFifoTX, TxMess.MsbCrc); // Ajoute l'octet MSB du CRC dans la FIFO TX
        PutCharInFifo(&descrFifoTX, TxMess.LsbCrc); // Ajoute l'octet LSB du CRC dans la FIFO TX
    }

    FreeSize = GetWriteSpace(&descrFifoTX); // Met � jour l'espace libre disponible apr�s l'insertion

    if (GetReadSize(&descrFifoTX) > 0) { // V�rifie s'il y a des donn�es � transmettre
        PLIB_INT_SourceEnable(INT_ID_0, INT_SOURCE_USART_1_TRANSMIT); // Active l'interruption TX pour envoyer les donn�es
    }
}


/**
 * @brief Gestion des interruptions de l'USART (RX, TX, erreurs).
 * 
 * @details Cette fonction g�re les �v�nements li�s � l'USART 1 :
 * - Traitement des erreurs de r�ception.
 * - R�ception des donn�es (FIFO hardware -> FIFO software).
 * - Transmission des donn�es (FIFO software -> FIFO hardware).
 */
void __ISR(_UART_1_VECTOR, ipl5AUTO) _IntHandlerDrvUsartInstance0(void) {
    USART_ERROR usartErrorStatus; // Stocke le statut des erreurs USART
    uint8_t txFifoDataCountBefore = GetReadSize(&descrFifoTX); // Nombre de donn�es TX avant transmission
    uint8_t txFifoDataCountAfter = txFifoDataCountBefore; // Suivi du nombre de donn�es TX apr�s transmission
    bool isTxHardwareBufferFull = false; // Indique si le buffer TX mat�riel est plein
    bool hasSentData = false; // Indique si au moins une donn�e a �t� envoy�e
    static int8_t receivedUartChar; // Stocke le dernier caract�re re�u de l'USART

    LED3_W = 1; // Allume la LED3 pour indiquer qu'une interruption est en cours

    // ==== 1. Gestion des erreurs USART ====
    if (PLIB_INT_SourceFlagGet(INT_ID_0, INT_SOURCE_USART_1_ERROR) &&
        PLIB_INT_SourceIsEnabled(INT_ID_0, INT_SOURCE_USART_1_ERROR)) {
        
        PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_USART_1_ERROR); // Efface le drapeau d'erreur

        // Vidange le buffer RX hardware pour �viter les erreurs r�siduelles
        while (PLIB_USART_ReceiverDataIsAvailable(USART_ID_1)) {
            PLIB_USART_ReceiverByteReceive(USART_ID_1);
        }
    }

    // ==== 2. Gestion de la r�ception des donn�es RX ====
    if (PLIB_INT_SourceFlagGet(INT_ID_0, INT_SOURCE_USART_1_RECEIVE) &&
        PLIB_INT_SourceIsEnabled(INT_ID_0, INT_SOURCE_USART_1_RECEIVE)) {

        usartErrorStatus = PLIB_USART_ErrorsGet(USART_ID_1); // R�cup�ration du statut d'erreur

        // V�rifie si aucune erreur de r�ception n'est d�tect�e
        if (!(usartErrorStatus & (USART_ERROR_PARITY | USART_ERROR_FRAMING | USART_ERROR_RECEIVER_OVERRUN))) {
            // Lire les donn�es du buffer RX tant qu'il y en a
            while (PLIB_USART_ReceiverDataIsAvailable(USART_ID_1)) {
                receivedUartChar = PLIB_USART_ReceiverByteReceive(USART_ID_1); // R�cup�re une donn�e du buffer RX
                PutCharInFifo(&descrFifoRX, receivedUartChar); // Stocke la donn�e dans la FIFO RX
            }

            // Mise � jour du contr�le de flux RTS en fonction de la place restante dans la FIFO RX
            if (GetWriteSpace(&descrFifoRX) >= 2 * MESS_SIZE) {
                RS232_RTS = 0; // Il y a assez d'espace, on autorise l'envoi depuis l'autre p�riph�rique
            } else {
                RS232_RTS = 1; // FIFO RX proche de la saturation, on bloque l'�mission du p�riph�rique distant
            }

            LED4_W = !LED4_R; // Toggle LED4 pour indiquer une r�ception
            PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_USART_1_RECEIVE); // Efface le drapeau RX
        }
        else {
            // Gestion sp�cifique de l'erreur d'overrun si d�tect�e
            if (usartErrorStatus & USART_ERROR_RECEIVER_OVERRUN) {
                PLIB_USART_ReceiverOverrunErrorClear(USART_ID_1);
            }
        }
    }

    // ==== 3. Gestion de la transmission des donn�es TX ====
    if (PLIB_INT_SourceFlagGet(INT_ID_0, INT_SOURCE_USART_1_TRANSMIT) &&
        PLIB_INT_SourceIsEnabled(INT_ID_0, INT_SOURCE_USART_1_TRANSMIT)) {

        // Envoi des donn�es tant que :
        // - Il reste des donn�es � transmettre
        // - Le signal CTS permet la transmission
        // - Le buffer TX mat�riel n'est pas satur�
        while ((txFifoDataCountAfter > 0) && (RS232_CTS == 0) && !isTxHardwareBufferFull) {
            int8_t dataToSend; // Stocke la donn�e � envoyer
            GetCharFromFifo(&descrFifoTX, &dataToSend); // R�cup�re une donn�e de la FIFO TX
            PLIB_USART_TransmitterByteSend(USART_ID_1, dataToSend); // Envoie la donn�e via l'USART

            txFifoDataCountAfter = GetReadSize(&descrFifoTX); // Met � jour le nombre de donn�es restantes
            isTxHardwareBufferFull = PLIB_USART_TransmitterBufferIsFull(USART_ID_1); // V�rifie si le buffer TX est plein
            hasSentData = true; // Confirme qu'une donn�e a �t� envoy�e
        }

        // Si plus aucune donn�e n'est disponible, on d�sactive l'interruption TX
        if (txFifoDataCountAfter == 0) {
            PLIB_INT_SourceDisable(INT_ID_0, INT_SOURCE_USART_1_TRANSMIT);
        } 
        else if (!hasSentData) { 
            // Si des donn�es sont en attente mais n'ont pas pu �tre envoy�es (CTS=1)
            // => D�sactivation temporaire de l'interruption TX pour �viter des interruptions inutiles
            PLIB_INT_SourceDisable(INT_ID_0, INT_SOURCE_USART_1_TRANSMIT);
        }

        LED5_W = !LED5_R; // Toggle LED5 pour indiquer une transmission
        PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_USART_1_TRANSMIT); // Efface le drapeau TX
    }

    LED3_W = 0; // �teint la LED3 pour indiquer la fin de l'interruption
}
