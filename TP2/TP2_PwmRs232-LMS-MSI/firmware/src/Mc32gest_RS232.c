// Mc32Gest_RS232.C
// Canevas manipulatio TP2 RS232 SLO2 2017-18
// Fonctions d'�mission et de r�ception des message
// CHR 20.12.2016 ajout traitement int error
// CHR 22.12.2016 evolution des marquers observation int Usart
// SCA 03.01.2018 nettoy� r�ponse interrupt pour ne laisser que les 3 ifs

#include <xc.h>
#include <sys/attribs.h>
#include <stdbool.h>
#include <stdlib.h>
#include "system_definitions.h"
// Ajout CHR
#include <GenericTypeDefs.h>
#include "app.h"
#include "GesFifoTh32.h"
#include "Mc32gest_RS232.h"
#include "gestPWM.h"
#include "Mc32CalCrc16.h"


// Struct pour �mission des messages
StruMess TxMess;
// Struct pour r�ception des messages
StruMess RxMess;

int8_t fifoRX[FIFO_RX_SIZE];
// Declaration du descripteur du FIFO de r�ception
S_fifo descrFifoRX;


int8_t fifoTX[FIFO_TX_SIZE];
// Declaration du descripteur du FIFO d'�mission
S_fifo descrFifoTX;



// Initialisation de la communication s�rielle
void InitFifoComm(void)
{    
    // Initialisation du fifo de r�ception
    InitFifo ( &descrFifoRX, FIFO_RX_SIZE, fifoRX, 0 );
    // Initialisation du fifo d'�mission
    InitFifo ( &descrFifoTX, FIFO_TX_SIZE, fifoTX, 0 );
    
    // Init RTS 
    RS232_RTS = 1;   // interdit �mission par l'autre
   
} // InitComm

 
/**
 * @brief Traite la r�ception de messages et met � jour les donn�es si un message valide est re�u.
 * 
 * @param[in,out] pData Pointeur vers la structure contenant les param�tres de configuration PWM.
 * @return int Statut de la communication :
 *             - 0 : Pas de message re�u (local, donn�es non modifi�es).
 *             - 1 : Message re�u (remote, donn�es mises � jour).
 */
