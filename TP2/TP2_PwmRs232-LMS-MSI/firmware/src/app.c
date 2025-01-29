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
#include "system_config.h"       // Configuration du syst�me (Harmony)
#include "system_definitions.h"  // D�finitions du syst�me (Harmony)
#include "bsp.h"                 // Board Support Package Harmony

// --------------- Inclusions suppl�mentaires ---------------
// (�cran LCD, ADC, etc.)
#include "Mc32DriverLcd.h"       // Pilote pour �cran LCD
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
 * @brief Callback pour le Timer 1. G�re les actions p�riodiques de l'application.
 * @author LMS - VCO
 * @date 2025-01-02
 *
 * @details Cette fonction est appel�e � chaque interruption du Timer 1. Elle g�re
 *          un compteur pour les 3 premi�res secondes, met � jour l'�tat de l'application
 *          et ex�cute des t�ches sp�cifiques apr�s cette p�riode.
 */
void App_Timer1Callback()
{
    // Compteur pour les 3 premi�res secondes (approximation bas�e sur une p�riode du timer)
    static uint8_t threeSecondCounter = 0;

    // Pendant les 3 premi�res secondes
    if (threeSecondCounter < 149)
    {
        threeSecondCounter++; // Incr�mente le compteur
    }
    else
    {
        // Apr�s les 3 premi�res secondes, ex�cute les t�ches de service
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
 * @brief Nettoie l'�cran LCD en effa�ant toutes ses lignes (1 � 4).
 * 
 * @author LMS- VCO
 * @date 2025-01-02
 *
 * @details
 * Cette fonction appelle successivement la routine `lcd_ClearLine()` pour
 * chaque ligne de l'�cran (de la 1 � la 4), permettant ainsi de r�initialiser
 * compl�tement l'affichage avant d'y �crire de nouvelles informations.
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
 *          pour forcer les broches correspondantes � l'�tat bas (0), allumant ainsi
 *          les LEDs connect�es.
 */
void TurnOnAllLEDs(void) {
    // Allumer les LEDs sur PORTA et PORTB
    PLIB_PORTS_Write(PORTS_ID_0, PORT_CHANNEL_A, 
                     PLIB_PORTS_Read(PORTS_ID_0, PORT_CHANNEL_A) & ~LEDS_PORTA_MASK);
    PLIB_PORTS_Write(PORTS_ID_0, PORT_CHANNEL_B, 
                     PLIB_PORTS_Read(PORTS_ID_0, PORT_CHANNEL_B) & ~LEDS_PORTB_MASK);
}

/**
 * @brief �teint toutes les LEDs (actives bas).
 * @author LMS - VCO
 * @date 2025-01-02
 *
 * @details Cette fonction utilise les masques `LEDS_PORTA_MASK` et `LEDS_PORTB_MASK`
 *          pour forcer les broches correspondantes � l'�tat haut (1), �teignant ainsi
 *          les LEDs connect�es.
 */
void TurnOffAllLEDs(void) {
    // �teindre les LEDs sur PORTA et PORTB
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

/**
 * @brief G�re l'ex�cution des t�ches de l'application en fonction de son �tat.
 *
 * @details Cette fonction impl�mente la machine d'�tat de l'application. 
 * - Dans l'�tat `APP_STATE_INIT`, elle effectue l'initialisation une seule fois.
 * - Dans l'�tat `APP_STATE_WAIT`, elle attend un nouvel �v�nement.
 * - Dans l'�tat `APP_STATE_SERVICE_TASKS`, elle g�re la r�ception, le traitement et l'envoi des donn�es.
 */
/**
 * @brief Ex�cute les t�ches principales de l'application en fonction de son �tat.
 */
void APP_Tasks(void)
{
    static uint8_t CommStatus = 0; // Statut de la communication (LOCAL ou REMOTE)
    static S_pwmSettings PWMDataToSend; // Stocke les valeurs locales des potentiom�tres
    static uint8_t firstInit = 1; // V�rifie si l'initialisation a d�j� �t� effectu�e
    static int8_t Iteration = 0; // Compteur pour g�rer l'envoi p�riodique des donn�es

    switch (appData.state)
    {
        case APP_STATE_INIT: // Initialisation de l'application
        {
            if (firstInit == 1)
            {
                firstInit = 0; // Emp�che une nouvelle ex�cution de cette section

                TurnOffAllLEDs(); // D�sactive toutes les LEDs
                
                lcd_init(); // Initialise l'�cran LCD
                lcd_bl_on(); // Active le r�tro�clairage
                
                lcd_gotoxy(1, 1);
                printf_lcd("Local Settings"); // Affiche l'�tat initial
                
                lcd_gotoxy(1, 2);
                printf_lcd("TP2 USART 2024-25"); // Affiche le titre du projet
                
                lcd_gotoxy(1, 3);
                printf_lcd("Leo Mendes"); // Affiche le premier auteur
                
                lcd_gotoxy(1, 4);
                printf_lcd("Matteo Stefanelli"); // Affiche le second auteur
            
                GPWM_Initialize(&pData); // Initialise la gestion du PWM
                BSP_InitADC10(); // Initialise l'ADC
                InitFifoComm(); // Initialise la communication FIFO
                DRV_USART0_Initialize(); // Initialise l'USART
            }
            break;
        }

        case APP_STATE_WAIT: // Mode attente, aucune action requise
            break;

        case APP_STATE_SERVICE_TASKS: // Traitement des donn�es
        {            
            BSP_LEDOn(BSP_LED_0); // Allume la LED 0 pour indiquer l'ex�cution des t�ches

            // R�cup�ration de l'�tat de la communication
            CommStatus = GetMessage(&pData); 

            if (CommStatus == LOCAL) 
            {
                // Mode LOCAL :
                // - Lecture des potentiom�tres
                // - Stockage dans `pData` pour utilisation imm�diate et envoi
                GPWM_GetSettings(&pData); 
            }
            else 
            {
                // Mode REMOTE :
                // - `pData` contient les derni�res valeurs re�ues via RS232
                // - On �vite d?�craser `pData`, donc on stocke les valeurs locales dans `PWMDataToSend`
                GPWM_GetSettings(&PWMDataToSend); 
            }

            GPWM_ExecPWM(&pData); // Applique les param�tres PWM
            GPWM_DispSettings(&pData, CommStatus); // Met � jour l'affichage
            
            Iteration++; // Incr�mente le compteur

            if (Iteration >= 5) // Ex�cute l'envoi des donn�es toutes les 5 it�rations
            {
                if (CommStatus == LOCAL) 
                { 
                    // Envoi des valeurs locales lues depuis les potentiom�tres
                    SendMessage(&pData); 
                }
                else 
                {
                    // Envoi des valeurs des potentiom�tres sauvegard�es
                    SendMessage(&PWMDataToSend); 
                }
                Iteration = 0; // R�initialisation du compteur
            }            

            BSP_LEDOff(BSP_LED_0); // �teint la LED 0 apr�s l'ex�cution des t�ches

            APP_UpdateState(APP_STATE_WAIT); // Repasse en attente
            break; 
        }

        default: // S�curit� en cas d'�tat inconnu
            break;
    }
}

/**
 * @brief Met � jour l'�tat actuel de l'application.
 * @author LMS - VCO
 * @date 2025-01-02
 * 
 * @param Newstate Nouveau �tat � affecter � l'application (type APP_STATES).
 * 
 * @details Cette fonction met � jour la variable globale `appData.state` avec
 *          la valeur de l'�tat fourni en param�tre.
 */
void APP_UpdateState(APP_STATES Newstate)
{
    // Met � jour l'�tat de l'application avec le nouvel �tat sp�cifi�
    appData.state = Newstate;
}

/*******************************************************************************
 End of File
 */
