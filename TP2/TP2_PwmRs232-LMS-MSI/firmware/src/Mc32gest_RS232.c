// Mc32Gest_RS232.C
// Canevas manipulatio TP2 RS232 SLO2 2017-18
// Fonctions d'émission et de réception des message
// CHR 20.12.2016 ajout traitement int error
// CHR 22.12.2016 evolution des marquers observation int Usart
// SCA 03.01.2018 nettoyé réponse interrupt pour ne laisser que les 3 ifs

// Bibliothèques standards
#include <stdlib.h>       // Fonctions utilitaires générales (e.g., abs).
#include <stdbool.h>      // Types booléens (true/false).

// Bibliothèques spécifiques au microcontrôleur
#include <xc.h>           // Gestion des registres spécifiques au microcontrôleur.
#include <sys/attribs.h>  // Gestion des niveaux de priorité des interruptions.

// Définitions spécifiques au système
#include "system_definitions.h" // Définitions matérielles et systèmes.
#include <GenericTypeDefs.h>    // Définitions génériques des types.

// Fichiers spécifiques au projet
#include "app.h"               // Déclarations des fonctions applicatives.
#include "GesFifoTh32.h"       // Gestion des buffers FIFO.
#include "Mc32gest_RS232.h"    // Fonctions spécifiques à la communication RS232.
#include "gestPWM.h"           // Gestion des signaux PWM.
#include "Mc32CalCrc16.h"      // Calculs CRC pour la vérification des données.

// Struct pour émission des messages
StruMess TxMess; // Déclaration d'une structure pour gérer les messages à transmettre.
// Struct pour réception des messages
StruMess RxMess; // Déclaration d'une structure pour les messages reçus.

int8_t fifoRX[FIFO_RX_SIZE]; // Buffer circulaire pour stocker les données reçues (FIFO RX).
// Déclaration du descripteur du FIFO de réception
S_fifo descrFifoRX; // Structure pour décrire les paramètres du FIFO RX.

int8_t fifoTX[FIFO_TX_SIZE]; // Buffer circulaire pour stocker les données à transmettre (FIFO TX).
// Déclaration du descripteur du FIFO d'émission
S_fifo descrFifoTX; // Structure pour décrire les paramètres du FIFO TX.

/**
 * @brief Initialise les buffers FIFO et configure le signal RTS.
 * 
 * @details Cette fonction initialise les descripteurs des buffers FIFO pour la 
 *          réception et l'émission de données série. Elle configure également
 *          le signal RTS pour bloquer temporairement l'émission externe.
 * 
 * @param[in] void Aucun paramètre requis.
 * 
 * @return void Aucun retour. La fonction met à jour les structures globales.
 */
void InitFifoComm(void)
{
    // Initialise le FIFO RX avec la taille et le buffer associés
    InitFifo(&descrFifoRX, FIFO_RX_SIZE, fifoRX, 0);

    // Initialise le FIFO TX avec la taille et le buffer associés
    InitFifo(&descrFifoTX, FIFO_TX_SIZE, fifoTX, 0);

    // Configure le signal RTS pour bloquer temporairement l'émission externe
    RS232_RTS = 1;
}

/**
 * @brief Vide les buffers FIFO RX et TX et désactive l'émission externe.
 * 
 * @details Cette fonction nettoie les données résiduelles dans les buffers FIFO de réception (RX)
 *          et d'émission (TX). Elle configure également le signal RTS pour bloquer
 *          temporairement l'émission de l'autre appareil.
 * 
 * @param[in] void Aucun paramètre requis.
 * 
 * @return void Aucun retour. Les buffers FIFO sont nettoyés et l'émission est bloquée.
 */
/**
 * @brief Vide les FIFO RX/TX et désactive l'émission externe lors du débranchement du câble.
 * @details Cette fonction est appelée une seule fois lorsqu?un événement de débranchement
 *          du câble est détecté. Elle ne perturbe pas les données en local.
 */
