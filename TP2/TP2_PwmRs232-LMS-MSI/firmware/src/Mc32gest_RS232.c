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
 * Cette fonction effectue les actions suivantes :
 * - Initialise le FIFO de réception avec son descripteur et son buffer dédié pour stocker les données entrantes.
 * - Initialise le FIFO d'émission avec son descripteur et son buffer dédié pour stocker les données à envoyer.
 * - Configure le signal RTS (Request to Send) à l'état **haut** pour bloquer temporairement l'émission du périphérique distant.
 * 
 * @return void Aucune valeur de retour.
 */
void InitFifoComm(void) {
    // Initialise le FIFO de réception pour stocker les messages entrants
    InitFifo(&descrFifoRX, FIFO_RX_SIZE, fifoRX, 0);

    // Initialise le FIFO d'émission pour stocker les messages à transmettre
    InitFifo(&descrFifoTX, FIFO_TX_SIZE, fifoTX, 0);

    // Place RTS à 1 pour interdire temporairement l'envoi par le périphérique distant
    RS232_RTS = 1;
} // Fin de InitFifoComm


/**
 * @brief Réinitialise l'état de la communication série après une déconnexion.
 * 
 * Cette fonction effectue les actions suivantes :
 * - Vide le FIFO de réception pour éviter les données corrompues après la perte de connexion.
 * - Vide le FIFO d'émission pour éviter l'envoi de messages obsolètes.
 * - Abaisse le signal RTS afin d'indiquer au périphérique distant qu'il peut émettre de nouvelles données.
 * 
 * @return void Aucune valeur de retour.
 */
void HandleCableDisconnection(void) {
    // Réinitialise le FIFO de réception pour éviter toute donnée résiduelle erronée
    ResetFifo(&descrFifoRX);

    // Réinitialise le FIFO d'émission pour éviter l'envoi de données obsolètes
    ResetFifo(&descrFifoTX);

    // Abaisse le signal RTS (Request to Send) pour permettre au périphérique distant d'envoyer des messages
    RS232_RTS = 0;
} // Fin de HandleCableDisconnection




/**
 * @brief Traite la réception de messages et met à jour les données si un message valide est reçu.
 * 
 * @param[in,out] pData Pointeur vers la structure contenant les paramètres de configuration PWM.
 * @return int Statut de la communication :
 *             - 0 : Aucun message valide reçu (mode local activé).
 *             - 1 : Message valide reçu (mode distant activé).
 */
