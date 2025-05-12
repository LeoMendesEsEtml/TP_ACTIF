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
// Prototypes des fonctions de communication s�rie USB
/*--------------------------------------------------------*/

/**
 * @brief Pr�pare une trame texte � envoyer via USB CDC.
 * 
 * Cette fonction construit une cha�ne de caract�res format�e contenant
 * l?ensemble des param�tres actuels du g�n�rateur (forme, fr�quence, amplitude,
 * offset) ainsi qu?un indicateur de sauvegarde.
 * 
 * @param USBSendBuffer Pointeur vers le tampon dans lequel la trame sera �crite.
 *                      Ce tampon doit avoir une taille suffisante pour contenir
 *                      toute la trame (64 octets minimum).
 * @param pParam Pointeur vers la structure contenant les param�tres du g�n�rateur.
 * @param Saved Bool�en indiquant si une sauvegarde a �t� effectu�e (true = oui, false = non).
 */
void SendMessage(int8_t *USBSendBuffer, S_ParamGen *pParam, bool Saved);

/**
 * @brief Analyse une trame re�ue via USB CDC et met � jour les param�tres du g�n�rateur.
 * 
 * Cette fonction extrait les informations contenues dans une trame re�ue
 * (sous forme de cha�ne de caract�res) et met � jour les champs correspondants
 * dans la structure S_ParamGen. Elle v�rifie �galement si une demande de
 * sauvegarde est incluse.
 * 
 * @param USBReadBuffer Pointeur vers la trame re�ue en entr�e (cha�ne ASCII).
 *                      Doit commencer par '!' et se terminer par '#'.
 * @param pParam Pointeur vers la structure � remplir avec les nouveaux param�tres.
 * @param SaveTodo Pointeur vers un bool�en qui sera mis � true si la trame demande une sauvegarde (W=1).
 * 
 * @return true si le message est valide et a �t� correctement d�cod�, false sinon.
 */
bool GetMessage(int8_t *USBReadBuffer, S_ParamGen *pParam, bool *SaveTodo);

#endif