void HandleCableDisconnection(void) {
    // Réinitialiser les FIFO RX et TX
    ResetFifo(&descrFifoRX);
    ResetFifo(&descrFifoTX);

    // Désactiver l'émission externe
    RS232_RTS = 1; // Bloque la réception par l'autre appareil

    // Indication visuelle ou autre, si nécessaire
    BSP_LEDOff(BSP_LED_6); // Éteindre LED de communication
}
/**
 * @brief Traite la réception des messages et met à jour les paramètres PWM si un message valide est reçu.
 * 
 * @details Cette fonction lit les données depuis la FIFO RX, vérifie l'intégrité du message via un calcul CRC
 *          et met à jour les paramètres PWM si le message est valide. En cas d'erreurs répétées, elle vide
 *          les buffers et bascule en mode local.
 * 
 * @param[in,out] pData Pointeur vers la structure contenant les paramètres de configuration PWM.
 * 
 * @return int Statut de la communication :
 *             - LOCAL (0) : Pas de message reçu ou trop d'erreurs.
 *             - REMOTE (1) : Message reçu et validé, données mises à jour.
 */
int GetMessage(S_pwmSettings *pData)
{
    static int CommStatus = LOCAL;      // Statut de la communication (LOCAL ou REMOTE).
    static uint8_t NbMessError = 10;   // Compteur d'erreurs consécutives.
    uint8_t NbCharToRead = 0;          // Nombre de caractères disponibles dans le FIFO RX.
    U_manip16 Crc;                     // Union pour le calcul et la validation du CRC.
    uint16_t CrcVal = CRCINIT;         // Initialisation du CRC avec une valeur prédéfinie.
    static bool wasCableConnected = true; // Indique si le câble était connecté précédemment
    static bool disconnectionHandled = false; // Indique si la déconnexion a déjà été gérée

    // Obtient le nombre de caractères disponibles dans le FIFO RX
    NbCharToRead = GetReadSize(&descrFifoRX);

    // Vérifie si le FIFO contient suffisamment de caractères pour un message complet
    if (NbCharToRead >= MESS_SIZE) 
    {
        // Lit le premier caractère (code de début) dans la structure RxMess
        GetCharFromFifo(&descrFifoRX, &RxMess.Start);

        // Vérifie si le code de début est valide
        if (RxMess.Start == STX_CODE) 
        {
            // Lit les données du message : vitesse, angle et CRC
            GetCharFromFifo(&descrFifoRX, &RxMess.Speed);
            GetCharFromFifo(&descrFifoRX, &RxMess.Angle);
            GetCharFromFifo(&descrFifoRX, &RxMess.MsbCrc);
            GetCharFromFifo(&descrFifoRX, &RxMess.LsbCrc);

            // Stocke les valeurs CRC dans l'union
            Crc.shl.Msb = RxMess.MsbCrc;
            Crc.shl.Lsb = RxMess.LsbCrc;

            // Met à jour le CRC calculé avec les données du message
            CrcVal = updateCRC16(CrcVal, STX_CODE);
            CrcVal = updateCRC16(CrcVal, RxMess.Speed);
            CrcVal = updateCRC16(CrcVal, RxMess.Angle);

            // Compare le CRC calculé avec celui reçu
            if (Crc.Val == CrcVal) 
            {
                // Mise à jour des paramètres PWM avec les valeurs du message
                pData->SpeedSetting = RxMess.Speed;
                pData->absSpeed = abs(RxMess.Speed);
                pData->AngleSetting = RxMess.Angle;
                pData->absAngle = abs(RxMess.Angle);

                // Réinitialise le compteur d'erreurs
                NbMessError = 0;

                // Allume une LED pour indiquer un message valide
                BSP_LEDOn(BSP_LED_6);
            } 
            else 
            {
                // Incrémente le compteur d'erreurs et éteint la LED pour signaler une erreur CRC
                NbMessError++;
                BSP_LEDOff(BSP_LED_6);
            }
        } 
        else 
        {
            // Incrémente le compteur d'erreurs si le code de début est incorrect
            NbMessError++;
        }
    } 
    else 
    {
        // Incrémente le compteur d'erreurs si le message est incomplet
        NbMessError++;
    }

    // Détection de déconnexion (si trop d'erreurs)
    if (NbMessError >= NBR_MESS_ERROR) {
        if (!disconnectionHandled) {
            HandleCableDisconnection(); // Appelé une seule fois
            disconnectionHandled = true; // Marque la déconnexion comme gérée
        }
        wasCableConnected = false; // Marque le câble comme débranché
        CommStatus = LOCAL;        // Passe en mode local
    } else {
        // Réinitialise les flags si la connexion revient
        if (!wasCableConnected) {
            wasCableConnected = true;      // Marque le câble comme reconnecté
            disconnectionHandled = false; // Réinitialise la gestion de déconnexion
        }
        CommStatus = REMOTE; // Continue en mode distant
    }
    
    // Gestion du contrôle de flux en fonction de l'espace disponible dans le FIFO RX
    if (GetWriteSpace(&descrFifoRX) >= (2 * MESS_SIZE)) 
    {
        // Active le signal RTS pour autoriser l'émission par l'autre appareil
        RS232_RTS = 0;
    }

    // Retourne le statut de la communication
    return CommStatus;
}


