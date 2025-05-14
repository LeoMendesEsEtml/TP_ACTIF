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
 * @brief Initialise les param�tres du menu � partir de la m�moire sauvegard�e ou en valeurs par d�faut.
 * @param pParam Pointeur vers la structure contenant les param�tres du g�n�rateur.
 */
void MENU_Initialize(S_ParamGen *pParam);

/**
 * @brief Affiche les param�tres actuels du g�n�rateur sur l'�cran LCD selon l'�tat du menu.
 * @param pParam Pointeur vers la structure de param�tres du g�n�rateur.
 * @param menu Num�ro d'�tat courant du menu (MenuState_t).
 */
void MENU_Display(S_ParamGen *pParam, uint8_t menu);

/**
 * @brief Machine � �tats du menu principal, g�re l'affichage, la modification et la sauvegarde des param�tres.
 * @param pParam Pointeur vers la structure contenant les param�tres en cours.
 * @param USBState Indique si le syst�me est en mode remote (USB actif).
 * @param saveRequested Indique si une demande de sauvegarde est en attente.
 */
void MENU_Execute(S_ParamGen *pParam, bool USBState, bool saveRequested);



#endif //Mc32GestSpiDac_H
