/*******************************************************************************
  MPLAB Harmony Application Source File
  
  Company:
    Microchip Technology Inc.
  
  File Name:
    app_gen.c

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

#include "app_gen.h"
#include "app.h"             // Fichier principal de l'application (appData, etc.)
#include "Mc32DriverLcd.h"   // Gestion de l'affichage LCD
#include "Mc32gestSpiDac.h"  // Gestion SPI du DAC LTC2604
#include "MenuGen.h"         // Gestion du menu g�n�rique
#include "GesPec12.h"        // Gestion du codeur rotatif PEC12
#include "Generateur.h"      // Gestion du g�n�rateur de signal
#include "bsp.h"
#include "Mc32gest_I2c_Eeprom.h"

// *****************************************************************************
// *****************************************************************************
// Section: Global Data Definitions
// *****************************************************************************
// *****************************************************************************
APP_GEN_DATA appGenData; // Structure globale contenant l'�tat de l'application
S_ParamGen LocalParamGen; // Structure locale pour les param�tres du g�n�rateur
S_ParamGen RemoteParamGen;
bool saveRequested = false;
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

APP_GEN_DATA appGenData;

// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Functions
// *****************************************************************************
// *****************************************************************************

// -----------------------------------------------------------------------------

/**
 * @brief Callback Timer1 (1 ms). G�re des actions p�riodiques, notamment ScanBtn.
 * 
 * Appel� toutes les 1 ms, ce callback va inverser LED1_W, compter un d�lai
 * d'initialisation et g�rer la transition d'�tat de l'application.
 */
void App_Timer1Callback() {
    LED1_W = !LED1_R; // Inverse l'�tat de LED1_W en se basant sur LED1_R

    // Compteur pour les 3 premi�res secondes
    static uint16_t WaitIteration = 0; // Variable statique qui conserve sa valeur entre appels
    static uint8_t InitDone = 0; // Flag pour indiquer si l'init est termin�e

    // Lecture des signaux du codeur PEC12 et du bouton S9 (S_OK)
    ScanBtn(PEC12_A, PEC12_B, PEC12_PB, S_OK);

    // Pendant les 3 premi�res secondes, on incr�mente WaitIteration
    if ((WaitIteration <= WAIT_INIT) && (InitDone == 0)) {
        WaitIteration++; // Incr�mente le compteur d'attente
    } else {
        // Si on est toujours dans l'�tat d'attente d'init (APP_GEN_INIT_WAIT)
        if (appGenData.state == APP_GEN_STATE_INIT_WAIT) {
            APP_GEN_UpdateState(APP_GEN_STATE_INIT_CLEAR); // Change l'�tat de l'application
            WaitIteration = 0; // R�initialise le compteur
            InitDone = 1; // Note que l'init est termin�e
        } else {
            // Une fois l'init termin�e, on ex�cute p�riodiquement le SERVICE_TASKS
            if (WaitIteration >= 10) {
                WaitIteration = 0; // Reset du compteur
                APP_GEN_UpdateState(APP_GEN_STATE_SERVICE_TASKS); // Demande ex�cution des t�ches
            } else {
                WaitIteration++; // Incr�mente jusqu'� 10 pour la prochaine ex�cution
            }
        }
    }
}

// -----------------------------------------------------------------------------

/**
 * @brief Callback Timer3. G�re l'ex�cution du g�n�rateur de signal.
 * 
 * Appel� p�riodiquement, ce callback allume LED0, ex�cute la g�n�ration de signal,
 * puis �teint LED0.
 */
void App_Timer3Callback() { // Force LED0 � l'�tat bas (active)
    BSP_LEDOn(BSP_LED_0);
    GENSIG_Execute(); // G�n�re le signal selon les param�tres en cours
    BSP_LEDOff(BSP_LED_0);
}
// *****************************************************************************
// *****************************************************************************
// Section: Application Local Functions
// *****************************************************************************
// *****************************************************************************


/**
 * @brief Nettoie l'�cran LCD en effa�ant chacune des lignes 1 � 4.
 * 
 * @details Cette fonction appelle `lcd_ClearLine()` pour les 4 lignes du LCD,
 *          afin de supprimer tout affichage courant avant de r��crire des
 *          informations.
 */
void ClearLcd() {
    lcd_ClearLine(1); // Efface la ligne 1
    lcd_ClearLine(2); // Efface la ligne 2
    lcd_ClearLine(3); // Efface la ligne 3
    lcd_ClearLine(4); // Efface la ligne 4
}

/**
 * @brief Allume toutes les LEDs (actives � l'�tat bas).
 * 
 * @details Utilise les masques `LEDS_PORTA_MASK` et `LEDS_PORTB_MASK` pour
 *          positionner � 0 les bits correspondants sur PORTA et PORTB.
 */
void TurnOnAllLEDs(void) {
    // Lit l'�tat courant de PORTA, applique un AND avec l'inversion du masque
    PLIB_PORTS_Write(PORTS_ID_0, PORT_CHANNEL_A,
            PLIB_PORTS_Read(PORTS_ID_0, PORT_CHANNEL_A) & ~LEDS_PORTA_MASK);

    // Idem pour PORTB
    PLIB_PORTS_Write(PORTS_ID_0, PORT_CHANNEL_B,
            PLIB_PORTS_Read(PORTS_ID_0, PORT_CHANNEL_B) & ~LEDS_PORTB_MASK);
}

