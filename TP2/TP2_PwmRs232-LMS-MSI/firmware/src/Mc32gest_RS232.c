// Mc32Gest_RS232.C
// Canevas manipulatio TP2 RS232 SLO2 2017-18
// Fonctions d'émission et de réception des message
// CHR 20.12.2016 ajout traitement int error
// CHR 22.12.2016 evolution des marquers observation int Usart
// SCA 03.01.2018 nettoyé réponse interrupt pour ne laisser que les 3 ifs

#include <xc.h>
#include <sys/attribs.h>
#include "system_definitions.h"
// Ajout CHR
#include <GenericTypeDefs.h>
#include "app.h"
#include "GesFifoTh32.h"
#include "Mc32gest_RS232.h"
#include "gestPWM.h"
#include "Mc32CalCrc16.h"

/**
 * @brief Union permettant de manipuler un entier 16 bits (uint16_t) de différentes manières.
 * 
 * Cette union offre deux représentations du même entier :
 * - Accès direct à la valeur complète via le membre `val` (uint16_t).
 * - Accès séparé aux deux octets constituant l'entier via la structure `shl` :
 *   - `lsb` : Octet de poids faible (Least Significant Byte).
 *   - `msb` : Octet de poids fort (Most Significant Byte).
 */
typedef union {
        uint16_t Val;
        struct {uint8_t Lsb;
                uint8_t Msb;} shl;
} U_manip16;


// Definition pour les messages (Taille du message)
#define MESS_SIZE  5
// avec int8_t besoin -86 au lieu de 0xAA
#define STX_CODE  (-86)

/**
 * @brief Structure décrivant le format d'un message.
 * 
 * Cette structure définit les différents champs nécessaires pour transmettre un message,
 * comprenant des informations de contrôle, des paramètres, et un CRC pour la vérification.
 * 
 * Champs :
 * - `Start` : Identifiant de début de message (1 octet).
 * - `Speed` : Vitesse exprimée en entier signé (1 octet, plage [-128, 127]).
 * - `Angle` : Angle exprimé en entier signé (1 octet, plage [-128, 127]).
 * - `MsbCrc` : Octet de poids fort du CRC (1 octet).
 * - `LsbCrc` : Octet de poids faible du CRC (1 octet).
 */
typedef struct {
    uint8_t Start;    // Identifiant du début du message
    int8_t  Speed;    // Vitesse (valeur signée)
    int8_t  Angle;    // Angle (valeur signée)
    uint8_t MsbCrc;   // Octet de poids fort du CRC
    uint8_t LsbCrc;   // Octet de poids faible du CRC
} StruMess;



// Struct pour émission des messages
StruMess TxMess;
// Struct pour réception des messages
StruMess RxMess;

// Declaration des FIFO pour réception et émission
#define FIFO_RX_SIZE ( (4*MESS_SIZE) + 1)  // 4 messages
#define FIFO_TX_SIZE ( (4*MESS_SIZE) + 1)  // 4 messages

int8_t fifoRX[FIFO_RX_SIZE];
// Declaration du descripteur du FIFO de réception
S_fifo descrFifoRX;


int8_t fifoTX[FIFO_TX_SIZE];
// Declaration du descripteur du FIFO d'émission
S_fifo descrFifoTX;


