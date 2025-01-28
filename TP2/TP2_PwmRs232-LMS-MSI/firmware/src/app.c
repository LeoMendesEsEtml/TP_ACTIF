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
// --------------- Inclusions standard ---------------
#include <stdint.h>              // Types entiers (uint8_t, etc.)

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
#include "Mc32gest_RS232.h"     // gestion des communications RS-232
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
/**
 * @brief Callback pour le Timer 1. Gère les actions périodiques de l'application.
 * @author LMS - VCO
 * @date 2025-01-02
 *
 * @details Cette fonction est appelée à chaque interruption du Timer 1. Elle gère
 *          un compteur pour les 3 premières secondes, met à jour l'état de l'application
 *          et exécute des tâches spécifiques après cette période.
 */
void App_Timer1Callback()
{
    // Compteur pour les 3 premières secondes (approximation basée sur une période du timer)
    static uint8_t threeSecondCounter = 0;

    // Pendant les 3 premières secondes
    if (threeSecondCounter < 149)
    {
        threeSecondCounter++; // Incrémente le compteur
    }
    else
    {
        // Après les 3 premières secondes, exécute les tâches de service
        APP_UpdateState(APP_STATE_SERVICE_TASKS);
        
        // Nettoyer le LCD
        ClearLcd();
    }
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
}


/******************************************************************************
  Function:
    void APP_Tasks ( void )

  Remarks:
    See prototype in app.h.
 */

void APP_Tasks ( void )
{
    uint8_t CommStatus = 0;
    S_pwmSettings PWMDataToSend;  
    
    /* Check the application's current state. */
    switch ( appData.state )
    {
        /* État initial de l'application */
        case APP_STATE_INIT:
        {
            // Variable statique utilisée pour s'assurer que cette section ne s'exécute qu'une seule fois
            static uint8_t firstInit = 1; 
    
            if (firstInit == 1)
            {
                // Mise à jour de la variable pour empêcher la réinitialisation lors des prochains appels
                firstInit = 0; 
                
                TurnOffAllLEDs();
                
                // Initialisation de l'écran LCD
                lcd_init(); 
        
                // Allume le rétroéclairage de l'écran LCD
                lcd_bl_on();
                
                // Positionne le curseur à la première ligne du LCD
                lcd_gotoxy(1, 1); 
        
                // Affiche l'etat des paramètres 
                printf_lcd("Local Settings"); 
                
                // Positionne le curseur à la première ligne du LCD
                lcd_gotoxy(1, 2); 
        
                // Affiche un texte d'introduction sur la première ligne
                printf_lcd("TP2 USART 2024-25"); 
        
                // Positionne le curseur à la deuxième ligne
                lcd_gotoxy(1, 3); 
        
                // Affiche le nom de l'auteur 1 sur la deuxième ligne
                printf_lcd("Leo Mendes"); 
        
                // Positionne le curseur à la troisième ligne
                lcd_gotoxy(1, 4); 
        
                // Affiche le nom de l'auteur 2 sur la troisième ligne
                printf_lcd("Matteo Stefanelli");           
        
                // Initialisation du PWM avec des données passées par pointeur
                GPWM_Initialize(&pData); 

                // Initialisation des ADC (convertisseurs analogiques-numériques)
                BSP_InitADC10(); 
                
                InitFifoComm();
                
                DRV_USART0_Initialize();
                
            }
        break; 
        }
        /* État attente de l'application */
        case APP_STATE_WAIT :
        {
            break;
        }
        
        /* État execution de l'application */
        case APP_STATE_SERVICE_TASKS :
        {
            static int8_t Iteration = 0; 
            static int8_t Iteration1ocal = 0; 
            
            // Allume la LED 0 (BSP_LED_0) pour indiquer l'exécution des tâches
            BSP_LEDOn(BSP_LED_0);
            
            // Réception param. remote
            CommStatus = GetMessage(&pData);
            // Lecture pot.
            if (CommStatus == LOCAL)
            { // local ?
                GPWM_GetSettings(&pData); // local
            }
            else
            {
                GPWM_GetSettings(&PWMDataToSend); 
            }// remote
            
            // Affichage
            GPWM_DispSettings(&pData, CommStatus);
            // Execution PWM et gestion moteur
            GPWM_ExecPWM(&pData);
            
            if(Iteration >= 5)
            {
                // Envoi valeurs
                if (CommStatus == LOCAL)
                { // local ?
                    SendMessage(&pData); // local
                }
                else
                {
                    SendMessage(&PWMDataToSend); // remote
                }
                Iteration = 0;
            }
            else 
            {
                Iteration++;   
            }


            // Éteint la LED 0 (BSP_LED_0) après l'exécution des tâches
            BSP_LEDOff(BSP_LED_0);

            // Passage de l'état de la achine en attente
            APP_UpdateState(APP_STATE_WAIT);
 
            break; 
        }

        /* The default state should never be executed. */
        default:
        {
            /* Gestion d'erreur de la machine d'état */
            break;
        }
    }
}

/**
 * @brief Met à jour l'état actuel de l'application.
 * @author LMS - VCO
 * @date 2025-01-02
 * 
 * @param Newstate Nouveau état à affecter à l'application (type APP_STATES).
 * 
 * @details Cette fonction met à jour la variable globale `appData.state` avec
 *          la valeur de l'état fourni en paramètre.
 */
void APP_UpdateState(APP_STATES Newstate)
{
    // Met à jour l'état de l'application avec le nouvel état spécifié
    appData.state = Newstate;
}

/*******************************************************************************
 End of File
 */
