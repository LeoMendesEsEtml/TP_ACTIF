// Mc32Gest_RS232.C
// Canevas manipulatio TP2 RS232 SLO2 2017-18
// Fonctions d'�mission et de r�ception des message
// CHR 20.12.2016 ajout traitement int error
// CHR 22.12.2016 evolution des marquers observation int Usart
// SCA 03.01.2018 nettoy� r�ponse interrupt pour ne laisser que les 3 ifs

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
 * @brief Union permettant de manipuler un entier 16 bits (uint16_t) de diff�rentes mani�res.
 * 
 * Cette union offre deux repr�sentations du m�me entier :
 * - Acc�s direct � la valeur compl�te via le membre `val` (uint16_t).
 * - Acc�s s�par� aux deux octets constituant l'entier via la structure `shl` :
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
 * @brief Structure d�crivant le format d'un message.
 * 
 * Cette structure d�finit les diff�rents champs n�cessaires pour transmettre un message,
 * comprenant des informations de contr�le, des param�tres, et un CRC pour la v�rification.
 * 
 * Champs :
 * - `Start` : Identifiant de d�but de message (1 octet).
 * - `Speed` : Vitesse exprim�e en entier sign� (1 octet, plage [-128, 127]).
 * - `Angle` : Angle exprim� en entier sign� (1 octet, plage [-128, 127]).
 * - `MsbCrc` : Octet de poids fort du CRC (1 octet).
 * - `LsbCrc` : Octet de poids faible du CRC (1 octet).
 */
typedef struct {
    uint8_t Start;    // Identifiant du d�but du message
    int8_t  Speed;    // Vitesse (valeur sign�e)
    int8_t  Angle;    // Angle (valeur sign�e)
    uint8_t MsbCrc;   // Octet de poids fort du CRC
    uint8_t LsbCrc;   // Octet de poids faible du CRC
} StruMess;



// Struct pour �mission des messages
StruMess TxMess;
// Struct pour r�ception des messages
StruMess RxMess;

// Declaration des FIFO pour r�ception et �mission
#define FIFO_RX_SIZE ( (4*MESS_SIZE) + 1)  // 4 messages
#define FIFO_TX_SIZE ( (4*MESS_SIZE) + 1)  // 4 messages

int8_t fifoRX[FIFO_RX_SIZE];
// Declaration du descripteur du FIFO de r�ception
S_fifo descrFifoRX;


int8_t fifoTX[FIFO_TX_SIZE];
// Declaration du descripteur du FIFO d'�mission
S_fifo descrFifoTX;