int GetMessage(S_pwmSettings *pData) {
    static bool wasCableConnected = true; // Indique si le câble était connecté lors du dernier appel

    static int CommStatus = 0; // Initialise le statut de la communication à LOCAL

    static uint8_t NbMessError = 0; // Initialise le compteur d'erreurs de réception

    static uint8_t NbCharToRead = 0; // Initialise le nombre de caractères à lire dans le FIFO RX

    U_manip16 Crc; // Déclare une union pour stocker le CRC

    uint16_t CrcVal = CRCINIT; // Initialise la valeur du CRC avec la valeur prédéfinie

    NbCharToRead = GetReadSize(&descrFifoRX); // Vérifie combien de caractères sont disponibles dans le FIFO RX

    if (NbCharToRead >= MESS_SIZE) { // Vérifie si un message complet est disponible
        GetCharFromFifo(&descrFifoRX, &RxMess.Start); // Récupère le premier caractère du message

        if (RxMess.Start == STX_CODE) { // Vérifie si le message commence bien par l'identifiant attendu
            GetCharFromFifo(&descrFifoRX, &RxMess.Speed); // Récupère la vitesse du message

            GetCharFromFifo(&descrFifoRX, &RxMess.Angle); // Récupère l'angle du message

            GetCharFromFifo(&descrFifoRX, &RxMess.MsbCrc); // Récupère le MSB du CRC

            Crc.shl.Msb = RxMess.MsbCrc; // Stocke le MSB du CRC dans la structure

            GetCharFromFifo(&descrFifoRX, &RxMess.LsbCrc); // Récupère le LSB du CRC

            Crc.shl.Lsb = RxMess.LsbCrc; // Stocke le LSB du CRC dans la structure

            CrcVal = updateCRC16(CrcVal, STX_CODE); // Met à jour le CRC avec le code de début

            CrcVal = updateCRC16(CrcVal, RxMess.Speed); // Met à jour le CRC avec la vitesse

            CrcVal = updateCRC16(CrcVal, RxMess.Angle); // Met à jour le CRC avec l'angle

            if (Crc.Val == CrcVal) { // Vérifie si le CRC calculé correspond au CRC reçu
                pData->SpeedSetting = RxMess.Speed; // Met à jour la vitesse du PWM

                pData->absSpeed = abs(RxMess.Speed); // Met à jour la vitesse absolue

                pData->AngleSetting = RxMess.Angle; // Met à jour l'angle du PWM

                pData->absAngle = abs(RxMess.Angle - 90); // Met à jour l'angle absolu en appliquant un décalage

                NbCharToRead = 0; // Réinitialise le nombre de caractères à lire

                NbMessError = 0; // Réinitialise le compteur d'erreurs
            } else { // Si le CRC est invalide
                NbMessError++; // Incrémente le compteur d'erreurs

                BSP_LEDToggle(BSP_LED_6); // Bascule la LED 6 pour indiquer une erreur CRC
            }
        }
    } else { // Si un message complet n'est pas disponible
        NbMessError++; // Incrémente le compteur d'erreurs
    }

    if (NbMessError >= NBR_MESS_ERROR) { // Vérifie si le nombre d'erreurs atteint la limite
        if (wasCableConnected) { // Vérifie si le câble était précédemment connecté
            //HandleCableDisconnection(); // Réinitialise les FIFO et arrête le RS232

            wasCableConnected = false; // Marque le câble comme déconnecté
        }

        CommStatus = LOCAL; // Passe en mode local

        if (NbMessError == 0xFF) { // Vérifie si le compteur d'erreurs atteint sa valeur maximale
            NbMessError = NBR_MESS_ERROR; // Réinitialise à la valeur limite pour éviter un dépassement
        }
    } else if (!wasCableConnected) { // Vérifie si le câble a été reconnecté après une perte de connexion
        wasCableConnected = true; // Marque le câble comme reconnecté

        CommStatus = REMOTE; // Passe en mode distant
    } else { // Si aucune erreur critique n'a été détectée
        CommStatus = REMOTE; // Reste en mode distant
    }

    if (GetWriteSpace(&descrFifoRX) >= (2 * MESS_SIZE)) { // Vérifie l'espace disponible dans la FIFO RX
        RS232_RTS = 0; // Active le signal RTS pour autoriser l'émission du périphérique distant
    }

    return CommStatus; // Retourne le statut de la communication
}

/**
 * @brief Envoie un message contenant les paramètres PWM via une FIFO de transmission.
 *
 * @param[in] pData Pointeur vers la structure contenant les paramètres de configuration PWM.
 */
