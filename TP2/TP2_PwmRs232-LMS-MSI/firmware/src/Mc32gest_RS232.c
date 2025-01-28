// Mc32Gest_RS232.C
// Canevas manipulatio TP2 RS232 SLO2 2017-18
// Fonctions d'�mission et de r�ception des message
// CHR 20.12.2016 ajout traitement int error
// CHR 22.12.2016 evolution des marquers observation int Usart
// SCA 03.01.2018 nettoy� r�ponse interrupt pour ne laisser que les 3 ifs

// Biblioth�ques standards
#include <stdlib.h>       // Fonctions utilitaires g�n�rales (e.g., abs).
#include <stdbool.h>      // Types bool�ens (true/false).

// Biblioth�ques sp�cifiques au microcontr�leur
#include <xc.h>           // Gestion des registres sp�cifiques au microcontr�leur.
#include <sys/attribs.h>  // Gestion des niveaux de priorit� des interruptions.

// D�finitions sp�cifiques au syst�me
#include "system_definitions.h" // D�finitions mat�rielles et syst�mes.
#include <GenericTypeDefs.h>    // D�finitions g�n�riques des types.

// Fichiers sp�cifiques au projet
#include "app.h"               // D�clarations des fonctions applicatives.
#include "GesFifoTh32.h"       // Gestion des buffers FIFO.
#include "Mc32gest_RS232.h"    // Fonctions sp�cifiques � la communication RS232.
#include "gestPWM.h"           // Gestion des signaux PWM.
#include "Mc32CalCrc16.h"      // Calculs CRC pour la v�rification des donn�es.

// Struct pour �mission des messages
StruMess TxMess; // D�claration d'une structure pour g�rer les messages � transmettre.
// Struct pour r�ception des messages
StruMess RxMess; // D�claration d'une structure pour les messages re�us.

int8_t fifoRX[FIFO_RX_SIZE]; // Buffer circulaire pour stocker les donn�es re�ues (FIFO RX).
// D�claration du descripteur du FIFO de r�ception
S_fifo descrFifoRX; // Structure pour d�crire les param�tres du FIFO RX.

int8_t fifoTX[FIFO_TX_SIZE]; // Buffer circulaire pour stocker les donn�es � transmettre (FIFO TX).
// D�claration du descripteur du FIFO d'�mission
S_fifo descrFifoTX; // Structure pour d�crire les param�tres du FIFO TX.

/**
 * @brief Initialise les buffers FIFO et configure le signal RTS.
 * 
 * @details Cette fonction initialise les descripteurs des buffers FIFO pour la 
 *          r�ception et l'�mission de donn�es s�rie. Elle configure �galement
 *          le signal RTS pour bloquer temporairement l'�mission externe.
 * 
 * @param[in] void Aucun param�tre requis.
 * 
 * @return void Aucun retour. La fonction met � jour les structures globales.
 */
void InitFifoComm(void)
{
    // Initialise le FIFO RX avec la taille et le buffer associ�s
    InitFifo(&descrFifoRX, FIFO_RX_SIZE, fifoRX, 0);

    // Initialise le FIFO TX avec la taille et le buffer associ�s
    InitFifo(&descrFifoTX, FIFO_TX_SIZE, fifoTX, 0);

    // Configure le signal RTS pour bloquer temporairement l'�mission externe
    RS232_RTS = 1;
}

/**
 * @brief Vide les buffers FIFO RX et TX et d�sactive l'�mission externe.
 * 
 * @details Cette fonction nettoie les donn�es r�siduelles dans les buffers FIFO de r�ception (RX)
 *          et d'�mission (TX). Elle configure �galement le signal RTS pour bloquer
 *          temporairement l'�mission de l'autre appareil.
 * 
 * @param[in] void Aucun param�tre requis.
 * 
 * @return void Aucun retour. Les buffers FIFO sont nettoy�s et l'�mission est bloqu�e.
 */
/**
 * @brief Vide les FIFO RX/TX et d�sactive l'�mission externe lors du d�branchement du c�ble.
 * @details Cette fonction est appel�e une seule fois lorsqu?un �v�nement de d�branchement
 *          du c�ble est d�tect�. Elle ne perturbe pas les donn�es en local.
 */
