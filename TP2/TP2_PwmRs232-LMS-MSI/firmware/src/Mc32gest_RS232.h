#ifndef Mc32Gest_RS232_H
#define Mc32Gest_RS232_H
/*--------------------------------------------------------*/
// Mc32Gest_RS232.h
/*--------------------------------------------------------*/
// Description : Gestion sp�cialis�e pour l'�mission et la r�ception
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
// Constantes et d�finitions associ�es � la communication
/*--------------------------------------------------------*/

#define CRCINIT 0xFFFF           // Valeur initiale pour le calcul CRC16-CCITT.
#define NBR_MESS_ERROR 10        // Nombre maximal d'erreurs de message avant de passer en mode local.
#define MESS_SIZE 5              // Taille d'un message complet en octets.
#define STX_CODE (-86)           // Code de d�part du message (converti en int8_t).


// Tailles des FIFO pour r�ception et �mission (supporte 4 messages complets chacun).
#define FIFO_RX_SIZE ((4 * MESS_SIZE) + 1)
#define FIFO_TX_SIZE ((4 * MESS_SIZE) + 1)

/*--------------------------------------------------------*/
// Structures et unions pour la gestion des messages
/*--------------------------------------------------------*/

/**
 * @brief Structure d�crivant le format d'un message RS232.
 * 
 * @details Cette structure contient les champs n�cessaires � un message :
 * - `Start` : Identifiant du d�but de message.
 * - `Speed` : Vitesse exprim�e en entier sign�.
 * - `Angle` : Angle exprim� en entier sign�.
 * - `MsbCrc` : Octet de poids fort du CRC.
 * - `LsbCrc` : Octet de poids faible du CRC.
 */
typedef struct {
    int8_t Start;    // Identifiant du d�but du message.
    int8_t Speed;     // Vitesse.
    int8_t Angle;     // Angle.
    int8_t MsbCrc;   // Octet de poids fort du CRC.
    int8_t LsbCrc;   // Octet de poids faible du CRC.
} StruMess;

/**
 * @brief Union permettant une manipulation simplifi�e des entiers 16 bits.
 * 
 * @details Permet un acc�s simultan� � une repr�sentation compl�te (uint16_t)
 * ou � une d�composition en octets (MSB et LSB).
 */
typedef union {
    uint16_t Val;          // Valeur enti�re 16 bits compl�te.
    struct {
        uint8_t Lsb;       // Octet de poids faible.
        uint8_t Msb;       // Octet de poids fort.
    } shl;                 // Structure pour d�composer l'entier.
} U_manip16;

/*--------------------------------------------------------*/
// Prototypes des fonctions
/*--------------------------------------------------------*/

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
void InitFifoComm(void);

/**
 * @brief Vide les FIFO RX/TX et d�sactive l'�mission externe lors du d�branchement du c�ble.
 * @details Cette fonction est appel�e une seule fois lorsqu?un �v�nement de d�branchement
 *          du c�ble est d�tect�. Elle r�initialise uniquement les pointeurs des FIFO et bloque
 *          la r�ception par l'autre appareil.
 */
void HandleCableDisconnection(void);


/**
 * @brief R�cup�re un message depuis la FIFO RX.
 * 
 * @param[in, out] pData Structure S_pwmSettings pour stocker les param�tres du message.
 * 
 * @return 
 * - `1` : Si un message valide est re�u et que les donn�es sont mises � jour.
 * - `0` : Si aucun message valide n'est disponible (mode local par d�faut).
 * 
 * @details La fonction analyse les donn�es dans la FIFO RX, v�rifie leur validit� 
 * � l'aide du CRC, et met � jour les champs de la structure `pData`.
 */
int GetMessage(S_pwmSettings *pData);

/**
 * @brief Pr�pare et envoie un message dans la FIFO TX.
 * 
 * @param[in] pData Structure S_pwmSettings contenant les param�tres � transmettre.
 * 
 * @details La fonction v�rifie s'il y a suffisamment d'espace libre dans la FIFO TX.
 * Si oui, elle formate le message avec un CRC valide et le d�pose dans la FIFO.
 * Elle active ensuite l'interruption TX pour lancer l'�mission.
 */
void SendMessage(S_pwmSettings *pData);

/*--------------------------------------------------------*/
// Descripteurs des FIFO externes
/*--------------------------------------------------------*/
extern S_fifo descrFifoRX;  // Descripteur de la FIFO RX (r�ception).
extern S_fifo descrFifoTX;  // Descripteur de la FIFO TX (�mission).

#endif // Mc32Gest_RS232_H
