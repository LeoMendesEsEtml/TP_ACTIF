// Mc32Gest_RS232.C
// Canevas manipulatio TP2 RS232 SLO2 2017-18
// Fonctions d'émission et de réception des message
// CHR 20.12.2016 ajout traitement int error
// CHR 22.12.2016 evolution des marquers observation int Usart
// SCA 03.01.2018 nettoyé réponse interrupt pour ne laisser que les 3 ifs

// ======= Inclusions des bibliothèques standard et spécifiques au microcontrôleur =======
#include <xc.h>                // Bibliothèque spécifique au compilateur XC pour le PIC32
#include <sys/attribs.h>       // Gestion des attributs d'interruptions et de priorité
#include <stdbool.h>           // Définition du type booléen standard (true/false)
#include <stdlib.h>            // Fonctions standards de gestion mémoire et conversion

// ======= Inclusions liées à la configuration système et aux définitions globales =======
#include "system_definitions.h" // Définitions spécifiques au projet et configuration système
#include <GenericTypeDefs.h>     // Définitions de types génériques pour le développement embarqué

// ======= Inclusions des modules applicatifs spécifiques =======
#include "app.h"               // Fichier principal de l'application
#include "GesFifoTh32.h"       // Gestion des files FIFO pour le traitement des données
#include "Mc32gest_RS232.h"    // Gestion de la communication série RS232
#include "gestPWM.h"           // Gestion du signal PWM pour les moteurs et servomoteurs
#include "Mc32CalCrc16.h"      // Calcul de CRC16 pour validation des transmissions


/// ======= Structures pour la gestion des messages =======
// Structure pour l'émission des messages
StruMess TxMess;

// Structure pour la réception des messages
StruMess RxMess;

// ======= FIFO de réception =======
int8_t fifoRX[FIFO_RX_SIZE];  // Buffer FIFO pour la réception des messages
S_fifo descrFifoRX;           // Descripteur du FIFO de réception

// ======= FIFO d'émission =======
int8_t fifoTX[FIFO_TX_SIZE];  // Buffer FIFO pour l'émission des messages
S_fifo descrFifoTX;           // Descripteur du FIFO d'émission

/**
 * @brief Initialise les FIFO de communication et configure le signal RTS.
 * 
 * Cette fonction initialise :
 * - Le FIFO de réception avec son descripteur et son buffer associé.
 * - Le FIFO d'émission avec son descripteur et son buffer associé.
 * - Le signal RTS pour interdire temporairement l'émission par l'autre périphérique.
 * 
 * @return void Aucune valeur de retour.
 */
void InitFifoComm(void) {
    // Initialisation du FIFO de réception
    InitFifo(&descrFifoRX, FIFO_RX_SIZE, fifoRX, 0);

    // Initialisation du FIFO d'émission
    InitFifo(&descrFifoTX, FIFO_TX_SIZE, fifoTX, 0);

    // Initialisation du signal RTS
    RS232_RTS = 1; // Interdit l'émission par l'autre périphérique

} // Fin InitFifoComm

/**
 * @brief Gère la déconnexion du câble série en réinitialisant les FIFO et le signal RTS.
 * 
 * Cette fonction effectue les actions suivantes :
 * - Réinitialisation du FIFO de réception.
 * - Réinitialisation du FIFO d'émission.
 * - Configuration du signal RTS pour autoriser l'émission du périphérique distant.
 * 
 * @return void Aucune valeur de retour.
 */
void HandleCableDisconnection(void) {
    // Réinitialisation du FIFO de réception
    ResetFifo(&descrFifoRX);

    // Réinitialisation du FIFO d'émission
    ResetFifo(&descrFifoTX);

    // Configuration du signal RTS pour autoriser l'émission du périphérique distant
    RS232_RTS = 0;

} // Fin HandleCableDisconnection


/**
 * @brief Traite la réception de messages et met à jour les données si un message valide est reçu.
 * 
 * @param[in,out] pData Pointeur vers la structure contenant les paramètres de configuration PWM.
 * @return int Statut de la communication :
 *             - 0 : Pas de message reçu (local, données non modifiées).
 *             - 1 : Message reçu (remote, données mises à jour).
 */
