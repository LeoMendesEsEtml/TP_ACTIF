/*******************************************************************************
  MPLAB Harmony Application Source File
  
  Company:
    Microchip Technology Inc.
  
  File Name:
    app.c

  Summary:
     Pour Tp3 Menu et generateur de signal .

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

#include <stdbool.h>
#include "app.h"
#include "Mc32DriverLcd.h"
#include "Mc32gestSpiDac.h"
#include "MenuGen.h"
#include "GesPec12.h"
#include "Generateur.h"

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
S_ParamGen LocalParamGen;


// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Functions
// *****************************************************************************
// *****************************************************************************
/**
 * @brief Callback pour le Timer 1. Gère les actions périodiques de l'application.
 * @author LMS - TCT
 * @date 2025-01-30
 *
 * @details 
 */
#define WAIT_INIT 2999

void App_Timer1Callback() {
    LED1_W = !LED1_R;
    // Compteur pour les 3 premières secondes (approximation basée sur une période du timer)
    static uint16_t WaitIteration = 0;
    static bool InitDone = false;
    // Pendant les 3 premières secondes
    if ((WaitIteration < WAIT_INIT)&&(InitDone == false)) {
        WaitIteration++; // Incrémente le compteur
    } else {
        if (InitDone == false) {
            ClearLcd();
            InitDone = true;
            WaitIteration = 0;
        }
        if (WaitIteration == 10) {
            WaitIteration = 0;
            ScanBtn(PEC12_A, PEC12_B, PEC12_PB,S_OK);
            // Après les 3 premières secondes, exécute les tâches de service
            APP_UpdateState(APP_STATE_SERVICE_TASKS);          
        } else {
            WaitIteration++;
        }
    }
}
/**
 * @brief Callback pour le Timer 3. 
 * @author LMS - TCT
 * @date 2025-01-30
 *
 * @details 
 */
void App_Timer3Callback()
{
    LED0_W = 1; 
    GENSIG_Execute();
    LED0_W = 0;
}


// *****************************************************************************
// *****************************************************************************
// Section: Application Local Functions
// *****************************************************************************
// *****************************************************************************

/**
 * @brief Nettoie l'écran LCD en effaçant toutes ses lignes (1 à 4).
 * 
 * @author LMS- VCO
 * @date 2025-01-02
 *
 * @details
 * Cette fonction appelle successivement la routine `lcd_ClearLine()` pour
 * chaque ligne de l'écran (de la 1 à la 4), permettant ainsi de réinitialiser
 * complètement l'affichage avant d'y écrire de nouvelles informations.
 */
void ClearLcd()
{
    lcd_ClearLine(1);
    lcd_ClearLine(2);
    lcd_ClearLine(3);
    lcd_ClearLine(4);
}

/**
 * @brief Allume toutes les LEDs (actives bas).
 * @author LMS - VCO
 * @date 2025-01-02
 *
 * @details Cette fonction utilise les masques `LEDS_PORTA_MASK` et `LEDS_PORTB_MASK`
 *          pour forcer les broches correspondantes à l'état bas (0), allumant ainsi
 *          les LEDs connectées.
 */
void TurnOnAllLEDs(void) {
    // Allumer les LEDs sur PORTA et PORTB
    PLIB_PORTS_Write(PORTS_ID_0, PORT_CHANNEL_A, 
                     PLIB_PORTS_Read(PORTS_ID_0, PORT_CHANNEL_A) & ~LEDS_PORTA_MASK);
    PLIB_PORTS_Write(PORTS_ID_0, PORT_CHANNEL_B, 
                     PLIB_PORTS_Read(PORTS_ID_0, PORT_CHANNEL_B) & ~LEDS_PORTB_MASK);
}

/**
 * @brief Éteint toutes les LEDs (actives bas).
 * @author LMS - VCO
 * @date 2025-01-02
 *
 * @details Cette fonction utilise les masques `LEDS_PORTA_MASK` et `LEDS_PORTB_MASK`
 *          pour forcer les broches correspondantes à l'état haut (1), éteignant ainsi
 *          les LEDs connectées.
 */
void TurnOffAllLEDs(void) {
    // Éteindre les LEDs sur PORTA et PORTB
    PLIB_PORTS_Write(PORTS_ID_0, PORT_CHANNEL_A, 
                     PLIB_PORTS_Read(PORTS_ID_0, PORT_CHANNEL_A) | LEDS_PORTA_MASK);
    PLIB_PORTS_Write(PORTS_ID_0, PORT_CHANNEL_B, 
                     PLIB_PORTS_Read(PORTS_ID_0, PORT_CHANNEL_B) | LEDS_PORTB_MASK);
}


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
            lcd_init();
            lcd_bl_on();

            // Init SPI DAC
            SPI_InitLTC2604();

            // Initialisation PEC12
            Pec12Init();

            // Initialisation du menu
            MENU_Initialize(&LocalParamGen);

            // Initialisation du generateur
            GENSIG_Initialize(&LocalParamGen);

            lcd_gotoxy(1, 1);
            printf_lcd("TP2 USART 2024-25"); // Affiche le titre du projet

            lcd_gotoxy(1, 2);
            printf_lcd("Leo Mendes"); // Affiche le premier auteur

            lcd_gotoxy(1, 3);
            printf_lcd("Tassilo Choulat"); // Affiche le second auteur

            // Active les timers 
            DRV_TMR0_Start();
            DRV_TMR1_Start();
            appData.state = APP_STATE_WAIT;
            break;
        }
        case APP_STATE_WAIT :
          // nothing to do
        break;

       case APP_STATE_SERVICE_TASKS:
            BSP_LEDToggle(BSP_LED_2);

            // Execution du menu
            MENU_Execute(&LocalParamGen);
            appData.state = APP_STATE_WAIT;
         break;
        /* TODO: implement your application state machine.*/

        /* The default state should never be executed. */
        default:
        {
            /* TODO: Handle error in application's state machine. */
            break;
        }
    }
}

void APP_UpdateState ( APP_STATES NewState )
{
    appData.state = NewState;
}

/*******************************************************************************
 End of File
 */

