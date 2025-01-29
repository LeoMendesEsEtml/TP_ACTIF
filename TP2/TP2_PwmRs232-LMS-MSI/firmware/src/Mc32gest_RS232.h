#ifndef Mc32Gest_RS232_H
#define Mc32Gest_RS232_H
/*--------------------------------------------------------*/
// Mc32Gest_RS232.h
/*--------------------------------------------------------*/
// Description : Gestion spécialisée pour l'émission et la réception
//               des messages RS232 dans le cadre du TP2.
//
// Auteur       : C. HUBER
//
// Version      : V1.3
// Compilateur  : XC32 V1.42 + Harmony 1.08
//
/*--------------------------------------------------------*/

#include <stdint.h>
#include "GesFifoTh32.h"
#include "gestPWM.h"

/*--------------------------------------------------------*/
// Constantes et définitions associées à la communication
/*--------------------------------------------------------*/

#define CRCINIT 0xFFFF           // Valeur initiale pour le calcul CRC16-CCITT.
#define CHARSTAR 0xAA            // Caractère identifiant le début du message.
#define NBR_MESS_ERROR 10        // Nombre maximal d'erreurs de message avant de passer en mode local.
#define MESS_SIZE 5              // Taille d'un message complet en octets.
#define STX_CODE (-86)           // Code de départ du message (converti en int8_t).


// Tailles des FIFO pour réception et émission (supporte 4 messages complets chacun).
#define FIFO_RX_SIZE ((4 * MESS_SIZE) + 1)
#define FIFO_TX_SIZE ((4 * MESS_SIZE) + 1)

/*--------------------------------------------------------*/
// Structures et unions pour la gestion des messages
/*--------------------------------------------------------*/

/**
 * @brief Structure décrivant le format d'un message RS232.
 * 
 * @details Cette structure contient les champs nécessaires à un message :
 * - `Start` : Identifiant du début de message.
 * - `Speed` : Vitesse exprimée en entier signé.
 * - `Angle` : Angle exprimé en entier signé.
 * - `MsbCrc` : Octet de poids fort du CRC.
 * - `LsbCrc` : Octet de poids faible du CRC.
 */
typedef struct {
    int8_t Start;    // Identifiant du début du message.
    int8_t Speed;     // Vitesse.
    int8_t Angle;     // Angle.
    int8_t MsbCrc;   // Octet de poids fort du CRC.
    int8_t LsbCrc;   // Octet de poids faible du CRC.
} StruMess;

/**
 * @brief Union permettant une manipulation simplifiée des entiers 16 bits.
 * 
 * @details Permet un accès simultané à une représentation complète (uint16_t)
 * ou à une décomposition en octets (MSB et LSB).
 */
typedef union {
    uint16_t Val;          // Valeur entière 16 bits complète.
    struct {
        uint8_t Lsb;       // Octet de poids faible.
        uint8_t Msb;       // Octet de poids fort.
    } shl;                 // Structure pour décomposer l'entier.
} U_manip16;

/*--------------------------------------------------------*/
// Prototypes des fonctions
/*--------------------------------------------------------*/

/**
 * @brief Initialise les FIFO pour la réception et l'émission RS232.
 * 
 * @details Cette fonction configure les descripteurs des FIFO RX et TX et
 * initialise l'état du signal RTS (Ready To Send) à 1 (émission bloquée).
 */
void InitFifoComm(void);

/**
 * @brief Lit les paramètres PWM à partir des valeurs des ADC (moyennes glissantes).
 * @author LMS - VCO
 * @date 2025-01-02
 *
 * @param pData Pointeur vers une structure S_pwmSettings pour stocker les paramètres calculés.
 *
 * @details Cette fonction lit les résultats bruts des ADC, calcule les moyennes glissantes
 *          pour les canaux spécifiés, et met à jour les réglages de vitesse et d'angle
 *          dans la structure `pData`.
 */
void GPWM_GetSettings(S_pwmSettings *pData);

/**
 * @brief Récupère un message depuis la FIFO RX.
 * 
 * @param[in, out] pData Structure S_pwmSettings pour stocker les paramètres du message.
 * 
 * @return 
 * - `1` : Si un message valide est reçu et que les données sont mises à jour.
 * - `0` : Si aucun message valide n'est disponible (mode local par défaut).
 * 
 * @details La fonction analyse les données dans la FIFO RX, vérifie leur validité 
 * à l'aide du CRC, et met à jour les champs de la structure `pData`.
 */
int GetMessage(S_pwmSettings *pData);

/**
 * @brief Prépare et envoie un message dans la FIFO TX.
 * 
 * @param[in] pData Structure S_pwmSettings contenant les paramètres à transmettre.
 * 
 * @details La fonction vérifie s'il y a suffisamment d'espace libre dans la FIFO TX.
 * Si oui, elle formate le message avec un CRC valide et le dépose dans la FIFO.
 * Elle active ensuite l'interruption TX pour lancer l'émission.
 */
void SendMessage(S_pwmSettings *pData);

/*--------------------------------------------------------*/
// Descripteurs des FIFO externes
/*--------------------------------------------------------*/
extern S_fifo descrFifoRX;  // Descripteur de la FIFO RX (réception).
extern S_fifo descrFifoTX;  // Descripteur de la FIFO TX (émission).

#endif // Mc32Gest_RS232_H