void SendMessage(S_pwmSettings *pData) {
    int16_t FreeSize; // Variable locale pour stocker la taille libre dans la FIFO de transmission

    uint16_t CrcVal = CRCINIT; // Initialise le CRC avec la valeur par défaut définie pour le protocole

    U_manip16 Crc; // Union permettant de manipuler le CRC sous forme d'octets séparés

    FreeSize = GetWriteSpace(&descrFifoTX); // Vérifie l'espace libre disponible dans la FIFO TX

    if (FreeSize >= MESS_SIZE) { // Vérifie si un message complet peut être stocké dans la FIFO
        CrcVal = updateCRC16(CrcVal, STX_CODE); // Ajoute le code de début au calcul du CRC
        CrcVal = updateCRC16(CrcVal, pData->SpeedSetting); // Ajoute la vitesse au calcul du CRC
        CrcVal = updateCRC16(CrcVal, pData->AngleSetting); // Ajoute l'angle au calcul du CRC

        Crc.Val = CrcVal; // Stocke le CRC calculé dans l'union pour une manipulation plus simple

        TxMess.Start = STX_CODE; // Initialise l'identifiant de début du message
        TxMess.Speed = pData->SpeedSetting; // Stocke la vitesse actuelle dans le message
        TxMess.Angle = pData->AngleSetting; // Stocke l'angle actuel dans le message
        TxMess.MsbCrc = Crc.shl.Msb; // Stocke le MSB du CRC dans la structure du message
        TxMess.LsbCrc = Crc.shl.Lsb; // Stocke le LSB du CRC dans la structure du message

        PutCharInFifo(&descrFifoTX, TxMess.Start); // Ajoute le code de début du message dans la FIFO TX
        PutCharInFifo(&descrFifoTX, TxMess.Speed); // Ajoute la vitesse dans la FIFO TX
        PutCharInFifo(&descrFifoTX, TxMess.Angle); // Ajoute l'angle dans la FIFO TX
        PutCharInFifo(&descrFifoTX, TxMess.MsbCrc); // Ajoute l'octet MSB du CRC dans la FIFO TX
        PutCharInFifo(&descrFifoTX, TxMess.LsbCrc); // Ajoute l'octet LSB du CRC dans la FIFO TX
    }

    FreeSize = GetWriteSpace(&descrFifoTX); // Met à jour l'espace libre disponible après l'insertion

    if (GetReadSize(&descrFifoTX) > 0) { // Vérifie s'il y a des données à transmettre
        PLIB_INT_SourceEnable(INT_ID_0, INT_SOURCE_USART_1_TRANSMIT); // Active l'interruption TX pour envoyer les données
    }
}


/**
 * @brief Gestion des interruptions de l'USART (RX, TX, erreurs).
 * 
 * @details Cette fonction gère les événements liés à l'USART 1 :
 * - Traitement des erreurs de réception.
 * - Réception des données (FIFO hardware -> FIFO software).
 * - Transmission des données (FIFO software -> FIFO hardware).
 */
