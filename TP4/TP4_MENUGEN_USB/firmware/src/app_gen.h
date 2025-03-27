/*******************************************************************************
  MPLAB Harmony Application Header File

  Company:
    Microchip Technology Inc.

  File Name:
    app_gen.h

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

#ifndef _APP_GEN_H
#define _APP_GEN_H

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include "system_config.h"
#include "system_definitions.h"

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility

extern "C" {

#endif
// DOM-IGNORE-END 
// *****************************************************************************
// *****************************************************************************
// Section: Type Definitions
// *****************************************************************************
#define WAIT_INIT 2999  // Nombre d'itérations approximatives pour 3 secondes
// Masques pour les LEDs
#define LEDS_PORTA_MASK  0b1000011111110011 // RA0-RA7 et RA15
#define LEDS_PORTB_MASK  0b0000010000000000 // RB10
// *****************************************************************************
// *****************************************************************************
// Section: Type Definitions
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Application states

          Summary:
            Application states enumeration

          Description:
            This enumeration defines the valid application states.  These states
            determine the behavior of the application at various times.
     */

    typedef enum {
        /* Application's state machine's initial state. */
        APP_GEN_STATE_INIT = 0,
        APP_GEN_STATE_INIT_WAIT = 1,
        APP_GEN_STATE_INIT_CLEAR = 2,
        APP_GEN_STATE_SERVICE_TASKS = 3,
        APP_GEN_STATE_WAIT = 4,
    } APP_GEN_STATES;


// *****************************************************************************
/* Application Data

  Summary:
    Holds application data

  Description:
    This structure holds the application's data.

  Remarks:
    Application strings and buffers are be defined outside this structure.
 */

typedef struct
{
    /* The application's current state */
    APP_GEN_STATES state;

    /* TODO: Define any additional data used by the application. */

} APP_GEN_DATA;


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
void App_Timer1Callback();
/**
 * @brief Callback pour le Timer 3. 
 * @author LMS - TCT
 * @date 2025-01-30
 *
 * @details 
 */
void App_Timer3Callback();
// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void APP_GEN_Initialize ( void )

  Summary:
     MPLAB Harmony application initialization routine.

  Description:
    This function initializes the Harmony application.  It places the 
    application in its initial state and prepares it to run so that its 
    APP_Tasks function can be called.

  Precondition:
    All other system initialization routines should be called before calling
    this routine (in "SYS_Initialize").

  Parameters:
    None.

  Returns:
    None.

  Example:
    <code>
    APP_GEN_Initialize();
    </code>

  Remarks:
    This routine must be called from the SYS_Initialize function.
*/

void APP_GEN_Initialize ( void );


/*******************************************************************************
  Function:
    void APP_GEN_Tasks ( void )

  Summary:
    MPLAB Harmony Demo application tasks function

  Description:
    This routine is the Harmony Demo application's tasks function.  It
    defines the application's state machine and core logic.

  Precondition:
    The system and application initialization ("SYS_Initialize") should be
    called before calling this.

  Parameters:
    None.

  Returns:
    None.

  Example:
    <code>
    APP_GEN_Tasks();
    </code>

  Remarks:
    This routine must be called from SYS_Tasks() routine.
 */

void APP_GEN_Tasks( void );



void APP_GEN_UpdateState ( APP_GEN_STATES NewState) ;
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

#endif /* _APP_GEN_H */

//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

/*******************************************************************************
 End of File
 */