int GetMessage(S_pwmSettings *pData)
{
    // Initialise le statut de la communication (local par d�faut)
    static int CommStatus = 0;

    // Compteur statique pour le nombre d'erreurs cons�cutives dans les messages
    static uint8_t NbMessError = 10;

    // Nombre de caract�res � lire depuis la FIFO RX
    static uint8_t NbCharToRead = 0;

    // Union pour le calcul et la validation du CRC
    U_manip16 Crc;

    // Initialise la valeur du CRC avec une constante pr�d�finie
    uint16_t CrcVal = CRCINIT;

    // Obtient le nombre de caract�res disponibles dans la FIFO RX
    NbCharToRead = GetReadSize(&descrFifoRX);

    // V�rifie si le nombre de caract�res disponibles correspond � un message complet
    if (NbCharToRead >= MESS_SIZE)
    {
        // Lit le premier caract�re de la FIFO et le stocke dans la structure RxMess
        GetCharFromFifo(&descrFifoRX, &RxMess.Start);

        // V�rifie si le caract�re re�u est un code de d�but valide
        if (RxMess.Start == STX_CODE)
        {
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
            if (Crc.Val == CrcVal)
            {
                // Met � jour la vitesse dans les param�tres PWM
                pData->SpeedSetting = RxMess.Speed;
                pData->absSpeed = abs(RxMess.Speed);        
                
                // Met � jour l'angle dans les param�tres PWM
                pData->AngleSetting = RxMess.Angle;
                pData->absAngle = abs(RxMess.Angle);

                CommStatus = REMOTE;
                // R�initialise le compteur d'erreurs de message
                NbMessError = 0;
                // Allume une LED pour indiquer un CRC valide
                BSP_LEDOn(BSP_LED_6);
            }
            else
            {
                // �teint la LED pour indiquer une erreur CRC
                BSP_LEDOff(BSP_LED_6);

                // Incr�mente le compteur d'erreurs de message
                NbMessError++;
            }
        }
        else
        {
            // Incr�mente le compteur d'erreurs de message si le code de d�but est incorrect
            NbMessError++;
        }
    }
    else
    {
        // Incr�mente le compteur d'erreurs de message si le code de d�but est incorrect
        NbMessError++;
        // V�rifie si le nombre d'erreurs cons�cutives a atteint la limite autoris�e
        if (NbMessError >= NBR_MESS_ERROR)
        {
          // D�finit le mode local si trop d'erreurs sont d�tect�es
          CommStatus = LOCAL;
          NbMessError = 10;
     }
    }

    // V�rifie l'espace disponible dans la FIFO RX pour g�rer le contr�le de flux
    if (GetWriteSpace(&descrFifoRX) >= (2 * MESS_SIZE))
    {
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
void SendMessage(S_pwmSettings *pData)
{
    // Variable locale pour stocker la taille libre dans la FIFO de transmission
    int16_t FreeSize;

    // Initialisation de la valeur CRC avec une constante pr�d�finie
    uint16_t CrcVal = CRCINIT;
    
    // Union pour le calcul et la validation du CRC
    U_manip16 Crc;

    // Obtient l'espace libre disponible dans la FIFO TX
    FreeSize = GetWriteSpace(&descrFifoTX);

    // V�rifie si l'espace libre est suffisant pour un message complet
    if (FreeSize >= MESS_SIZE)
    {
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

    // V�rifie si le signal CTS est bas et qu'il reste de l'espace disponible
    if ((RS232_CTS == 0) && (FreeSize > 0))
    {
        // Active l'interruption pour autoriser l'�mission de donn�es
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
void __ISR(_UART_1_VECTOR, ipl5AUTO) _IntHandlerDrvUsartInstance0(void) 
{
    // D�claration pour g�rer les erreurs USART
    USART_ERROR UsartStatus;

    static int8_t CharUsartToFifo;  // Donn�e re�ue depuis le UART � transf�rer dans la FIFO
    static int8_t TxData;           // Donn�e � transmettre depuis la FIFO
    uint8_t BuffSoftSize = 0;       // Taille des donn�es pr�sentes dans la FIFO software
    bool BuffHardFull = false;       // Indicateur d'�tat du buffer hardware de transmission (plein ou non)

    // Allume LED3 pour indiquer le d�but de l'interruption
    LED3_W = 1;

    // 1. Gestion des erreurs UART
    if (PLIB_INT_SourceFlagGet(INT_ID_0, INT_SOURCE_USART_1_ERROR) &&
            PLIB_INT_SourceIsEnabled(INT_ID_0, INT_SOURCE_USART_1_ERROR)) {
        // On nettoie le flag d'interruption
        PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_USART_1_ERROR);

        // Lit la cause de l'erreur
        UsartStatus = PLIB_USART_ErrorsGet(USART_ID_1);

        // Si overrun, on le clear
        if ((UsartStatus & USART_ERROR_RECEIVER_OVERRUN) == USART_ERROR_RECEIVER_OVERRUN) {
            PLIB_USART_ReceiverOverrunErrorClear(USART_ID_1);
        }
        // Si besoin, lire le FIFO RX hardware pour vider les �ventuelles data erron�es
        while (PLIB_USART_ReceiverDataIsAvailable(USART_ID_1)) {
            (void) PLIB_USART_ReceiverByteReceive(USART_ID_1);
        }
    }

    // 2. Gestion des donn�es RX (r�ception)
    if (PLIB_INT_SourceFlagGet(INT_ID_0, INT_SOURCE_USART_1_RECEIVE) && 
        PLIB_INT_SourceIsEnabled(INT_ID_0, INT_SOURCE_USART_1_RECEIVE)) 
    {
        // V�rifie s'il y a des erreurs de r�ception (parit�, framing, overrun)
        UsartStatus = PLIB_USART_ErrorsGet(USART_ID_1);

        if ((UsartStatus & (USART_ERROR_PARITY | USART_ERROR_FRAMING | USART_ERROR_RECEIVER_OVERRUN)) == 0) 
        {
            // Lecture des donn�es tant qu'elles sont disponibles dans le buffer hardware RX
            while (PLIB_USART_ReceiverDataIsAvailable(USART_ID_1)) {
                // R�cup�re un caract�re du buffer hardware
                CharUsartToFifo = PLIB_USART_ReceiverByteReceive(USART_ID_1);
                // Ajoute ce caract�re dans la FIFO software RX
                PutCharInFifo(&descrFifoRX, CharUsartToFifo);
            }

            // Inverse l'�tat de LED4 pour indiquer qu'une donn�e a �t� re�ue
            LED4_W = !LED4_R;

            // Efface le drapeau d'interruption RX (plus de donn�es � lire)
            PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_USART_1_RECEIVE);
        } 
        else 
        {
            // Suppression des erreurs sp�cifiques (notamment overrun)
            if ((UsartStatus & USART_ERROR_RECEIVER_OVERRUN) == USART_ERROR_RECEIVER_OVERRUN) {
                PLIB_USART_ReceiverOverrunErrorClear(USART_ID_1);
            }
        }
      if (GetWriteSpace(&descrFifoRX) <= MESS_SIZE +1) 
      {
            RS232_RTS = 1; 
      }
    }

    // 3. Gestion des donn�es TX (transmission)
    if (PLIB_INT_SourceFlagGet(INT_ID_0, INT_SOURCE_USART_1_TRANSMIT) && 
        PLIB_INT_SourceIsEnabled(INT_ID_0, INT_SOURCE_USART_1_TRANSMIT)) 
    {
        // Lit la taille disponible dans la FIFO software TX et l'�tat du buffer hardware TX
        BuffSoftSize = GetReadSize(&descrFifoTX);
        BuffHardFull = PLIB_USART_TransmitterBufferIsFull(USART_ID_1);

        // Si le signal CTS (Clear To Send) est bas, on peut �mettre
        if ((RS232_CTS == 0) && (BuffSoftSize > 0) && (BuffHardFull == false))
        {
            // Transmission des donn�es tant que les conditions sont remplies
            while (RS232_CTS == 0 && BuffSoftSize > 0 && BuffHardFull == false) 
            {
                // R�cup�re une donn�e � transmettre depuis la FIFO software
                GetCharFromFifo(&descrFifoTX, &TxData);
                // Envoie cette donn�e dans le buffer hardware TX
                PLIB_USART_TransmitterByteSend(USART_ID_1, TxData);

                // Mets � jour les indicateurs apr�s l'envoi
                BuffSoftSize = GetReadSize(&descrFifoTX);
                BuffHardFull = PLIB_USART_TransmitterBufferIsFull(USART_ID_1);
            }
        } 
        else 
        {
            // Si CTS est haut, d�sactive l'�metteur pour �viter une surcharge
            PLIB_USART_TransmitterDisable(USART_ID_1);
        }

        // Inverse l'�tat de LED5 pour indiquer une transmission
        LED5_W = !LED5_R;

        // Efface le drapeau d'interruption TX
        PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_USART_1_TRANSMIT);
    }

    // �teint LED3 pour indiquer la fin de l'interruption
    LED3_W = 0;
}