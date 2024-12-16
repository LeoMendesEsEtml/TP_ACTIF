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
#include "bsp.h"
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include "Mc32DriverLcd.h"
 
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
            
            GPWM_Initialize();

            //BSP_InitADC10(); // Initialisation des ADC (convertisseurs analogiques-numériques)
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
            GPWM_Getsettings();
            APP_UpdateState(APP_STATE_WAIT);
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
    static uint8_t test = 1;
     APP_UpdateState(APP_STATE_SERVICE_TASKS);
    if(test == 1)
    {
        BSP_LEDOff(BSP_LED_0);
        test = 0; 
    }
    else
    {
        BSP_LEDOn(BSP_LED_0);
        test = 1;
    }
}
void App_Timer4Callback()
{
    // ToBeRemove
    static uint8_t test = 1;
    if(test == 1)
    {
        BSP_LEDOff(BSP_LED_2);
        test = 0; 
    }
    else
    {
        BSP_LEDOn(BSP_LED_2);
        test = 1;
    }
}
void GPWM_Initialize()
{
    DRV_TMR0_Start();
    DRV_TMR1_Start();
    DRV_TMR2_Start();
    DRV_TMR3_Start();
    DRV_OC0_Start();
    DRV_OC1_Start();
    BSP_EnableHbrige();     
}

// Obtention de vitesse et angles
void GPWM_Getsettings()
{
    // Lecture ADC
    ADC1_Conversion();

}

// Affichage
void GPWM_DISPSettings()
{
    
}

// Execution PWM et gestion Moteur
void GPWM_ExecPWM()
{
    
}

void ADC1_Conversion()
{
    // Lecture ADC 
    #define NUM_SAMPLES 10   // Taille de la moyenne glissante
    #define ADC_MAX 1024     // Valeur maximale de l'ADC (10 bits)

    static uint8_t adcValues[NUM_SAMPLES] = {0};  // Tableau pour la moyenne glissante
    static uint16_t adcValue = 500; 
    static uint8_t currentIndex = 0;              // Index pour l'insertion dans le tableau
    static uint32_t adcSum = 0;                   // Somme des 10 dernières valeurs pour la moyenne
    
    static uint8_t avgAdcValue = 0;
    static uint8_t mappedValue = 0;
    static int8_t speed = 0;
    static uint8_t absSpeed = 0; 
    static int8_t pwmValue = 0;
    
    // Soustraire la vieille valeur et ajouter la nouvelle
    adcSum -= adcValues[currentIndex];
    adcValues[currentIndex] = adcValue;
    adcSum += adcValue;

    // Passer à l'index suivant
    currentIndex = (currentIndex + 1) % NUM_SAMPLES;

    // Calcul de la moyenne de l'ADC
    avgAdcValue = adcSum / NUM_SAMPLES;

    // Conversion de la valeur ADC en une plage de 0 à 198
    mappedValue = (avgAdcValue * 198) / ADC_MAX;  // Plage 0-198

    // Calcul de la vitesse signée (speed), allant de -99 à 99
    speed = mappedValue - 99;  // Plage -99 à +99

    // Calcul de la vitesse absolue (absSpeed), allant de 0 à 99
    if (speed < 0) 
    {
        absSpeed = -speed;  // Si speed est négatif, absSpeed devient la valeur positive
    } 
    else 
    {
        absSpeed = speed;   // Si speed est positif ou nul, absSpeed reste la même
    }


    // Calcul du taux PWM, allant de -99 à 99
    pwmValue = (speed * 62) / 99;  // Plage de PWM allant de -62 à +62

    // Décalage de 62 pour obtenir une plage de 0 à 124 (si nécessaire)
    pwmValue = pwmValue + 62;    
}
/*******************************************************************************
 End of File
 */