#define CRCINIT 0xFFFF
// D�claration des constantes pour GetMessage
//D�finition de la valeur de caract�re de start
#define CHARSTAR 0xAA
// Nombre de message en erreur avant passage en local
#define NBR_MESS_ERROR 10

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
    int CommStatus = 0;

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

                // Met � jour l'angle dans les param�tres PWM
                pData->absAngle = RxMess.Angle;

                // R�initialise le nombre de caract�res � lire
                NbCharToRead = 0;

                // Allume une LED pour indiquer un CRC valide
                BSP_LEDOn(BSP_LED_6);

                // R�initialise le compteur d'erreurs de message
                NbMessError = 0;
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

    // V�rifie si le nombre d'erreurs cons�cutives a atteint la limite autoris�e
    if (NbMessError >= NBR_MESS_ERROR)
    {
        // D�finit le mode local si trop d'erreurs sont d�tect�es
        CommStatus = 0;
    }
    else
    {
        // D�finit le mode remote si les messages sont valides
        CommStatus = 1;
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
    int8_t freeSize;

    // Initialisation de la valeur CRC avec une constante pr�d�finie
    uint16_t CrcVal = CRCINIT;

    // Obtient l'espace libre disponible dans la FIFO TX
    freeSize = GetWriteSpace(&descrFifoTX);

    // V�rifie si l'espace libre est suffisant pour un message complet
    if (freeSize >= MESS_SIZE)
    {
        // Met � jour le CRC avec le code de d�marrage du message
        CrcVal = updateCRC16(CrcVal, STX_CODE);

        // Met � jour le CRC avec la valeur de la vitesse
        CrcVal = updateCRC16(CrcVal, pData->SpeedSetting);

        // Met � jour le CRC avec la valeur de l'angle
        CrcVal = updateCRC16(CrcVal, pData->absAngle);

        // Affecte le code de d�marrage dans la structure TxMess
        TxMess.Start = STX_CODE;

        // Affecte la vitesse dans la structure TxMess
        TxMess.Speed = pData->SpeedSetting;

        // Affecte l'angle dans la structure TxMess
        TxMess.Angle = pData->absAngle;

        // Affecte le MSB du CRC dans la structure TxMess
        TxMess.MsbCrc = CrcVal >> 8;

        // Affecte le LSB du CRC dans la structure TxMess
        TxMess.LsbCrc = CrcVal & 0xFF;

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
    freeSize = GetWriteSpace(&descrFifoTX);

    // V�rifie si le signal CTS est bas et qu'il reste de l'espace disponible
    if ((RS232_CTS == 0) && (freeSize > 0))
    {
        // Active l'interruption pour autoriser l'�mission de donn�es
        PLIB_INT_SourceEnable(INT_ID_0, INT_SOURCE_USART_1_TRANSMIT);
    }
}



// Interruption USART1
// !!!!!!!!
// Attention ne pas oublier de supprimer la r�ponse g�n�r�e dans system_interrupt
// !!!!!!!!
 void __ISR(_UART_1_VECTOR, ipl5AUTO) _IntHandlerDrvUsartInstance0(void)
{
    USART_ERROR UsartStatus;    


    // Marque d�but interruption avec Led3
    LED3_W = 1;
    
    // Is this an Error interrupt ?
    if ( PLIB_INT_SourceFlagGet(INT_ID_0, INT_SOURCE_USART_1_ERROR) &&
                 PLIB_INT_SourceIsEnabled(INT_ID_0, INT_SOURCE_USART_1_ERROR) ) {
        /* Clear pending interrupt */
        PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_USART_1_ERROR);
        // Traitement de l'erreur � la r�ception.
    }
   

    // Is this an RX interrupt ?
    if ( PLIB_INT_SourceFlagGet(INT_ID_0, INT_SOURCE_USART_1_RECEIVE) &&
                 PLIB_INT_SourceIsEnabled(INT_ID_0, INT_SOURCE_USART_1_RECEIVE) ) {

        // Oui Test si erreur parit� ou overrun
        UsartStatus = PLIB_USART_ErrorsGet(USART_ID_1);

        if ( (UsartStatus & (USART_ERROR_PARITY |
                             USART_ERROR_FRAMING | USART_ERROR_RECEIVER_OVERRUN)) == 0) {

            // Traitement RX � faire ICI
            // Lecture des caract�res depuis le buffer HW -> fifo SW
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

        
        // Traitement controle de flux reception � faire ICI
        // Gerer sortie RS232_RTS en fonction de place dispo dans fifo reception
        // ...

        
    } // end if RX

    
    // Is this an TX interrupt ?
    if ( PLIB_INT_SourceFlagGet(INT_ID_0, INT_SOURCE_USART_1_TRANSMIT) &&
                 PLIB_INT_SourceIsEnabled(INT_ID_0, INT_SOURCE_USART_1_TRANSMIT) ) {

        // Traitement TX � faire ICI
        // Envoi des caract�res depuis le fifo SW -> buffer HW
            
        // Avant d'�mettre, on v�rifie 3 conditions :
        //  Si CTS = 0 autorisation d'�mettre (entr�e RS232_CTS)
        //  S'il y a un carat�res � �mettre dans le fifo
        //  S'il y a de la place dans le buffer d'�mission (PLIB_USART_TransmitterBufferIsFull)
        //   (envoi avec PLIB_USART_TransmitterByteSend())
       
        // ...
       
	   
        LED5_W = !LED5_R; // Toggle Led5
		
        // disable TX interrupt (pour �viter une interrupt. inutile si plus rien � transmettre)
        PLIB_INT_SourceDisable(INT_ID_0, INT_SOURCE_USART_1_TRANSMIT);
        
        // Clear the TX interrupt Flag (Seulement apres TX) 
        PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_USART_1_TRANSMIT);
    }
    // Marque fin interruption avec Led3
    LED3_W = 0;
 }