int GetMessage(S_pwmSettings *pData) {
    static bool wasCableConnected = true; // Indique si le câble était connecté précédemment

    // Initialise le statut de la communication (local par défaut)
    static int CommStatus = 0;

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
    if (NbCharToRead >= MESS_SIZE) {
        // Lit le premier caractère de la FIFO et le stocke dans la structure RxMess
        GetCharFromFifo(&descrFifoRX, &RxMess.Start);

        // Vérifie si le caractère reçu est un code de début valide
        if (RxMess.Start == STX_CODE) {
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
            if (Crc.Val == CrcVal) {
                // Met à jour la vitesse dans les paramètres PWM
                pData->SpeedSetting = RxMess.Speed;
                pData->absSpeed = abs(RxMess.Speed);

                // Met à jour l'angle dans les paramètres PWM
                pData->AngleSetting = RxMess.Angle;
                pData->absAngle = abs(RxMess.Angle - 90);

                // Réinitialise le nombre de caractères à lire
                NbCharToRead = 0;

                // Réinitialise le compteur d'erreurs de message
                NbMessError = 0;
            } else {
                // Incrémente le compteur d'erreurs de message
                NbMessError++;
                /* Indique que le CRC est faux */
                BSP_LEDToggle(BSP_LED_6);
            }
        }

    } else {
        NbMessError++;
    }



    // ---- Détection de la perte de connexion ----
    if (NbMessError >= NBR_MESS_ERROR) {
        if (wasCableConnected) { // Si le câble vient d'être débranché
            //HandleCableDisconnection(); // Reset FIFO et stop RS232
            wasCableConnected = false; // Marque le câble comme débranché
        }
        CommStatus = LOCAL;
        if (NbMessError == 0xFF) {
            NbMessError = NBR_MESS_ERROR;
        }
    }        // ---- Détection de la reconnexion ----
    else if (!wasCableConnected) { // Si les messages reviennent, le câble est reconnecté
        wasCableConnected = true; // Marque le câble comme connecté
        CommStatus = REMOTE;
    } else {
        CommStatus = REMOTE;
    }

    // Vérifie l'espace disponible dans la FIFO RX pour gérer le contrôle de flux
    if (GetWriteSpace(&descrFifoRX) >= (2 * MESS_SIZE)) {
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
void SendMessage(S_pwmSettings *pData) {
    // Variable locale pour stocker la taille libre dans la FIFO de transmission
    int16_t FreeSize;

    // Initialisation de la valeur CRC avec une constante prédéfinie
    uint16_t CrcVal = CRCINIT;

    // Union pour le calcul et la validation du CRC
    U_manip16 Crc;

    // Obtient l'espace libre disponible dans la FIFO TX
    FreeSize = GetWriteSpace(&descrFifoTX);

    // Vérifie si l'espace libre est suffisant pour un message complet
    if (FreeSize >= MESS_SIZE) {
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

    if (GetReadSize(&descrFifoTX) > 0) {
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
void __ISR(_UART_1_VECTOR, ipl5AUTO) _IntHandlerDrvUsartInstance0(void) {
    // Déclaration pour gérer les erreurs USART
    USART_ERROR UsartStatus;
    uint8_t nDataBefore = GetReadSize(&descrFifoTX);
    uint8_t nDataAfter = nDataBefore;
    bool hwFull = false;
    bool sentSomething = false;
    static int8_t CharUsartToFifo; // Donnée reçue depuis le UART à transférer dans la FIFO


    // Allume LED3 pour indiquer le début de l'interruption
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

    // 2. Gestion des données RX (réception)
    if (PLIB_INT_SourceFlagGet(INT_ID_0, INT_SOURCE_USART_1_RECEIVE) &&
            PLIB_INT_SourceIsEnabled(INT_ID_0, INT_SOURCE_USART_1_RECEIVE)) {

        // Vérifie s'il y a des erreurs de réception (parité, framing, overrun)
        UsartStatus = PLIB_USART_ErrorsGet(USART_ID_1);

        if ((UsartStatus & (USART_ERROR_PARITY | USART_ERROR_FRAMING | USART_ERROR_RECEIVER_OVERRUN)) == 0) {
            // Lecture des données tant qu'elles sont disponibles dans le buffer hardware RX
            while (PLIB_USART_ReceiverDataIsAvailable(USART_ID_1)) {
                // Récupère un caractère du buffer hardware
                CharUsartToFifo = PLIB_USART_ReceiverByteReceive(USART_ID_1);
                // Ajoute ce caractère dans la FIFO software RX
                PutCharInFifo(&descrFifoRX, CharUsartToFifo);
            }

            // --- Flow control update: if we have plenty of space, allow more data ---
            if (GetWriteSpace(&descrFifoRX) >= 2 * MESS_SIZE) {
                RS232_RTS = 0; // Enough space, let the other side send
            } else {
                RS232_RTS = 1; // Getting full, block the other side
            }
            LED4_W = !LED4_R; // Toggle Led4
            // Efface le drapeau d'interruption RX (plus de données à lire)
            PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_USART_1_RECEIVE);
        }
        else {
            // Suppression des erreurs spécifiques (notamment overrun)
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
    // Éteint LED3 pour indiquer la fin de l'interruption
    LED3_W = 0;
}