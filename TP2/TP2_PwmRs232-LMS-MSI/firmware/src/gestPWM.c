/*--------------------------------------------------------*/
// GestPWM.c
/*--------------------------------------------------------*/
//	Description :	Gestion des PWM 
//			        pour TP1 2016-2017
//
//	Auteur 		: 	C. HUBER
//
//	Version		:	V1.1
//	Compilateur	:	XC32 V1.42 + Harmony 1.08
//
/*--------------------------------------------------------*/
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
#include "gestPWM.h"            // gestion des pwm
#include "peripheral/oc/plib_oc.h"  // Pilote pour Output Compare

S_pwmSettings PWMData;  // pour les settings

/**
 * @brief Initialise les paramètres et l'état pour le module PWM.
 * @author LMS - VCO
 * @date 2025-01-02
 *
 * @param pData Pointeur vers une structure S_pwmSettings contenant les paramètres PWM à initialiser.
 *
 * @details Cette fonction initialise les données PWM à leurs valeurs par défaut,
 *          active le pont en H et démarre les timers ainsi que les sorties de comparaison (OC).
 */
void GPWM_Initialize(S_pwmSettings *pData)
{
    // Initialisation des paramètres PWM
    pData->absSpeed = 0;        // Vitesse absolue initialisée à 0
    pData->absAngle = 0;        // Angle absolu initialisé à 0
    pData->SpeedSetting = 0;    // Réglage de vitesse initialisé à 0

    // Activation du pont en H pour la commande moteur
    BSP_EnableHbrige();

    // Démarrage des timers nécessaires au fonctionnement du PWM
    DRV_TMR0_Start(); // Timer 1
    DRV_TMR1_Start(); // Timer 2
    DRV_TMR2_Start(); // Timer 3
    // Le timer 4 dois être activé une fois l'initialisation débutée ou les condition de
    // D'init ne sont pas complète = LED4 CLignotte car PWM Actif
    //DRV_TMR3_Start(); // Timer 4

    // Démarrage des sorties de comparaison pour générer les signaux PWM
    DRV_OC0_Start(); // Output Compare N°0 = OC2
    DRV_OC1_Start(); // Output Compare N°1 = OC3
}

/**
 * @brief Lit les paramètres PWM à partir des valeurs des ADC (moyennes glissantes).
 * @author LMS - VCO
 * @date 2025-01-02
 *
 * @param pData Pointeur vers une structure S_pwmSettings pour stocker les paramètres calculés.
 *
 * @details Cette fonction lit les résultats bruts des ADC, calcule les moyennes glissantes
 *          pour les canaux spécifiés, et met à jour les réglages de vitesse et d'angle
 *          dans la structure `pData`.
 */
