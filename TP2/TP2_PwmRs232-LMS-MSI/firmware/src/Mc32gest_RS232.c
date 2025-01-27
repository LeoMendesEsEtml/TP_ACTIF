// Mc32Gest_RS232.C
// Canevas manipulatio TP2 RS232 SLO2 2017-18
// Fonctions d'émission et de réception des message
// CHR 20.12.2016 ajout traitement int error
// CHR 22.12.2016 evolution des marquers observation int Usart
// SCA 03.01.2018 nettoyé réponse interrupt pour ne laisser que les 3 ifs

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


// Struct pour émission des messages
StruMess TxMess;
// Struct pour réception des messages
StruMess RxMess;

int8_t fifoRX[FIFO_RX_SIZE];
// Declaration du descripteur du FIFO de réception
S_fifo descrFifoRX;


int8_t fifoTX[FIFO_TX_SIZE];
// Declaration du descripteur du FIFO d'émission
S_fifo descrFifoTX;



// Initialisation de la communication sérielle
void InitFifoComm(void)
{    
    // Initialisation du fifo de réception
    InitFifo ( &descrFifoRX, FIFO_RX_SIZE, fifoRX, 0 );
    // Initialisation du fifo d'émission
    InitFifo ( &descrFifoTX, FIFO_TX_SIZE, fifoTX, 0 );
    
    // Init RTS 
    RS232_RTS = 1;   // interdit émission par l'autre
   
} // InitComm

 
/**
 * @brief Traite la réception de messages et met à jour les données si un message valide est reçu.
 * 
 * @param[in,out] pData Pointeur vers la structure contenant les paramètres de configuration PWM.
 * @return int Statut de la communication :
 *             - 0 : Pas de message reçu (local, données non modifiées).
 *             - 1 : Message reçu (remote, données mises à jour).
 */
int GetMessage(S_pwmSettings *pData)
{
    // Initialise le statut de la communication (local par défaut)
    static int CommStatus = 0;

    // Compteur statique pour le nombre d'erreurs consécutives dans les messages
    static uint8_t NbMessError = 10;

    // Nombre de caractères à lire depuis la FIFO RX
    static uint8_t NbCharToRead = 0;

    // Union pour le calcul et la validation du CRC
    U_manip16 Crc;

    // Initialise la valeur du CRC avec une constante prédéfinie
    uint16_t CrcVal = CRCINIT;

    // Obtient le nombre de caractères disponibles dans la FIFO RX
    NbCharToRead = GetReadSize(&descrFifoRX);

    // Vérifie si le nombre de caractères disponibles correspond à un message complet
    if (NbCharToRead >= MESS_SIZE)
    {
        // Lit le premier caractère de la FIFO et le stocke dans la structure RxMess
        GetCharFromFifo(&descrFifoRX, &RxMess.Start);

        // Vérifie si le caractère reçu est un code de début valide
        if (RxMess.Start == STX_CODE)
        {
            // Lit le paramètre de vitesse depuis la FIFO RX
            GetCharFromFifo(&descrFifoRX, &RxMess.Speed);

            // Lit le paramètre d'angle depuis la FIFO RX
            GetCharFromFifo(&descrFifoRX, &RxMess.Angle);

            // Lit le MSB (octet supérieur) du CRC reçu depuis la FIFO RX
            GetCharFromFifo(&descrFifoRX, &RxMess.MsbCrc);

            // Stocke le MSB dans l'union Crc
            Crc.shl.Msb = RxMess.MsbCrc;

            // Lit le LSB (octet inférieur) du CRC reçu depuis la FIFO RX
            GetCharFromFifo(&descrFifoRX, &RxMess.LsbCrc);

            // Stocke le LSB dans l'union Crc
            Crc.shl.Lsb = RxMess.LsbCrc;

            // Met à jour le CRC calculé avec le code de début
            CrcVal = updateCRC16(CrcVal, STX_CODE);

            // Met à jour le CRC calculé avec la valeur de la vitesse
            CrcVal = updateCRC16(CrcVal, RxMess.Speed);

            // Met à jour le CRC calculé avec la valeur de l'angle
            CrcVal = updateCRC16(CrcVal, RxMess.Angle);

            // Compare le CRC calculé avec celui reçu
            if (Crc.Val == CrcVal)
            {
                // Met à jour la vitesse dans les paramètres PWM
                pData->SpeedSetting = RxMess.Speed;
                pData->absSpeed = abs(RxMess.Speed);        
                
                // Met à jour l'angle dans les paramètres PWM
                pData->AngleSetting = RxMess.Angle;
                pData->absAngle = abs(RxMess.Angle);

                CommStatus = REMOTE;
                // Réinitialise le compteur d'erreurs de message
                NbMessError = 0;
                // Allume une LED pour indiquer un CRC valide
                BSP_LEDOn(BSP_LED_6);
            }
            else
            {
                // Éteint la LED pour indiquer une erreur CRC
                BSP_LEDOff(BSP_LED_6);

                // Incrémente le compteur d'erreurs de message
                NbMessError++;
            }
        }
        else
        {
            // Incrémente le compteur d'erreurs de message si le code de début est incorrect
            NbMessError++;
        }
    }
    else
    {
        // Incrémente le compteur d'erreurs de message si le code de début est incorrect
        NbMessError++;
        // Vérifie si le nombre d'erreurs consécutives a atteint la limite autorisée
        if (NbMessError >= NBR_MESS_ERROR)
        {
          // Définit le mode local si trop d'erreurs sont détectées
          CommStatus = LOCAL;
          NbMessError = 10;
     }
    }

    // Vérifie l'espace disponible dans la FIFO RX pour gérer le contrôle de flux
    if (GetWriteSpace(&descrFifoRX) >= (2 * MESS_SIZE))
    {
        // Active le signal RTS pour autoriser l'émission par l'autre appareil
        RS232_RTS = 0;
    }

    // Retourne le statut de la communication
    return CommStatus;
}