#define CRCINIT 0xFFFF
// Déclaration des constantes pour GetMessage
//Définition de la valeur de caractère de start
#define CHARSTAR 0xAA
// Nombre de message en erreur avant passage en local
#define NBR_MESS_ERROR 10

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
    int CommStatus = 0;

    // Compteur statique pour le nombre d'erreurs consécutives dans les messages
    static uint8_t NbMessError = 0;

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

                // Met à jour l'angle dans les paramètres PWM
                pData->absAngle = RxMess.Angle;

                // Réinitialise le nombre de caractères à lire
                NbCharToRead = 0;

                // Allume une LED pour indiquer un CRC valide
                BSP_LEDOn(BSP_LED_6);

                // Réinitialise le compteur d'erreurs de message
                NbMessError = 0;
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

    // Vérifie si le nombre d'erreurs consécutives a atteint la limite autorisée
    if (NbMessError >= NBR_MESS_ERROR)
    {
        // Définit le mode local si trop d'erreurs sont détectées
        CommStatus = 0;
    }
    else
    {
        // Définit le mode remote si les messages sont valides
        CommStatus = 1;
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
    int8_t freeSize;

    // Initialisation de la valeur CRC avec une constante prédéfinie
    uint16_t CrcVal = CRCINIT;

    // Obtient l'espace libre disponible dans la FIFO TX
    freeSize = GetWriteSpace(&descrFifoTX);

    // Vérifie si l'espace libre est suffisant pour un message complet
    if (freeSize >= MESS_SIZE)
    {
        // Met à jour le CRC avec le code de démarrage du message
        CrcVal = updateCRC16(CrcVal, STX_CODE);

        // Met à jour le CRC avec la valeur de la vitesse
        CrcVal = updateCRC16(CrcVal, pData->SpeedSetting);

        // Met à jour le CRC avec la valeur de l'angle
        CrcVal = updateCRC16(CrcVal, pData->absAngle);

        // Affecte le code de démarrage dans la structure TxMess
        TxMess.Start = STX_CODE;

        // Affecte la vitesse dans la structure TxMess
        TxMess.Speed = pData->SpeedSetting;

        // Affecte l'angle dans la structure TxMess
        TxMess.Angle = pData->absAngle;

        // Affecte le MSB du CRC dans la structure TxMess
        TxMess.MsbCrc = CrcVal >> 8;

        // Affecte le LSB du CRC dans la structure TxMess
        TxMess.LsbCrc = CrcVal & 0xFF;

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
    freeSize = GetWriteSpace(&descrFifoTX);

    // Vérifie si le signal CTS est bas et qu'il reste de l'espace disponible
    if ((RS232_CTS == 0) && (freeSize > 0))
    {
        // Active l'interruption pour autoriser l'émission de données
        PLIB_INT_SourceEnable(INT_ID_0, INT_SOURCE_USART_1_TRANSMIT);
    }
}



// Interruption USART1
// !!!!!!!!
// Attention ne pas oublier de supprimer la réponse générée dans system_interrupt
// !!!!!!!!
 void __ISR(_UART_1_VECTOR, ipl5AUTO) _IntHandlerDrvUsartInstance0(void)
{
    USART_ERROR UsartStatus;    


    // Marque début interruption avec Led3
    LED3_W = 1;
    
    // Is this an Error interrupt ?
    if ( PLIB_INT_SourceFlagGet(INT_ID_0, INT_SOURCE_USART_1_ERROR) &&
                 PLIB_INT_SourceIsEnabled(INT_ID_0, INT_SOURCE_USART_1_ERROR) ) {
        /* Clear pending interrupt */
        PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_USART_1_ERROR);
        // Traitement de l'erreur à la réception.
    }
   

    // Is this an RX interrupt ?
    if ( PLIB_INT_SourceFlagGet(INT_ID_0, INT_SOURCE_USART_1_RECEIVE) &&
                 PLIB_INT_SourceIsEnabled(INT_ID_0, INT_SOURCE_USART_1_RECEIVE) ) {

        // Oui Test si erreur parité ou overrun
        UsartStatus = PLIB_USART_ErrorsGet(USART_ID_1);

        if ( (UsartStatus & (USART_ERROR_PARITY |
                             USART_ERROR_FRAMING | USART_ERROR_RECEIVER_OVERRUN)) == 0) {

            // Traitement RX à faire ICI
            // Lecture des caractères depuis le buffer HW -> fifo SW
			//  (pour savoir s'il y a une data dans le buffer HW RX : PLIB_USART_ReceiverDataIsAvailable())
			//  (Lecture via fonction PLIB_USART_ReceiverByteReceive())
            // ...
            
                         
            LED4_W = !LED4_R; // Toggle Led4
            // buffer is empty, clear interrupt flag
            PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_USART_1_RECEIVE);
        } else {
            // Suppression des erreurs
            // La lecture des erreurs les efface sauf pour overrun
            if ( (UsartStatus & USART_ERROR_RECEIVER_OVERRUN) == USART_ERROR_RECEIVER_OVERRUN) {
                   PLIB_USART_ReceiverOverrunErrorClear(USART_ID_1);
            }
        }

        
        // Traitement controle de flux reception à faire ICI
        // Gerer sortie RS232_RTS en fonction de place dispo dans fifo reception
        // ...

        
    } // end if RX

    
    // Is this an TX interrupt ?
    if ( PLIB_INT_SourceFlagGet(INT_ID_0, INT_SOURCE_USART_1_TRANSMIT) &&
                 PLIB_INT_SourceIsEnabled(INT_ID_0, INT_SOURCE_USART_1_TRANSMIT) ) {

        // Traitement TX à faire ICI
        // Envoi des caractères depuis le fifo SW -> buffer HW
            
        // Avant d'émettre, on vérifie 3 conditions :
        //  Si CTS = 0 autorisation d'émettre (entrée RS232_CTS)
        //  S'il y a un caratères à émettre dans le fifo
        //  S'il y a de la place dans le buffer d'émission (PLIB_USART_TransmitterBufferIsFull)
        //   (envoi avec PLIB_USART_TransmitterByteSend())
       
        // ...
       
	   
        LED5_W = !LED5_R; // Toggle Led5
		
        // disable TX interrupt (pour éviter une interrupt. inutile si plus rien à transmettre)
        PLIB_INT_SourceDisable(INT_ID_0, INT_SOURCE_USART_1_TRANSMIT);
        
        // Clear the TX interrupt Flag (Seulement apres TX) 
        PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_USART_1_TRANSMIT);
    }
    // Marque fin interruption avec Led3
    LED3_W = 0;
 }




