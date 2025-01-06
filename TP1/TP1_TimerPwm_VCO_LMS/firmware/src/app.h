/*******************************************************************************
  MPLAB Harmony Application Header File

  Company:
    Microchip Technology Inc.

  File Name:
    app.h

  Summary:
    This header file provides prototypes and definitions for the application.

  Description:
    This header file provides function prototypes and data type definitions for
    the application.  Some of these are required by the system (such as the
    "APP_Initialize" and "APP_Tasks" prototypes) and some of them are only used
    internally by the application (such as the "APP_STATES" definition).  Both
    are defined here for convenience.
*******************************************************************************/

//DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2013-2014 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
 *******************************************************************************/
//DOM-IGNORE-END

#ifndef _APP_H
#define _APP_H

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
// --------------- Inclusions standard ---------------
#include <stdint.h>              // Types entiers (uint8_t, etc.)
#include <stdbool.h>             // Type booléen (true/false)
#include <stddef.h>              // Définit size_t, NULL, etc.
#include <stdlib.h>              // Fonctions utilitaires standard

// --------------- Inclusions Harmony ---------------
#include "system_config.h"       // Configuration du système (Harmony)
#include "system_definitions.h"  // Définitions du système (Harmony)
#include "bsp.h"                 // Board Support Package Harmony

// --------------- Inclusions supplémentaires ---------------
// (Écran LCD, ADC, etc.)
#include "Mc32DriverLcd.h"       // Pilote pour écran LCD
#include "Mc32DriverAdc.h"       // Pilote pour ADC
#include "peripheral/ports/plib_ports.h" //Gestion des ports

#include "gestPWM.h"            // gestion des pwm


// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility

extern "C" {
#endif
// DOM-IGNORE-END 

// *****************************************************************************
// *****************************************************************************
// Section: Type Definitions
// *****************************************************************************
// *****************************************************************************
// Masques pour les LEDs
#define LEDS_PORTA_MASK  0b1000011111110011 // RA0-RA7 et RA15
#define LEDS_PORTB_MASK  0b0000010000000000 // RB10
/**
 * @enum APP_STATES
 * @brief Énumération pour les différents états de l'application.
 */
typedef enum
{
    APP_STATE_INIT = 0,      // État initial de l'application
    APP_STATE_WAIT,          // État d'attente ou de temporisation
    APP_STATE_SERVICE_TASKS, // État d'exécution des tâches applicatives
} APP_STATES;

/**
 * @struct APP_DATA
 * @brief Structure contenant les données de l'application.
 */
typedef struct
{
    APP_STATES state;        //État courant de l'application
    S_ADCResults AdcRes;     // Résultats ADC (structure personnalisée)
} APP_DATA;

// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Routines
// *****************************************************************************
// *****************************************************************************
/**
 * @brief Fonction callback pour le Timer 1.
 *
 * Appelée lors de chaque interruption du Timer 1. Gère un compteur pour les premières
 * secondes et lance l'exécution de tâches après ce délai.
 */
void App_Timer1Callback(void);

/**
 * @brief Fonction callback pour le Timer 4.
 *
 * Appelée lors de chaque interruption du Timer 4. Gère l'exécution de la PWM logicielle.
 */
void App_Timer4Callback(void);

// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************
// *****************************************************************************

/**
 * @brief Initialise l'application.
 *
 * Cette fonction prépare l'application pour qu'elle puisse être exécutée.
 * Elle doit être appelée depuis la fonction `SYS_Initialize()`.
 *
 * @pre Toutes les initialisations du système doivent être terminées avant d?appeler cette fonction.
 */
void APP_Initialize(void);

/**
 * @brief Met à jour l'état courant de l'application.
 *
 * @param NewState Le nouvel état à affecter (de type @c APP_STATES).
 */
void APP_UpdateState(APP_STATES NewState);

/**
 * @brief Gère la machine à états principale de l'application.
 *
 * Cette fonction définit la logique principale de l'application et est appelée
 * de manière continue depuis `SYS_Tasks()`. En fonction de l'état courant,
 * différentes actions sont exécutées.
 */
void APP_Tasks(void);

// *****************************************************************************
// *****************************************************************************
// Section: Application specific functions
// *****************************************************************************
// *****************************************************************************
/**
 * @brief Allume toutes les LEDs actives bas.
 *
 * Met à l'état bas toutes les broches associées aux LEDs.
 */
void TurnOnAllLEDs(void);

/**
 * @brief Éteint toutes les LEDs actives bas.
 *
 * Met à l'état haut toutes les broches associées aux LEDs.
 */
void TurnOffAllLEDs(void);

/**
 * @brief Efface l'affichage de l'écran LCD.
 *
 * Cette fonction nettoie toutes les lignes de l'écran LCD.
 */
void ClearLcd(void);

// DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
// DOM-IGNORE-END

#endif /* _APP_H */

/*******************************************************************************
 End of File
 */

