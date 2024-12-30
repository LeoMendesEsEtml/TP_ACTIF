/*******************************************************************************
  MPLAB Harmony Application Source File
  
  Company:
    Microchip Technology Inc.
  
  File Name:
    app.c

  Summary:
    This file contains the source code for the MPLAB Harmony application.

  Description:
    This file contains the source code for the MPLAB Harmony application.  It 
    implements the logic of the application's state machine and it may call 
    API routines of other MPLAB Harmony modules in the system, such as drivers,
    system services, and middleware.  However, it does not call any of the
    system interfaces (such as the "Initialize" and "Tasks" functions) of any of
    the modules in the system or make any assumptions about when those functions
    are called.  That is the responsibility of the configuration-specific system
    files.
 *******************************************************************************/

// DOM-IGNORE-BEGIN
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
// DOM-IGNORE-END


// *****************************************************************************
// *****************************************************************************
// Section: Included Files 
// *****************************************************************************
// *****************************************************************************

#include "app.h"
#include "gestPWM.h"

// *****************************************************************************
// *****************************************************************************
// Section: Global Data Definitions
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Application Data

  Summary:
    Holds application data

  Description:
    This structure holds the application's data.

  Remarks:
    This structure should be initialized by the APP_Initialize function.
    
    Application strings and buffers are be defined outside this structure.
*/

APP_DATA appData;
S_pwmSettings pData;
// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Functions
// *****************************************************************************
// *****************************************************************************

/* TODO:  Add any necessary callback functions.
*/

// *****************************************************************************
// *****************************************************************************
// Section: Application Local Functions
// *****************************************************************************
// *****************************************************************************


/* TODO:  Add any necessary local functions.
*/


// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void APP_Initialize ( void )

  Remarks:
    See prototype in app.h.
 */

void APP_Initialize ( void )
{
    /* Place the App state machine in its initial state. */
    appData.state = APP_STATE_INIT;

    
    /* TODO: Initialize your application's state machine and other
     * parameters.
     */
}


/******************************************************************************
  Function:
    void APP_Tasks ( void )

  Remarks:
    See prototype in app.h.
 */

void APP_Tasks ( void )
{

    /* Check the application's current state. */
    switch ( appData.state )
    {
        /* Application's initial state. */
        case APP_STATE_INIT:
        {
            lcd_init(); // Initialisation de l'écran LCD
            lcd_bl_on(); // Allume le rétroéclairage du LCD
            
            lcd_gotoxy(1,1); // Positionne le curseur à la première ligne
            printf_lcd("TP1 PWM 2024-25"); // Affiche un texte d'introduction
            lcd_gotoxy(1,2); 
            printf_lcd("Leo Mendes"); 
            lcd_gotoxy(1,3);
            printf_lcd("Vitor Coelho");           
            
            GPWM_Initialize(&pData);

            BSP_InitADC10(); // Initialisation des ADC (convertisseurs analogiques-numériques)
            DRV_OC0_PulseWidthSet(70);
            DRV_OC1_PulseWidthSet(1000);
            APP_UpdateState(APP_STATE_SERVICE_TASKS);
            break; 
        }

        case APP_STATE_WAIT :
        {
            break;
        }
        
        /* TODO: implement your application state machine.*/
        case APP_STATE_SERVICE_TASKS :
        {
            break; 
        }

        /* The default state should never be executed. */
        default:
        {
            /* TODO: Handle error in application's state machine. */
            break;
        }
    }
}

 void APP_UpdateState (APP_STATES Newstate)
{
    appData.state = Newstate; // Met à jour l'état de l'application
}


void App_Timer1Callback()
{
    static uint8_t compteur3s = 0;
    static uint8_t compteurClearLine = 0;

    // Pendant les 3 premières secondes
    if (compteur3s < 149)
    {
        APP_UpdateState(APP_STATE_INIT);
        compteur3s++;
    }
    else
    {
        // Après les 3 premières secondes

        // Affiche des informations sur l'afficheur LCD
        if (compteurClearLine <= 0)
        {
            lcd_ClearLine(2);
            lcd_ClearLine(3);
            compteurClearLine++;
        }

        // Allume la LED BSP_LED_0 pendant l'exécution des tâches
        BSP_LEDOn(BSP_LED_0);

        // Obtient les paramètres PWM, les affiche et exécute la PWM
        GPWM_GetSettings(&pData);
        GPWM_DispSettings(&pData);
        GPWM_ExecPWM(&pData);

        // Éteint la LED BSP_LED_0 après l'exécution des tâches
        BSP_LEDOff(BSP_LED_0);
    }
}
void App_Timer4Callback()
{
    // Allume la LED BSP_LED_1 pendant l'exécution de la PWM logiciel
    BSP_LEDOn(BSP_LED_1);

    // Exécute la PWM logiciel
    GPWM_ExecPWMSoft(&pData);

    // Éteint la LED BSP_LED_1 après l'exécution de la PWM logiciel
    BSP_LEDOff(BSP_LED_1);
}
/*******************************************************************************
 End of File
 */