/**
 * @brief Envoie un message contenant les paramètres PWM via une FIFO de transmission.
 *
 * @param[in] pData Pointeur vers la structure contenant les paramètres de configuration PWM.
 */
void SendMessage(S_pwmSettings *pData)
{
    // Variable locale pour stocker la taille libre dans la FIFO de transmission
    int16_t FreeSize;

    // Initialisation de la valeur CRC avec une constante prédéfinie
    uint16_t CrcVal = CRCINIT;
    
    // Union pour le calcul et la validation du CRC
    U_manip16 Crc;

    // Obtient l'espace libre disponible dans la FIFO TX
    FreeSize = GetWriteSpace(&descrFifoTX);

    // Vérifie si l'espace libre est suffisant pour un message complet
    if (FreeSize >= MESS_SIZE)
    {
        // Met à jour le CRC avec le code de démarrage du message
        CrcVal = updateCRC16(CrcVal, STX_CODE);

        // Met à jour le CRC avec la valeur de la vitesse
        CrcVal = updateCRC16(CrcVal, pData->SpeedSetting);

        // Met à jour le CRC avec la valeur de l'angle
        CrcVal = updateCRC16(CrcVal, pData->AngleSetting);
        
        // Affecte le crc caculer à l'union local CRC
        Crc.Val = CrcVal;

        // Affecte le code de démarrage dans la structure TxMess
        TxMess.Start = STX_CODE;

        // Affecte la vitesse dans la structure TxMess
        TxMess.Speed = pData->SpeedSetting;

        // Affecte l'angle dans la structure TxMess
        TxMess.Angle = pData->AngleSetting;

        // Affecte le MSB du CRC dans la structure TxMess
        TxMess.MsbCrc = Crc.shl.Msb;

        // Affecte le LSB du CRC dans la structure TxMess
        TxMess.LsbCrc = Crc.shl.Lsb;

        // Dépose le code de démarrage dans la FIFO TX
        PutCharInFifo(&descrFifoTX, TxMess.Start);

        // Dépose la vitesse dans la FIFO TX
        PutCharInFifo(&descrFifoTX, TxMess.Speed);

        // Dépose l'angle dans la FIFO TX
        PutCharInFifo(&descrFifoTX, TxMess.Angle);

        // Dépose le MSB du CRC dans la FIFO TX
        PutCharInFifo(&descrFifoTX, TxMess.MsbCrc);

        // Dépose le LSB du CRC dans la FIFO TX
        PutCharInFifo(&descrFifoTX, TxMess.LsbCrc);
    }

    // Met à jour la taille libre disponible dans la FIFO TX
    FreeSize = GetWriteSpace(&descrFifoTX);

    // Vérifie si le signal CTS est bas et qu'il reste de l'espace disponible
    if ((RS232_CTS == 0) && (FreeSize > 0))
    {
        // Active l'interruption pour autoriser l'émission de données
        PLIB_INT_SourceEnable(INT_ID_0, INT_SOURCE_USART_1_TRANSMIT);
    }
}



/**
 * @brief Interruption pour la gestion de l'USART (RX, TX, erreurs).
 * 
 * @details Cette fonction gère les interruptions liées à l'USART 1.
 * Elle couvre :
 * 1. Le traitement des erreurs de réception.
 * 2. La réception des données (FIFO hardware -> FIFO software).
 * 3. La transmission des données (FIFO software -> FIFO hardware).
 */