void __ISR(_UART_1_VECTOR, ipl5AUTO) _IntHandlerDrvUsartInstance0(void) {
    USART_ERROR usartErrorStatus; // Stocke le statut des erreurs USART
    uint8_t txFifoDataCountBefore = GetReadSize(&descrFifoTX); // Nombre de données TX avant transmission
    uint8_t txFifoDataCountAfter = txFifoDataCountBefore; // Suivi du nombre de données TX après transmission
    bool isTxHardwareBufferFull = false; // Indique si le buffer TX matériel est plein
    bool hasSentData = false; // Indique si au moins une donnée a été envoyée
    static int8_t receivedUartChar; // Stocke le dernier caractère reçu de l'USART

    LED3_W = 1; // Allume la LED3 pour indiquer qu'une interruption est en cours

    // ==== 1. Gestion des erreurs USART ====
    if (PLIB_INT_SourceFlagGet(INT_ID_0, INT_SOURCE_USART_1_ERROR) &&
        PLIB_INT_SourceIsEnabled(INT_ID_0, INT_SOURCE_USART_1_ERROR)) {
        
        PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_USART_1_ERROR); // Efface le drapeau d'erreur

        // Vidange le buffer RX hardware pour éviter les erreurs résiduelles
        while (PLIB_USART_ReceiverDataIsAvailable(USART_ID_1)) {
            PLIB_USART_ReceiverByteReceive(USART_ID_1);
        }
    }

    // ==== 2. Gestion de la réception des données RX ====
    if (PLIB_INT_SourceFlagGet(INT_ID_0, INT_SOURCE_USART_1_RECEIVE) &&
        PLIB_INT_SourceIsEnabled(INT_ID_0, INT_SOURCE_USART_1_RECEIVE)) {

        usartErrorStatus = PLIB_USART_ErrorsGet(USART_ID_1); // Récupération du statut d'erreur

        // Vérifie si aucune erreur de réception n'est détectée
        if (!(usartErrorStatus & (USART_ERROR_PARITY | USART_ERROR_FRAMING | USART_ERROR_RECEIVER_OVERRUN))) {
            // Lire les données du buffer RX tant qu'il y en a
            while (PLIB_USART_ReceiverDataIsAvailable(USART_ID_1)) {
                receivedUartChar = PLIB_USART_ReceiverByteReceive(USART_ID_1); // Récupère une donnée du buffer RX
                PutCharInFifo(&descrFifoRX, receivedUartChar); // Stocke la donnée dans la FIFO RX
            }

            // Mise à jour du contrôle de flux RTS en fonction de la place restante dans la FIFO RX
            if (GetWriteSpace(&descrFifoRX) >= 2 * MESS_SIZE) {
                RS232_RTS = 0; // Il y a assez d'espace, on autorise l'envoi depuis l'autre périphérique
            } else {
                RS232_RTS = 1; // FIFO RX proche de la saturation, on bloque l'émission du périphérique distant
            }

            LED4_W = !LED4_R; // Toggle LED4 pour indiquer une réception
            PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_USART_1_RECEIVE); // Efface le drapeau RX
        }
        else {
            // Gestion spécifique de l'erreur d'overrun si détectée
            if (usartErrorStatus & USART_ERROR_RECEIVER_OVERRUN) {
                PLIB_USART_ReceiverOverrunErrorClear(USART_ID_1);
            }
        }
    }

    // ==== 3. Gestion de la transmission des données TX ====
    if (PLIB_INT_SourceFlagGet(INT_ID_0, INT_SOURCE_USART_1_TRANSMIT) &&
        PLIB_INT_SourceIsEnabled(INT_ID_0, INT_SOURCE_USART_1_TRANSMIT)) {

        // Envoi des données tant que :
        // - Il reste des données à transmettre
        // - Le signal CTS permet la transmission
        // - Le buffer TX matériel n'est pas saturé
        while ((txFifoDataCountAfter > 0) && (RS232_CTS == 0) && !isTxHardwareBufferFull) {
            int8_t dataToSend; // Stocke la donnée à envoyer
            GetCharFromFifo(&descrFifoTX, &dataToSend); // Récupère une donnée de la FIFO TX
            PLIB_USART_TransmitterByteSend(USART_ID_1, dataToSend); // Envoie la donnée via l'USART

            txFifoDataCountAfter = GetReadSize(&descrFifoTX); // Met à jour le nombre de données restantes
            isTxHardwareBufferFull = PLIB_USART_TransmitterBufferIsFull(USART_ID_1); // Vérifie si le buffer TX est plein
            hasSentData = true; // Confirme qu'une donnée a été envoyée
        }

        // Si plus aucune donnée n'est disponible, on désactive l'interruption TX
        if (txFifoDataCountAfter == 0) {
            PLIB_INT_SourceDisable(INT_ID_0, INT_SOURCE_USART_1_TRANSMIT);
        } 
        else if (!hasSentData) { 
            // Si des données sont en attente mais n'ont pas pu être envoyées (CTS=1)
            // => Désactivation temporaire de l'interruption TX pour éviter des interruptions inutiles
            PLIB_INT_SourceDisable(INT_ID_0, INT_SOURCE_USART_1_TRANSMIT);
        }

        LED5_W = !LED5_R; // Toggle LED5 pour indiquer une transmission
        PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_USART_1_TRANSMIT); // Efface le drapeau TX
    }

    LED3_W = 0; // Éteint la LED3 pour indiquer la fin de l'interruption
}