void GPWM_GetSettings(S_pwmSettings *pData) {
    // Buffers circulaires pour les valeurs ADC du canal 1 (statique pour conserver les données entre appels)
    static uint16_t adc1Values[ADC_SAMPLING_SIZE] = {0}; // Stocke les dernières valeurs ADC du canal 1
    static uint32_t adc1Sum = 0; // Somme des valeurs dans le buffer circulaire du canal 1
    // Buffers circulaires pour les valeurs ADC du canal 2 (statique pour conserver les données entre appels)
    static uint16_t adc2Values[ADC_SAMPLING_SIZE] = {0}; // Stocke les dernières valeurs ADC du canal 2
    static uint32_t adc2Sum = 0; // Somme des valeurs dans le buffer circulaire du canal 2
    // Index statique pour suivre la position actuelle dans les buffers circulaires
    static uint8_t index = 0;

    // Variables intermédiaires pour le traitement
    static uint32_t avgAdc1 = 0; // Moyenne glissante pour le canal 1
    static uint32_t avgAdc2 = 0; // Moyenne glissante pour le canal 2
    static int16_t speedSigned = 0; // Vitesse signée calculée à partir du canal 1
    static uint8_t speedAbsolute = 0; // Vitesse absolue calculée à partir de speedSigned
    static uint8_t angle = 0; // Angle calculé à partir du canal 2

    // Lecture des valeurs brutes des ADC à partir du matériel
    S_ADCResults adcResults = BSP_ReadAllADC(); // Récupère les dernières mesures des canaux ADC

    // Mise à jour des buffers circulaires pour le canal 1
    adc1Sum = adc1Sum - adc1Values[index]; // Retire la plus ancienne valeur de la somme
    adc1Values[index] = adcResults.Chan0; // Ajoute la nouvelle valeur dans le buffer
    adc1Sum = adc1Sum + adc1Values[index]; // Ajoute la nouvelle valeur à la somme

    // Mise à jour des buffers circulaires pour le canal 2
    adc2Sum = adc2Sum - adc2Values[index]; // Retire la plus ancienne valeur de la somme
    adc2Values[index] = adcResults.Chan1; // Ajoute la nouvelle valeur dans le buffer
    adc2Sum = adc2Sum + adc2Values[index]; // Ajoute la nouvelle valeur à la somme

    // Incrémentation de l'index et gestion du débordement
    index = (index + 1) % ADC_SAMPLING_SIZE; // Passe à l'emplacement suivant dans le buffer circulaire

    // Calcul des moyennes glissantes
    avgAdc1 = adc1Sum / ADC_SAMPLING_SIZE; // Moyenne glissante des valeurs ADC pour le canal 1
    avgAdc2 = adc2Sum / ADC_SAMPLING_SIZE; // Moyenne glissante des valeurs ADC pour le canal 2

    // Conversion des données ADC du canal 1 en une vitesse signée
    speedSigned = ((avgAdc1 * ADC1_VALUE_MAX) / ADC1_MAX) - (ADC1_VALUE_MAX / 2); // Centre les valeurs autour de 0

    // Calcul de la vitesse absolue
    if (speedSigned < 0) {
        speedAbsolute = -speedSigned; // Si la vitesse est négative, on prend la valeur absolue
    } else {
        speedAbsolute = speedSigned; // Sinon, on garde la valeur telle quelle
    }

    // Mise à jour de la structure avec les valeurs calculées pour la vitesse
    pData->SpeedSetting = speedSigned; // Met à jour la vitesse signée (-99 à +99)
    pData->absSpeed = speedAbsolute;   // Met à jour la vitesse absolue (0 à 99)

    // Conversion des données ADC du canal 2 en un angle absolu
    angle = (avgAdc2 * ADC2_ANGLE_MAX) / ADC2_MAX; // Échelle la valeur entre 0 et 180
    pData->absAngle = angle; // Met à jour l'angle absolu (0 à 180 degrés)
}

/**
 * @brief Affiche les paramètres PWM sur l'écran LCD.
 * @author LMS - VCO
 * @date 2025-01-02
 *
 * @param pData Pointeur vers une structure S_pwmSettings contenant les paramètres à afficher.
 *
 * @details Cette fonction met à jour les lignes de l'écran LCD avec les informations suivantes :
 *          - Ligne 1 : Titre statique.
 *          - Ligne 2 : Vitesse signée (SpeedSetting).
 *          - Ligne 3 : Vitesse absolue (absSpeed).
 *          - Ligne 4 : Angle ajusté (absAngle).
 */
void GPWM_DispSettings(S_pwmSettings *pData)
{
    // Ligne 1 : Message statique
    lcd_gotoxy(1, 1); // Positionne le curseur en haut à gauche
    printf_lcd("TP1 PWM 2024-25"); // Affiche le message statique

    // Ligne 2 : Vitesse signée (SpeedSetting)
    lcd_gotoxy(1, 2); // Place le curseur pour le texte statique
    printf_lcd("Speed:"); // Affiche l'étiquette "Speed"

    lcd_gotoxy(11, 2); // Place la valeur à la colonne 11
    if (pData->SpeedSetting == 0)
    {
        // Afficher "0" sans signe, sur 3 caractères pour garder l'alignement
        printf_lcd("%3d", pData->SpeedSetting); // Exemple : "  0"
    }
    else if (pData->SpeedSetting > 0)
    {
        // Vitesse positive
        if (pData->SpeedSetting < 10)
        {
            // 1 chiffre
            printf_lcd(" +%1d", pData->SpeedSetting); // Exemple : " +5"
        }
        else
        {
            // 2 chiffres ou plus
            printf_lcd("+%2d", pData->SpeedSetting); // Exemple : "+12"
        }
    }
    else
    {
        // Vitesse négative
        printf_lcd("%3d", pData->SpeedSetting); // Exemple : "-15"
    }


    // Ligne 3 : Vitesse absolue (absSpeed)
    lcd_gotoxy(1, 3); // Place le curseur pour le texte statique
    printf_lcd("AbsSpeed:"); // Affiche l'étiquette "AbsSpeed"

    lcd_gotoxy(11, 3); // Place la valeur à la colonne 11
    printf_lcd("%3d", pData->absSpeed); // Affiche la vitesse absolue sur 3 caractères, exemple : " 99"

    // Ligne 4 : Angle ajusté (absAngle)
    lcd_gotoxy(1, 4); // Place le curseur pour le texte statique
    printf_lcd("Angle:"); // Affiche l'étiquette "Angle"

    lcd_gotoxy(11, 4); // Place la valeur à la colonne 11
    printf_lcd("%3d", pData->absAngle - 90); // Affiche l'angle ajusté (-90 à +90) sur 3 caractères
}

