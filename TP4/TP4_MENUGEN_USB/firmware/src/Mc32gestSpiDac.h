/*--------------------------------------------------------*/
// Mc32GestSpiDac.h
/*--------------------------------------------------------*/
//	Description :	Gestion DAC Spi du Kit (LTC2604)
//
//	Auteur 		: 	C. Huber
//	Version		:	V1.2
//	Compilateur	:	XC32 V1.40 + Harmony 1.06
//
//  Modifications :
//   CHR 06.03.2015  ajout fonction SPI_CfgWriteToDac
//   CHR 24.05.2016  maj version compilateur et Harmony 
//
/*--------------------------------------------------------*/

#ifndef Mc32GestSpiDac_H
#define Mc32GestSpiDac_H

#include <stdint.h>

/*--------------------------------------------------------*/
// Prototypes des fonctions pour MenuGen.c
/*--------------------------------------------------------*/

/**
 * @brief Initialise les paramètres du menu à partir de la mémoire sauvegardée ou en valeurs par défaut.
 * @param pParam Pointeur vers la structure contenant les paramètres du générateur.
 */
void MENU_Initialize(S_ParamGen *pParam);

/**
 * @brief Affiche les paramètres actuels du générateur sur l'écran LCD selon l'état du menu.
 * @param pParam Pointeur vers la structure de paramètres du générateur.
 * @param menu Numéro d'état courant du menu (MenuState_t).
 */
void MENU_Display(S_ParamGen *pParam, uint8_t menu);

/**
 * @brief Machine à états du menu principal, gère l'affichage, la modification et la sauvegarde des paramètres.
 * @param pParam Pointeur vers la structure contenant les paramètres en cours.
 * @param USBState Indique si le système est en mode remote (USB actif).
 * @param saveRequested Indique si une demande de sauvegarde est en attente.
 */
void MENU_Execute(S_ParamGen *pParam, bool USBState, bool saveRequested);



#endif //Mc32GestSpiDac_H
