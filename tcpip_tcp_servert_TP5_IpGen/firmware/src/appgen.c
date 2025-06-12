/*******************************************************************************
  MPLAB Harmony Application Source File
  
  Company:
    Microchip Technology Inc.
  
  File Name:
    appgen.c

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

#include "appgen.h"
#include "Mc32DriverLcd.h"
#include <stdbool.h>          // Permet l'utilisation du type bool
#include "app.h"             // Fichier principal de l'application (appData, etc.)
#include "Mc32DriverLcd.h"   // Gestion de l'affichage LCD
#include "Mc32gestSpiDac.h"  // Gestion SPI du DAC LTC2604
#include "MenuGen.h"         // Gestion du menu générique
#include "GesPec12.h"        // Gestion du codeur rotatif PEC12
#include "Generateur.h"      // Gestion du générateur de signal
#include "system_definitions.h"

// *****************************************************************************
// *****************************************************************************
// Section: Global Data Definitions
// *****************************************************************************
// *****************************************************************************

APPGEN_DATA appgenData; // Structure globale contenant l'état de l'application
S_ParamGen LocalParamGen; // Structure locale pour les paramètres du générateur
S_ParamGen RemoteParamGen;

// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Functions
// *****************************************************************************
// *****************************************************************************
S_ParamGen* APP_GEN_GetRemoteParam(void)
{
    return &RemoteParamGen; // renvoie l?adresse
}



/**
 * @brief Callback Timer1 (1 ms). Gère des actions périodiques, notamment ScanBtn.
 * 
 * Appelé toutes les 1 ms, ce callback va inverser LED1_W, compter un délai
 * d'initialisation et gérer la transition d'état de l'application.
 */
void App_Timer1Callback() {
    LED1_W = !LED1_R; // Inverse l'état de LED1_W en se basant sur LED1_R

    // Compteur pour les 3 premières secondes
    static uint16_t WaitIteration = 0; // Variable statique qui conserve sa valeur entre appels
    static uint8_t InitDone = 0; // Flag pour indiquer si l'init est terminée

    // Lecture des signaux du codeur PEC12 et du bouton S9 (S_OK)
    ScanBtn(PEC12_A, PEC12_B, PEC12_PB, S_OK);

    // Pendant les 3 premières secondes, on incrémente WaitIteration
    if ((WaitIteration <= WAIT_INIT) && (InitDone == 0)) {
        WaitIteration++; // Incrémente le compteur d'attente
    } else {
        // Si on est toujours dans l'état d'attente d'init (APPGEN_INIT_WAIT)
        if (appgenData.state == APPGEN_STATE_INIT_WAIT) {
            APPGEN_UpdateState(APPGEN_STATE_INIT_CLEAR); // Change l'état de l'application
            WaitIteration = 0; // Réinitialise le compteur
            InitDone = 1; // Note que l'init est terminée
        } else {
            // Une fois l'init terminée, on exécute périodiquement le SERVICE_TASKS
            if (WaitIteration >= 10) {
                WaitIteration = 0; // Reset du compteur
                APPGEN_UpdateState(APPGEN_STATE_SERVICE_TASKS); // Demande exécution des tâches
            } else {
                WaitIteration++; // Incrémente jusqu'à 10 pour la prochaine exécution
            }
        }
    }
}

/**
 * @brief Callback Timer3. Gère l'exécution du générateur de signal.
 * 
 * Appelé périodiquement, ce callback allume LED0, exécute la génération de signal,
 * puis éteint LED0.
 */
void App_Timer3Callback() { // Force LED0 à l'état bas (active)
    BSP_LEDOn(BSP_LED_0);
    GENSIG_Execute(); // Génère le signal selon les paramètres en cours
    BSP_LEDOff(BSP_LED_0);
}


// *****************************************************************************
// *****************************************************************************
// Section: Application Local Functions
// *****************************************************************************
// *****************************************************************************
/**
 * @brief Nettoie l'écran LCD en effaçant chacune des lignes 1 à 4.
 * 
 * @details Cette fonction appelle `lcd_ClearLine()` pour les 4 lignes du LCD,
 *          afin de supprimer tout affichage courant avant de réécrire des
 *          informations.
 */