/**
 * @brief Exécute la PWM et contrôle le moteur en fonction des paramètres.
 * @author LMS - VCO
 * @date 2025-01-02
 *
 * @param pData Pointeur vers une structure S_pwmSettings contenant les paramètres de vitesse et d'angle.
 *
 * @details Cette fonction gère le contrôle du pont en H pour la direction du moteur, calcule la largeur
 *          d'impulsion pour les canaux PWM (OC2 et OC3), et met à jour ces largeurs en fonction des
 *          paramètres fournis.
 */
void GPWM_ExecPWM(S_pwmSettings *pData)
{
    // Variables pour les largeurs d'impulsion PWM
    static uint16_t PulseWidthOC2;
    static uint16_t PulseWidthOC3;

    // Contrôle de l'état du pont en H en fonction de la vitesse
    if (pData->SpeedSetting < 0)
    {
        // Direction négative : active AIN1 et désactive AIN2
        PLIB_PORTS_PinSet(PORTS_ID_0, AIN1_HBRIDGE_PORT, AIN1_HBRIDGE_BIT);
        PLIB_PORTS_PinClear(PORTS_ID_0, AIN2_HBRIDGE_PORT, AIN2_HBRIDGE_BIT);
    }
    else if (pData->SpeedSetting > 0)
    {
        // Direction positive : active AIN2 et désactive AIN1
        PLIB_PORTS_PinClear(PORTS_ID_0, AIN1_HBRIDGE_PORT, AIN1_HBRIDGE_BIT);
        PLIB_PORTS_PinSet(PORTS_ID_0, AIN2_HBRIDGE_PORT, AIN2_HBRIDGE_BIT);
    }
    else
    {
        // Vitesse nulle : désactive les deux entrées du pont en H
        PLIB_PORTS_PinClear(PORTS_ID_0, AIN1_HBRIDGE_PORT, AIN1_HBRIDGE_BIT);
        PLIB_PORTS_PinClear(PORTS_ID_0, AIN2_HBRIDGE_PORT, AIN2_HBRIDGE_BIT);
    }

    // Calcul de la largeur d'impulsion pour OC2 (PWM pour la vitesse)
    PulseWidthOC2 = pData->absSpeed * PWM_OC2_SCALE; // Étape 1 : Multiplie par l'échelle 125
    PulseWidthOC2 = PulseWidthOC2 / PWM_OC2_DIV;   // Étape 2 : Divise par 99 pour normaliser (0% à 100%)
    PLIB_OC_PulseWidth16BitSet(OC_ID_2, PulseWidthOC2); // Applique la largeur calculée à OC2

    // Calcul de la largeur d'impulsion pour OC3 (PWM pour l'angle)
    PulseWidthOC3 = ((pData->absAngle * (PWM_OC3_MAX - PWM_OC3_MIN)) / PWM_OC3_DIV) + PWM_OC3_MIN; // 0.6 ms à 2.4 ms
    PLIB_OC_PulseWidth16BitSet(OC_ID_3, PulseWidthOC3); // Applique la largeur calculée à OC3
}

/**
 * @brief Exécute une PWM logicielle pour le contrôle d'une LED.
 * @author LMS - VCO
 * @date 2025-01-02
 *
 * @param pData Pointeur vers une structure S_pwmSettings contenant les paramètres de vitesse (absSpeed).
 *
 * @details Cette fonction génère une PWM logicielle en contrôlant l'état de la LED BSP_LED_2
 *          en fonction de la vitesse absolue. La période est fixe (100 cycles).
 */
void GPWM_ExecPWMSoft(S_pwmSettings *pData)
{
    // Compteur pour générer la PWM logicielle
    static uint8_t pwmCounter = 0;

    // Gestion de l'état de la LED en fonction de la vitesse absolue
    if (pwmCounter < pData->absSpeed || pData->absSpeed == 99)
    {
        // Lorsque le compteur est inférieur à la vitesse absolue (ON)
        BSP_LEDOff(BSP_LED_2); // État logique pour éteindre la LED
    }
    else
    {
        // Sinon, allumer la LED
        BSP_LEDOn(BSP_LED_2); // État logique pour allumer la LED
    }

    // Incrémentation du compteur
    pwmCounter = pwmCounter + 1;

    // Réinitialisation du compteur après 100 cycles
    if (pwmCounter >= 100)
    {
        pwmCounter = 0;
    }
}