void HandleCableDisconnection(void) {
    // R�initialiser les FIFO RX et TX
    ResetFifo(&descrFifoRX);
    ResetFifo(&descrFifoTX);

    // D�sactiver l'�mission externe
    RS232_RTS = 1; // Bloque la r�ception par l'autre appareil

    // Indication visuelle ou autre, si n�cessaire
    BSP_LEDOff(BSP_LED_6); // �teindre LED de communication
}
/**
 * @brief Traite la r�ception des messages et met � jour les param�tres PWM si un message valide est re�u.
 * 
 * @details Cette fonction lit les donn�es depuis la FIFO RX, v�rifie l'int�grit� du message via un calcul CRC
 *          et met � jour les param�tres PWM si le message est valide. En cas d'erreurs r�p�t�es, elle vide
 *          les buffers et bascule en mode local.
 * 
 * @param[in,out] pData Pointeur vers la structure contenant les param�tres de configuration PWM.
 * 
 * @return int Statut de la communication :
 *             - LOCAL (0) : Pas de message re�u ou trop d'erreurs.
 *             - REMOTE (1) : Message re�u et valid�, donn�es mises � jour.
 */
int GetMessage(S_pwmSettings *pData)
{
    static int CommStatus = LOCAL;      // Statut de la communication (LOCAL ou REMOTE).
    static uint8_t NbMessError = 10;   // Compteur d'erreurs cons�cutives.
    uint8_t NbCharToRead = 0;          // Nombre de caract�res disponibles dans le FIFO RX.
    U_manip16 Crc;                     // Union pour le calcul et la validation du CRC.
    uint16_t CrcVal = CRCINIT;         // Initialisation du CRC avec une valeur pr�d�finie.
    static bool wasCableConnected = true; // Indique si le c�ble �tait connect� pr�c�demment
    static bool disconnectionHandled = false; // Indique si la d�connexion a d�j� �t� g�r�e

    // Obtient le nombre de caract�res disponibles dans le FIFO RX
    NbCharToRead = GetReadSize(&descrFifoRX);

    // V�rifie si le FIFO contient suffisamment de caract�res pour un message complet
    if (NbCharToRead >= MESS_SIZE) 
    {
        // Lit le premier caract�re (code de d�but) dans la structure RxMess
        GetCharFromFifo(&descrFifoRX, &RxMess.Start);

        // V�rifie si le code de d�but est valide
        if (RxMess.Start == STX_CODE) 
        {
            // Lit les donn�es du message : vitesse, angle et CRC
            GetCharFromFifo(&descrFifoRX, &RxMess.Speed);
            GetCharFromFifo(&descrFifoRX, &RxMess.Angle);
            GetCharFromFifo(&descrFifoRX, &RxMess.MsbCrc);
            GetCharFromFifo(&descrFifoRX, &RxMess.LsbCrc);

            // Stocke les valeurs CRC dans l'union
            Crc.shl.Msb = RxMess.MsbCrc;
            Crc.shl.Lsb = RxMess.LsbCrc;

            // Met � jour le CRC calcul� avec les donn�es du message
            CrcVal = updateCRC16(CrcVal, STX_CODE);
            CrcVal = updateCRC16(CrcVal, RxMess.Speed);
            CrcVal = updateCRC16(CrcVal, RxMess.Angle);

            // Compare le CRC calcul� avec celui re�u
            if (Crc.Val == CrcVal) 
            {
                // Mise � jour des param�tres PWM avec les valeurs du message
                pData->SpeedSetting = RxMess.Speed;
                pData->absSpeed = abs(RxMess.Speed);
                pData->AngleSetting = RxMess.Angle;
                pData->absAngle = abs(RxMess.Angle);

                // R�initialise le compteur d'erreurs
                NbMessError = 0;

                // Allume une LED pour indiquer un message valide
                BSP_LEDOn(BSP_LED_6);
            } 
            else 
            {
                // Incr�mente le compteur d'erreurs et �teint la LED pour signaler une erreur CRC
                NbMessError++;
                BSP_LEDOff(BSP_LED_6);
            }
        } 
        else 
        {
            // Incr�mente le compteur d'erreurs si le code de d�but est incorrect
            NbMessError++;
        }
    } 
    else 
    {
        // Incr�mente le compteur d'erreurs si le message est incomplet
        NbMessError++;
    }

    // D�tection de d�connexion (si trop d'erreurs)
    if (NbMessError >= NBR_MESS_ERROR) {
        if (!disconnectionHandled) {
            HandleCableDisconnection(); // Appel� une seule fois
            disconnectionHandled = true; // Marque la d�connexion comme g�r�e
        }
        wasCableConnected = false; // Marque le c�ble comme d�branch�
        CommStatus = LOCAL;        // Passe en mode local
    } else {
        // R�initialise les flags si la connexion revient
        if (!wasCableConnected) {
            wasCableConnected = true;      // Marque le c�ble comme reconnect�
            disconnectionHandled = false; // R�initialise la gestion de d�connexion
        }
        CommStatus = REMOTE; // Continue en mode distant
    }
    
    // Gestion du contr�le de flux en fonction de l'espace disponible dans le FIFO RX
    if (GetWriteSpace(&descrFifoRX) >= (2 * MESS_SIZE)) 
    {
        // Active le signal RTS pour autoriser l'�mission par l'autre appareil
        RS232_RTS = 0;
    }

    // Retourne le statut de la communication
    return CommStatus;
}


