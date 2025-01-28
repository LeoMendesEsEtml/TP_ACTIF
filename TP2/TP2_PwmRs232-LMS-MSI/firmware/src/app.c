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
 * @brief Callback pour le Timer 1 : g�re les actions p�riodiques de l'application.
 * 
 * @details Cette fonction est appel�e � chaque interruption g�n�r�e par le Timer 1. 
 *          Pendant les 3 premi�res secondes, un compteur est incr�ment� pour surveiller 
 *          la p�riode initiale de d�marrage. Apr�s cette p�riode, la fonction ex�cute
 *          des t�ches sp�cifiques telles que la mise � jour de l'�tat de l'application
 *          et le nettoyage de l'�cran LCD.
 * 
 * @param[in] void Aucun param�tre requis.
 * 
 * @return void Aucun retour. Toutes les mises � jour sont g�r�es via des variables globales 
 *              ou des fonctions applicatives.
 */
/**
 * @brief Callback pour le Timer 1 : g�re les actions p�riodiques de l'application.
 */
void App_Timer1Callback(void)
{
    // Compteur pour g�rer les 3 premi�res secondes (approximation bas�e sur la p�riode du timer)
    static uint8_t threeSecondCounter = 0;

    // Indicateur pour demander un nettoyage de l'�cran
    static uint8_t ClearScreenRequest = 0;

    // Pendant les 3 premi�res secondes
    if (threeSecondCounter < 149) // 149 interruptions approximativement �gales � 3 secondes
    {
        // Incr�mente le compteur
        threeSecondCounter++;

        // Marque que le nettoyage de l'�cran est requis
        ClearScreenRequest = 1;
    }
    else
    {
        // Apr�s les 3 premi�res secondes, ex�cute les t�ches de service
        APP_UpdateState(APP_STATE_SERVICE_TASKS);

        // Si le nettoyage de l'�cran est demand�
        if (ClearScreenRequest == 1)
        {
            // Nettoie l'�cran LCD
            ClearLcd();

            // R�initialise la demande de nettoyage
            ClearScreenRequest = 0;
        }
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


/******************************************************************************
  Function:
    void APP_Tasks ( void )

  Remarks:
    See prototype in app.h.
 */

void APP_Tasks(void)
{
    // Statut de la communication (LOCAL ou REMOTE).
    static uint8_t CommStatus = 0;

    // Structure pour stocker les param�tres PWM � envoyer.
    static S_pwmSettings PWMDataToSend;
    
    // Variable statique pour s'assurer que cette section s'ex�cute une seule fois.
    static uint8_t firstInit = 1;
    // Compteur pour contr�ler les cycles d'ex�cution.
    static int8_t Iteration = 0;
    
    /* V�rifie l'�tat actuel de l'application. */
    switch (appData.state)
    {
        /* �tat initial de l'application */
        case APP_STATE_INIT:
        {

            if (firstInit == 1)
            {
                firstInit = 0; // Emp�che la r�initialisation lors des prochains appels.

                TurnOffAllLEDs(); // �teint toutes les LED.

                // Initialisation de l'�cran LCD.
                lcd_init();
                lcd_bl_on(); // Active le r�tro�clairage.

                // Affichage des informations sur l'�cran LCD.
                lcd_gotoxy(1, 1);
                printf_lcd("Local Settings");
                lcd_gotoxy(1, 2);
                printf_lcd("TP2 USART 2024-25");
                lcd_gotoxy(1, 3);
                printf_lcd("Leo Mendes");
                lcd_gotoxy(1, 4);
                printf_lcd("Matteo Stefanelli");

                // Initialisation des modules de l'application.
                GPWM_Initialize(&pData);   // Initialisation des param�tres PWM.
                BSP_InitADC10();          // Initialisation des ADC.
                InitFifoComm();           // Initialisation des FIFOs.
                DRV_USART0_Initialize();  // Initialisation de l'USART.
            }

            break;
        }

        /* �tat d'attente de l'application */
        case APP_STATE_WAIT:
        {
            break;
        }

        /* �tat d'ex�cution des t�ches de l'application */
        case APP_STATE_SERVICE_TASKS:
        {
            // Allume la LED 0 pour indiquer l'ex�cution des t�ches.
            BSP_LEDOn(BSP_LED_0);

            // R�ception des param�tres (local ou remote).
            CommStatus = GetMessage(&pData);

            // Lecture des param�tres PWM en fonction du statut de communication.
            if (CommStatus == LOCAL)
            {
                GPWM_GetSettings(&pData); // Mode local : lit les param�tres directement.
            }
            else
            {
                GPWM_GetSettings(&PWMDataToSend); // Mode remote : pr�pare les donn�es � envoyer.
            }

            // Ex�cute les param�tres PWM et g�re le moteur.
            GPWM_ExecPWM(&pData);

            // Affiche les param�tres PWM et l'�tat de la communication.
            GPWM_DispSettings(&pData, CommStatus);

            // Incr�mente le compteur d'it�rations.
            Iteration++;

            // Envoie les param�tres toutes les 5 it�rations.
            if (Iteration >= 5)
            {
                if (CommStatus == LOCAL)
                {
                    SendMessage(&pData); // Envoie les param�tres en mode local.
                }
                else
                {
                    SendMessage(&PWMDataToSend); // Envoie les param�tres en mode remote.
                }

                Iteration = 0; // R�initialise le compteur.
            }

            // �teint la LED 0 apr�s l'ex�cution des t�ches.
            BSP_LEDOff(BSP_LED_0);

            // Bascule l'�tat de l'application en mode attente.
            APP_UpdateState(APP_STATE_WAIT);

            break;
        }

        /* �tat par d�faut (ne devrait jamais �tre ex�cut�) */
        default:
        {
            // Gestion des erreurs dans la machine d'�tat.
            break;
        }
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
