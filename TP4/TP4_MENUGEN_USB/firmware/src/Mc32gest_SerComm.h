#ifndef Mc32Gest_SERCOMM_H
#define Mc32Gest_SERCOMM_H
/*--------------------------------------------------------*/
// Mc32Gest_SerComm.h
/*--------------------------------------------------------*/
//	Description :	emission et reception specialisee
//			pour TP4 2015-2016
//
//	Auteur 		: 	C. HUBER
//
//	Version		:	V1.2
//	Compilateur	:	XC32 V1.40 + Harmony 1.06
//
/*--------------------------------------------------------*/

#include <stdint.h>
#include "DefMenuGen.h"

/*--------------------------------------------------------*/
// Prototypes des fonctions de communication série USB
/*--------------------------------------------------------*/

/**
 * @brief Prépare une trame texte à envoyer via USB CDC.
 * 
 * Cette fonction construit une chaîne de caractères formatée contenant
 * l?ensemble des paramètres actuels du générateur (forme, fréquence, amplitude,
 * offset) ainsi qu?un indicateur de sauvegarde.
 * 
 * @param USBSendBuffer Pointeur vers le tampon dans lequel la trame sera écrite.
 *                      Ce tampon doit avoir une taille suffisante pour contenir
 *                      toute la trame (64 octets minimum).
 * @param pParam Pointeur vers la structure contenant les paramètres du générateur.
 * @param Saved Booléen indiquant si une sauvegarde a été effectuée (true = oui, false = non).
 */
void SendMessage(int8_t *USBSendBuffer, S_ParamGen *pParam, bool Saved);

/**
 * @brief Analyse une trame reçue via USB CDC et met à jour les paramètres du générateur.
 * 
 * Cette fonction extrait les informations contenues dans une trame reçue
 * (sous forme de chaîne de caractères) et met à jour les champs correspondants
 * dans la structure S_ParamGen. Elle vérifie également si une demande de
 * sauvegarde est incluse.
 * 
 * @param USBReadBuffer Pointeur vers la trame reçue en entrée (chaîne ASCII).
 *                      Doit commencer par '!' et se terminer par '#'.
 * @param pParam Pointeur vers la structure à remplir avec les nouveaux paramètres.
 * @param SaveTodo Pointeur vers un booléen qui sera mis à true si la trame demande une sauvegarde (W=1).
 * 
 * @return true si le message est valide et a été correctement décodé, false sinon.
 */
bool GetMessage(int8_t *USBReadBuffer, S_ParamGen *pParam, bool *SaveTodo);

#endif