/**
 * @brief Envoie un message contenant les param�tres PWM via la FIFO de transmission.
 * 
 * @details Cette fonction pr�pare les donn�es � transmettre (code de d�but, vitesse, angle et CRC),
 *          les ins�re dans la FIFO TX, et active les interruptions de transmission si n�cessaire.
 *          Elle v�rifie �galement si suffisamment d'espace est disponible dans la FIFO pour le message.
 * 
 * @param[in] pData Pointeur vers la structure contenant les param�tres de configuration PWM.
 * 
 * @return void Aucun retour. Le message est ajout� � la FIFO et pr�t pour l'envoi.
 */
void SendMessage(S_pwmSettings *pData)
{
    int16_t FreeSize;             // Taille de l'espace disponible dans la FIFO TX.
    uint16_t CrcVal = CRCINIT;    // Initialisation du CRC avec une valeur pr�d�finie.
    U_manip16 Crc;                // Union pour le calcul et la validation du CRC.

    // V�rifie l'espace libre disponible dans la FIFO TX
    FreeSize = GetWriteSpace(&descrFifoTX);

    // Si suffisamment d'espace est disponible, pr�parer et ajouter les donn�es au FIFO
    if (FreeSize >= MESS_SIZE)
    {
        // Calcul du CRC en utilisant les donn�es du message
        CrcVal = updateCRC16(CrcVal, STX_CODE);
        CrcVal = updateCRC16(CrcVal, pData->SpeedSetting);
        CrcVal = updateCRC16(CrcVal, pData->AngleSetting);

        // Stocke le CRC calcul� dans l'union locale
        Crc.Val = CrcVal;

        // Pr�pare le message � transmettre
        TxMess.Start = STX_CODE;             // Code de d�but.
        TxMess.Speed = pData->SpeedSetting;  // Vitesse.
        TxMess.Angle = pData->AngleSetting;  // Angle.
        TxMess.MsbCrc = Crc.shl.Msb;         // Octet sup�rieur du CRC.
        TxMess.LsbCrc = Crc.shl.Lsb;         // Octet inf�rieur du CRC.

        // Ajoute les donn�es dans la FIFO TX
        PutCharInFifo(&descrFifoTX, TxMess.Start);
        PutCharInFifo(&descrFifoTX, TxMess.Speed);
        PutCharInFifo(&descrFifoTX, TxMess.Angle);
        PutCharInFifo(&descrFifoTX, TxMess.MsbCrc);
        PutCharInFifo(&descrFifoTX, TxMess.LsbCrc);
    }

    // Met � jour l'espace libre apr�s l'ajout du message
    FreeSize = GetWriteSpace(&descrFifoTX);

    // Active l'interruption TX si le signal CTS est bas et s'il reste des donn�es � transmettre
    if ((RS232_CTS == 0) && (FreeSize > 0))
    {
        // Active l'interruption de transmission pour g�rer l'envoi
        PLIB_INT_SourceEnable(INT_ID_0, INT_SOURCE_USART_1_TRANSMIT);
    }
}

/**
 * @brief Interruption pour la gestion des �v�nements de l'USART 1 (RX, TX, erreurs).
 * 
 * @details Cette fonction g�re les interruptions li�es � l'USART 1, couvrant :
 *          1. La gestion des erreurs de r�ception (parit�, framing, overrun).
 *          2. La r�ception des donn�es (transfert FIFO hardware -> FIFO software RX).
 *          3. La transmission des donn�es (transfert FIFO software TX -> FIFO hardware).
 * 
 * @param[in] void Aucun param�tre requis.
 * 
 * @return void Aucun retour. Les donn�es sont trait�es et les interruptions sont g�r�es.
 */