/**
 * @brief Envoie un message contenant les paramètres PWM via la FIFO de transmission.
 * 
 * @details Cette fonction prépare les données à transmettre (code de début, vitesse, angle et CRC),
 *          les insère dans la FIFO TX, et active les interruptions de transmission si nécessaire.
 *          Elle vérifie également si suffisamment d'espace est disponible dans la FIFO pour le message.
 * 
 * @param[in] pData Pointeur vers la structure contenant les paramètres de configuration PWM.
 * 
 * @return void Aucun retour. Le message est ajouté à la FIFO et prêt pour l'envoi.
 */
void SendMessage(S_pwmSettings *pData)
{
    int16_t FreeSize;             // Taille de l'espace disponible dans la FIFO TX.
    uint16_t CrcVal = CRCINIT;    // Initialisation du CRC avec une valeur prédéfinie.
    U_manip16 Crc;                // Union pour le calcul et la validation du CRC.

    // Vérifie l'espace libre disponible dans la FIFO TX
    FreeSize = GetWriteSpace(&descrFifoTX);

    // Si suffisamment d'espace est disponible, préparer et ajouter les données au FIFO
    if (FreeSize >= MESS_SIZE)
    {
        // Calcul du CRC en utilisant les données du message
        CrcVal = updateCRC16(CrcVal, STX_CODE);
        CrcVal = updateCRC16(CrcVal, pData->SpeedSetting);
        CrcVal = updateCRC16(CrcVal, pData->AngleSetting);

        // Stocke le CRC calculé dans l'union locale
        Crc.Val = CrcVal;

        // Prépare le message à transmettre
        TxMess.Start = STX_CODE;             // Code de début.
        TxMess.Speed = pData->SpeedSetting;  // Vitesse.
        TxMess.Angle = pData->AngleSetting;  // Angle.
        TxMess.MsbCrc = Crc.shl.Msb;         // Octet supérieur du CRC.
        TxMess.LsbCrc = Crc.shl.Lsb;         // Octet inférieur du CRC.

        // Ajoute les données dans la FIFO TX
        PutCharInFifo(&descrFifoTX, TxMess.Start);
        PutCharInFifo(&descrFifoTX, TxMess.Speed);
        PutCharInFifo(&descrFifoTX, TxMess.Angle);
        PutCharInFifo(&descrFifoTX, TxMess.MsbCrc);
        PutCharInFifo(&descrFifoTX, TxMess.LsbCrc);
    }

    // Met à jour l'espace libre après l'ajout du message
    FreeSize = GetWriteSpace(&descrFifoTX);

    // Active l'interruption TX si le signal CTS est bas et s'il reste des données à transmettre
    if ((RS232_CTS == 0) && (FreeSize > 0))
    {
        // Active l'interruption de transmission pour gérer l'envoi
        PLIB_INT_SourceEnable(INT_ID_0, INT_SOURCE_USART_1_TRANSMIT);
    }
}

/**
 * @brief Interruption pour la gestion des événements de l'USART 1 (RX, TX, erreurs).
 * 
 * @details Cette fonction gère les interruptions liées à l'USART 1, couvrant :
 *          1. La gestion des erreurs de réception (parité, framing, overrun).
 *          2. La réception des données (transfert FIFO hardware -> FIFO software RX).
 *          3. La transmission des données (transfert FIFO software TX -> FIFO hardware).
 * 
 * @param[in] void Aucun paramètre requis.
 * 
 * @return void Aucun retour. Les données sont traitées et les interruptions sont gérées.
 */