/**
 * @brief �teint toutes les LEDs (actives � l'�tat bas).
 * 
 * @details Utilise les masques `LEDS_PORTA_MASK` et `LEDS_PORTB_MASK` pour
 *          positionner � 1 les bits correspondants sur PORTA et PORTB.
 */
void TurnOffAllLEDs(void) {
    // Lit l'�tat courant de PORTA, applique un OR avec le masque
    PLIB_PORTS_Write(PORTS_ID_0, PORT_CHANNEL_A,
            PLIB_PORTS_Read(PORTS_ID_0, PORT_CHANNEL_A) | LEDS_PORTA_MASK);

    // Idem pour PORTB
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
    void APP_GEN_Initialize ( void )

  Remarks:
    See prototype in app_gen.h.
 */

void APP_GEN_Initialize ( void )
{
    APP_GEN_UpdateState(APP_GEN_STATE_INIT); // Positionne l'application en �tat d'init
}


/******************************************************************************
  Function:
    void APP_GEN_Tasks ( void )

  Remarks:
    See prototype in app_gen.h.
 */

void APP_GEN_Tasks ( void ) {
    bool UsbState;
    /* Check the application's current state. */
     // Machine � �tats principale du g�n�rateur de signal
    switch (appGenData.state) {

        case APP_GEN_STATE_INIT:
        {
            // �tat d'initialisation g�n�rale du syst�me

            // Initialise l'�cran LCD
            lcd_init();

            // Allume le r�tro�clairage du LCD
            lcd_bl_on();

            // Initialise le bus SPI pour le DAC LTC2604
            SPI_InitLTC2604();

            // Initialise le bus I2C pour le RTC MCP79411
            I2C_InitMCP79411();

            // Initialise le codeur rotatif PEC12
            Pec12Init();

            // Positionne le curseur � la ligne 1, colonne 1
            lcd_gotoxy(1, 1);

            // Affiche le titre du TP
            printf_lcd("TP4 UsbGen 2024-25");

            // Positionne le curseur � la ligne 2, colonne 1
            lcd_gotoxy(1, 2);

            // Affiche le nom de l'auteur
            printf_lcd("Leo Mendes");

            // D�marre le timer 0 (intervalles longs ou g�n�raux)
            DRV_TMR0_Start();

            // D�marre le timer 1 (intervalles courts pour les �tats)
            DRV_TMR1_Start();

            // Initialise les LEDs de la carte
            BSP_LEDInit();

            // Initialise le menu avec les param�tres locaux
            MENU_Initialize(&LocalParamGen);

            // Initialise le g�n�rateur de signal avec les param�tres locaux
            GENSIG_Initialize(&LocalParamGen);

            // Passe � l'�tat suivant : attente post-initialisation
            APP_GEN_UpdateState(APP_GEN_STATE_INIT_WAIT);

            break;
        }

        case APP_GEN_STATE_INIT_WAIT:
            // �tat d'attente apr�s initialisation, g�r� uniquement par Timer1
            break;

        case APP_GEN_STATE_INIT_CLEAR:
            // Efface l'�cran LCD apr�s le d�lai d'initialisation
            ClearLcd();

            // Passe � l'�tat d'attente normale
            APP_GEN_UpdateState(APP_GEN_STATE_WAIT);

            break;

        case APP_GEN_STATE_WAIT:
            // �tat d'attente passive entre deux actions ou cycles
            break;

        case APP_GEN_STATE_SERVICE_TASKS:
            // �tat de traitement p�riodique des t�ches

            // Bascule l'�tat de la LED_2 pour indiquer une activit�
            BSP_LEDToggle(BSP_LED_2);

            // Lit l'�tat courant de la connexion USB
            UsbState = GetUsbState();

            // V�rifie si le syst�me est en mode USB distant
            if (UsbState == true)
            {
                // Ex�cute le menu avec les param�tres re�us par USB
                MENU_Execute(&RemoteParamGen, UsbState, saveRequested);

                // Copie les param�tres distants vers les param�tres locaux
                LocalParamGen = RemoteParamGen;

            } else {
                // Ex�cute le menu avec les param�tres locaux
                MENU_Execute(&LocalParamGen, UsbState, saveRequested);

                // Copie les param�tres locaux vers les param�tres distants
                RemoteParamGen = LocalParamGen;
            }

            // Revient � l'�tat d'attente apr�s traitement
            APP_GEN_UpdateState(APP_GEN_STATE_WAIT);

            break;

        default:
        {
            // �tat non reconnu ou erreur de machine � �tats
            break;
        }
    }
}
/**
 * @brief Met � jour l'�tat de l'application.
 * 
 * @param NewState Le nouvel �tat � appliquer � l'application.
 * 
 * @details Cette fonction permet de forcer le passage d'un �tat � un autre
 *          depuis d'autres parties du code (ex: Timer1Callback).
 */
void APP_GEN_UpdateState(APP_GEN_STATES NewState) {
    appGenData.state = NewState; // Affecte le nouvel �tat
}

S_ParamGen* APP_GEN_GetRemoteParam(void)
{
    return &RemoteParamGen; // renvoie l?adresse
}

bool APP_GEN_saveRequested(void)
{
    return saveRequested;
}

void APP_GEN_clearSaveRequested(void)
{
    saveRequested = false;
}

void APP_GEN_setSaveRequested(bool value)
{
    saveRequested = value;
}

/*******************************************************************************
 End of File
 */