void __ISR(_UART_1_VECTOR, ipl5AUTO) _IntHandlerDrvUsartInstance0(void) 
{
    USART_ERROR UsartStatus;       // �tat des erreurs d�tect�es sur l'USART.
    static int8_t CharUsartToFifo; // Donn�e re�ue depuis le UART � transf�rer dans la FIFO RX.
    static int8_t TxData;          // Donn�e � transmettre depuis la FIFO TX.
    uint8_t BuffSoftSize = 0;      // Taille des donn�es pr�sentes dans la FIFO TX (software).
    bool BuffHardFull = false;     // Indicateur d'�tat du buffer hardware de transmission (plein ou non).

    // Indique le d�but de l'interruption avec une LED.
    LED3_W = 1;

    // 1. Gestion des erreurs UART
    if (PLIB_INT_SourceFlagGet(INT_ID_0, INT_SOURCE_USART_1_ERROR) && 
        PLIB_INT_SourceIsEnabled(INT_ID_0, INT_SOURCE_USART_1_ERROR)) 
    {
        // Efface le drapeau d'interruption d'erreur.
        PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_USART_1_ERROR);

        // Vidange le buffer hardware pour supprimer les erreurs restantes.
        while (PLIB_USART_ReceiverDataIsAvailable(USART_ID_1)) {
            PLIB_USART_ReceiverByteReceive(USART_ID_1); // Lecture pour vider le buffer.
        }
    }

    // 2. Gestion des donn�es RX (r�ception)
    if (PLIB_INT_SourceFlagGet(INT_ID_0, INT_SOURCE_USART_1_RECEIVE) && 
        PLIB_INT_SourceIsEnabled(INT_ID_0, INT_SOURCE_USART_1_RECEIVE)) 
    {
        // R�cup�re l'�tat des erreurs sur la r�ception.
        UsartStatus = PLIB_USART_ErrorsGet(USART_ID_1);

        // V�rifie s'il n'y a pas d'erreurs (parit�, framing, overrun).
        if ((UsartStatus & (USART_ERROR_PARITY | USART_ERROR_FRAMING | USART_ERROR_RECEIVER_OVERRUN)) == 0) 
        {
            // Lecture des donn�es tant qu'elles sont disponibles dans le buffer hardware RX.
            while (PLIB_USART_ReceiverDataIsAvailable(USART_ID_1)) 
            {
                CharUsartToFifo = PLIB_USART_ReceiverByteReceive(USART_ID_1); // R�cup�re une donn�e.
                PutCharInFifo(&descrFifoRX, CharUsartToFifo);                 // Ajoute la donn�e dans la FIFO RX.
            }

            // Indique qu'une donn�e a �t� re�ue en inversant l'�tat de LED4.
            LED4_W = !LED4_R;

            // Efface le drapeau d'interruption RX.
            PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_USART_1_RECEIVE);
        } 
        else 
        {
            // Gestion sp�cifique des erreurs d'overrun.
            if ((UsartStatus & USART_ERROR_RECEIVER_OVERRUN) == USART_ERROR_RECEIVER_OVERRUN) {
                PLIB_USART_ReceiverOverrunErrorClear(USART_ID_1);
            }
        }

        // Contr�le de flux pour la r�ception.
        if (GetWriteSpace(&descrFifoRX) >= (2 * MESS_SIZE)) {
            RS232_RTS = 0; // Autorise l'�mission par l'autre appareil.
        } else {
            RS232_RTS = 1; // Bloque l'�mission.
        }
    }

    // 3. Gestion des donn�es TX (transmission)
    if (PLIB_INT_SourceFlagGet(INT_ID_0, INT_SOURCE_USART_1_TRANSMIT) && 
        PLIB_INT_SourceIsEnabled(INT_ID_0, INT_SOURCE_USART_1_TRANSMIT)) 
    {
        // Lit la taille disponible dans la FIFO TX (software) et l'�tat du buffer hardware TX.
        BuffSoftSize = GetReadSize(&descrFifoTX);
        BuffHardFull = PLIB_USART_TransmitterBufferIsFull(USART_ID_1);

        // V�rifie si le signal CTS est bas (autorisation d'�mettre).
        if (RS232_CTS == 0) 
        {
            // Tant que des donn�es sont disponibles et que le buffer hardware n'est pas plein.
            while (RS232_CTS == 0 && BuffSoftSize > 0 && BuffHardFull == false) 
            {
                GetCharFromFifo(&descrFifoTX, &TxData); // R�cup�re une donn�e depuis la FIFO TX.
                PLIB_USART_TransmitterByteSend(USART_ID_1, TxData); // Envoie la donn�e.

                // Met � jour les indicateurs apr�s l'envoi.
                BuffSoftSize = GetReadSize(&descrFifoTX);
                BuffHardFull = PLIB_USART_TransmitterBufferIsFull(USART_ID_1);
            }
        } 
        else 
        {
            // D�sactive l'�metteur si CTS est haut (surcharge �vit�e).
            PLIB_USART_TransmitterDisable(USART_ID_1);
        }

        // Inverse l'�tat de LED5 pour indiquer une transmission.
        LED5_W = !LED5_R;

        // D�sactive l'interruption TX si aucune donn�e n'est disponible.
        PLIB_INT_SourceDisable(INT_ID_0, INT_SOURCE_USART_1_TRANSMIT);

        // Efface le drapeau d'interruption TX.
        PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_USART_1_TRANSMIT);
    }

    // �teint LED3 pour indiquer la fin de l'interruption.
    LED3_W = 0;
}