void __ISR(_UART_1_VECTOR, ipl5AUTO) _IntHandlerDrvUsartInstance0(void) 
{
    // Déclaration pour gérer les erreurs USART
    USART_ERROR UsartStatus;

    static int8_t CharUsartToFifo;  // Donnée reçue depuis le UART à transférer dans la FIFO
    static int8_t TxData;           // Donnée à transmettre depuis la FIFO
    uint8_t BuffSoftSize = 0;       // Taille des données présentes dans la FIFO software
    bool BuffHardFull = false;       // Indicateur d'état du buffer hardware de transmission (plein ou non)

    // Allume LED3 pour indiquer le début de l'interruption
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
        // Si besoin, lire le FIFO RX hardware pour vider les éventuelles data erronées
        while (PLIB_USART_ReceiverDataIsAvailable(USART_ID_1)) {
            (void) PLIB_USART_ReceiverByteReceive(USART_ID_1);
        }
    }

    // 2. Gestion des données RX (réception)
    if (PLIB_INT_SourceFlagGet(INT_ID_0, INT_SOURCE_USART_1_RECEIVE) && 
        PLIB_INT_SourceIsEnabled(INT_ID_0, INT_SOURCE_USART_1_RECEIVE)) 
    {
        // Vérifie s'il y a des erreurs de réception (parité, framing, overrun)
        UsartStatus = PLIB_USART_ErrorsGet(USART_ID_1);

        if ((UsartStatus & (USART_ERROR_PARITY | USART_ERROR_FRAMING | USART_ERROR_RECEIVER_OVERRUN)) == 0) 
        {
            // Lecture des données tant qu'elles sont disponibles dans le buffer hardware RX
            while (PLIB_USART_ReceiverDataIsAvailable(USART_ID_1)) {
                // Récupère un caractère du buffer hardware
                CharUsartToFifo = PLIB_USART_ReceiverByteReceive(USART_ID_1);
                // Ajoute ce caractère dans la FIFO software RX
                PutCharInFifo(&descrFifoRX, CharUsartToFifo);
            }

            // Inverse l'état de LED4 pour indiquer qu'une donnée a été reçue
            LED4_W = !LED4_R;

            // Efface le drapeau d'interruption RX (plus de données à lire)
            PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_USART_1_RECEIVE);
        } 
        else 
        {
            // Suppression des erreurs spécifiques (notamment overrun)
            if ((UsartStatus & USART_ERROR_RECEIVER_OVERRUN) == USART_ERROR_RECEIVER_OVERRUN) {
                PLIB_USART_ReceiverOverrunErrorClear(USART_ID_1);
            }
        }
      if (GetWriteSpace(&descrFifoRX) <= MESS_SIZE +1) 
      {
            RS232_RTS = 1; 
      }
    }

    // 3. Gestion des données TX (transmission)
    if (PLIB_INT_SourceFlagGet(INT_ID_0, INT_SOURCE_USART_1_TRANSMIT) && 
        PLIB_INT_SourceIsEnabled(INT_ID_0, INT_SOURCE_USART_1_TRANSMIT)) 
    {
        // Lit la taille disponible dans la FIFO software TX et l'état du buffer hardware TX
        BuffSoftSize = GetReadSize(&descrFifoTX);
        BuffHardFull = PLIB_USART_TransmitterBufferIsFull(USART_ID_1);

        // Si le signal CTS (Clear To Send) est bas, on peut émettre
        if ((RS232_CTS == 0) && (BuffSoftSize > 0) && (BuffHardFull == false))
        {
            // Transmission des données tant que les conditions sont remplies
            while (RS232_CTS == 0 && BuffSoftSize > 0 && BuffHardFull == false) 
            {
                // Récupère une donnée à transmettre depuis la FIFO software
                GetCharFromFifo(&descrFifoTX, &TxData);
                // Envoie cette donnée dans le buffer hardware TX
                PLIB_USART_TransmitterByteSend(USART_ID_1, TxData);

                // Mets à jour les indicateurs après l'envoi
                BuffSoftSize = GetReadSize(&descrFifoTX);
                BuffHardFull = PLIB_USART_TransmitterBufferIsFull(USART_ID_1);
            }
        } 
        else 
        {
            // Si CTS est haut, désactive l'émetteur pour éviter une surcharge
            PLIB_USART_TransmitterDisable(USART_ID_1);
        }

        // Inverse l'état de LED5 pour indiquer une transmission
        LED5_W = !LED5_R;

        // Efface le drapeau d'interruption TX
        PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_USART_1_TRANSMIT);
    }

    // Éteint LED3 pour indiquer la fin de l'interruption
    LED3_W = 0;
}