void ClearLcd() {
    lcd_ClearLine(1); // Efface la ligne 1
    lcd_ClearLine(2); // Efface la ligne 2
    lcd_ClearLine(3); // Efface la ligne 3
    lcd_ClearLine(4); // Efface la ligne 4
}
/**
 * @brief Met à jour l'état de l'application.
 * 
 * @param NewState Le nouvel état à appliquer à l'application.
 * 
 * @details Cette fonction permet de forcer le passage d'un état à un autre
 *          depuis d'autres parties du code (ex: Timer1Callback).
 */
void APPGEN_UpdateState(APPGEN_STATES NewState) {
    appgenData.state = NewState; // Affecte le nouvel état
}
// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void APPGEN_Initialize ( void )

  Remarks:
    See prototype in appgen.h.
 */

void APPGEN_Initialize ( void )
{
    /* Place the App state machine in its initial state. */
    appgenData.state = APPGEN_STATE_INIT;

    
    /* TODO: Initialize your application's state machine and other
     * parameters.
     */
}


/******************************************************************************
  Function:
    void APPGEN_Tasks ( void )

  Remarks:
    See prototype in appgen.h.
 */

void APPGEN_Tasks(void) {
    // Vérifie l'état courant de l'application
    switch (appgenData.state) {
        case APPGEN_STATE_INIT:
        {
            // Initialisation du LCD
            lcd_init();
            lcd_bl_on();

            // Initialisation du SPI pour le DAC
            SPI_InitLTC2604();

            // Initialisation du codeur PEC12
            Pec12Init();

            // Initialisation du menu
            MENU_Initialize(&LocalParamGen);

            // Initialisation du générateur
            GENSIG_Initialize(&LocalParamGen);

            // Affichage initial sur l'écran LCD
            lcd_gotoxy(1, 1);
            printf_lcd("TP5 IPGEN");

            lcd_gotoxy(1, 2);
            printf_lcd("Leo Mendes");

            lcd_gotoxy(1, 3);
            printf_lcd("Matteo Stefanelli");
            
            lcd_gotoxy(1, 4);
            printf_lcd("Port : 9760"); 

            // Démarre les timers TMR0 et TMR1
            DRV_TMR0_Initialize();
            DRV_TMR1_Initialize();
            DRV_TMR0_Start();
            DRV_TMR1_Start();
            
           RemoteParamGen = LocalParamGen;

            // Passe à l'état d'attente init
            appgenData.state = APPGEN_STATE_INIT_WAIT;
            break;
        }

        case APPGEN_STATE_INIT_WAIT:
            // Rien à faire de particulier ici, tout est géré par le callback Timer1
            lcd_gotoxy(1, 4);
            break;

        case APPGEN_STATE_INIT_CLEAR:
            // Efface l'écran LCD une fois l'init terminée (après 3s)
            ClearLcd();
            // Puis passe à l'état d'attente
            appgenData.state = APPGEN_STATE_WAIT;
            break;

        case APPGEN_STATE_WAIT:
            // Etat d'attente : on ne fait rien tant qu'on n'a pas été relancé par Timer1
            break;

        case APPGEN_STATE_SERVICE_TASKS:
            // Bascule une LED (LED_2) pour indiquer un cycle de service
            BSP_LEDToggle(BSP_LED_2);
            
            if (GetTcpState()) {
                MENU_Execute(&RemoteParamGen);
            } else {

                MENU_Execute(&LocalParamGen);
            }

            // Une fois fait, repasse en mode attente
            appgenData.state = APPGEN_STATE_WAIT;
            break;

        default:
        {
            // Etat par défaut (devrait ne jamais arriver).
            // On peut éventuellement y gérer une erreur système.
            break;
        }
    }
}

 

/*******************************************************************************
 End of File
 */