void __ISR(_UART_1_VECTOR, ipl5AUTO) _IntHandlerDrvUsartInstance0(void) 
{
    USART_ERROR UsartStatus;       // État des erreurs détectées sur l'USART.
    static int8_t CharUsartToFifo; // Donnée reçue depuis le UART à transférer dans la FIFO RX.
    static int8_t TxData;          // Donnée à transmettre depuis la FIFO TX.
    uint8_t BuffSoftSize = 0;      // Taille des données présentes dans la FIFO TX (software).
    bool BuffHardFull = false;     // Indicateur d'état du buffer hardware de transmission (plein ou non).

    // Indique le début de l'interruption avec une LED.
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

    // 2. Gestion des données RX (réception)
    if (PLIB_INT_SourceFlagGet(INT_ID_0, INT_SOURCE_USART_1_RECEIVE) && 
        PLIB_INT_SourceIsEnabled(INT_ID_0, INT_SOURCE_USART_1_RECEIVE)) 
    {
        // Récupère l'état des erreurs sur la réception.
        UsartStatus = PLIB_USART_ErrorsGet(USART_ID_1);

        // Vérifie s'il n'y a pas d'erreurs (parité, framing, overrun).
        if ((UsartStatus & (USART_ERROR_PARITY | USART_ERROR_FRAMING | USART_ERROR_RECEIVER_OVERRUN)) == 0) 
        {
            // Lecture des données tant qu'elles sont disponibles dans le buffer hardware RX.
            while (PLIB_USART_ReceiverDataIsAvailable(USART_ID_1)) 
            {
                CharUsartToFifo = PLIB_USART_ReceiverByteReceive(USART_ID_1); // Récupère une donnée.
                PutCharInFifo(&descrFifoRX, CharUsartToFifo);                 // Ajoute la donnée dans la FIFO RX.
            }

            // Indique qu'une donnée a été reçue en inversant l'état de LED4.
            LED4_W = !LED4_R;

            // Efface le drapeau d'interruption RX.
            PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_USART_1_RECEIVE);
        } 
        else 
        {
            // Gestion spécifique des erreurs d'overrun.
            if ((UsartStatus & USART_ERROR_RECEIVER_OVERRUN) == USART_ERROR_RECEIVER_OVERRUN) {
                PLIB_USART_ReceiverOverrunErrorClear(USART_ID_1);
            }
        }

        // Contrôle de flux pour la réception.
        if (GetWriteSpace(&descrFifoRX) >= (2 * MESS_SIZE)) {
            RS232_RTS = 0; // Autorise l'émission par l'autre appareil.
        } else {
            RS232_RTS = 1; // Bloque l'émission.
        }
    }

    // 3. Gestion des données TX (transmission)
    if (PLIB_INT_SourceFlagGet(INT_ID_0, INT_SOURCE_USART_1_TRANSMIT) && 
        PLIB_INT_SourceIsEnabled(INT_ID_0, INT_SOURCE_USART_1_TRANSMIT)) 
    {
        // Lit la taille disponible dans la FIFO TX (software) et l'état du buffer hardware TX.
        BuffSoftSize = GetReadSize(&descrFifoTX);
        BuffHardFull = PLIB_USART_TransmitterBufferIsFull(USART_ID_1);

        // Vérifie si le signal CTS est bas (autorisation d'émettre).
        if (RS232_CTS == 0) 
        {
            // Tant que des données sont disponibles et que le buffer hardware n'est pas plein.
            while (RS232_CTS == 0 && BuffSoftSize > 0 && BuffHardFull == false) 
            {
                GetCharFromFifo(&descrFifoTX, &TxData); // Récupère une donnée depuis la FIFO TX.
                PLIB_USART_TransmitterByteSend(USART_ID_1, TxData); // Envoie la donnée.

                // Met à jour les indicateurs après l'envoi.
                BuffSoftSize = GetReadSize(&descrFifoTX);
                BuffHardFull = PLIB_USART_TransmitterBufferIsFull(USART_ID_1);
            }
        } 
        else 
        {
            // Désactive l'émetteur si CTS est haut (surcharge évitée).
            PLIB_USART_TransmitterDisable(USART_ID_1);
        }

        // Inverse l'état de LED5 pour indiquer une transmission.
        LED5_W = !LED5_R;

        // Désactive l'interruption TX si aucune donnée n'est disponible.
        PLIB_INT_SourceDisable(INT_ID_0, INT_SOURCE_USART_1_TRANSMIT);

        // Efface le drapeau d'interruption TX.
        PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_USART_1_TRANSMIT);
    }

    // Éteint LED3 pour indiquer la fin de l'interruption.
    LED3_W = 0;
}