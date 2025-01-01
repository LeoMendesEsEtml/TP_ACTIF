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


#include "bsp.h"
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include "Mc32DriverLcd.h"
#include "GestPWM.h"
#include "app.h"
#include "Mc32DriverAdc.h"


S_pwmSettings PWMData;  // pour les settings

void GPWM_Initialize(S_pwmSettings *pData)
{
    // Init les data
    pData->absSpeed = 0;
    pData->absAngle = 0;
    pData->SpeedSetting = 0;
    pData->AngleSetting = 0;

    // Init état du pont en H
    BSP_EnableHbrige(); 

    // lance les timers et OC
    DRV_TMR0_Start();
    DRV_TMR1_Start();
    DRV_TMR2_Start();
    DRV_TMR3_Start();
    DRV_OC0_Start();
    DRV_OC1_Start();    
}

/* Corrections pour la gestion ADC1 et ADC2 avec moyenne glissante et conversions */
#include "GestPWM.h"
#include "Mc32DriverAdc.h"

#define TAILLE_MOYENNE_ADC 10

void GPWM_GetSettings(S_pwmSettings *pData) {
    static uint16_t adc1Values[TAILLE_MOYENNE_ADC] = {0};
    static uint32_t adc1Sum = 0;
    static uint16_t adc2Values[TAILLE_MOYENNE_ADC] = {0};
    static uint32_t adc2Sum = 0;
    static uint8_t index = 0;

    // Lire les valeurs brutes des ADC
    S_ADCResults adcResults = BSP_ReadAllADC();

    // Mise à jour des buffers circulaires
    adc1Sum = adc1Sum - adc1Values[index];
    adc1Values[index] = adcResults.Chan0;
    adc1Sum = adc1Sum + adc1Values[index];

    adc2Sum = adc2Sum - adc2Values[index];
    adc2Values[index] = adcResults.Chan1;
    adc2Sum = adc2Sum + adc2Values[index];

    // Incrémenter l'index et gérer le débordement
    index = (index + 1) % TAILLE_MOYENNE_ADC;

    // Calculer les moyennes glissantes
    uint32_t avgAdc1 = adc1Sum / TAILLE_MOYENNE_ADC;
    uint32_t avgAdc2 = adc2Sum / TAILLE_MOYENNE_ADC;

    // Conversion ADC1 (vitesse)
    int16_t speedSigned = ((avgAdc1 * ADC1_VALUE_MAX) / ADC1_MAX) - (ADC1_VALUE_MAX / 2);
    uint8_t speedAbsolute;
    if (speedSigned < 0) {
        speedAbsolute = -speedSigned;
    } else {
        speedAbsolute = speedSigned;
    }

    pData->SpeedSetting = speedSigned; // Vitesse signée (-99 à +99)
    pData->absSpeed = speedAbsolute;  // Vitesse absolue (0 à 99)

    // Conversion ADC2 (angle)
    uint8_t angle = (avgAdc2 * ADC2_ANGLE_MAX) / ADC2_MAX;
    pData->absAngle = angle; // Angle absolu (0 à 180)
}

void GPWM_DispSettings(S_pwmSettings *pData) {
    // Ligne 1 : Message statique
    lcd_gotoxy(1, 1);
    printf_lcd("TP1 PWM 2024-25");

    // Ligne 2 : Vitesse signée (Speed)
    lcd_gotoxy(1, 2); // Texte statique
    printf_lcd("Speed:");
    lcd_gotoxy(14 - 3, 2); // Aligne le dernier chiffre à la colonne 14
    if (pData->SpeedSetting >= 0) {
        if (pData->SpeedSetting < 10) {
            printf_lcd(" +%1d", pData->SpeedSetting); // Ajoute un espace avant si un seul chiffre
        } else {
            printf_lcd("+%2d", pData->SpeedSetting); // Pas d'espace supplémentaire
        }
    } else {
        printf_lcd("%3d", pData->SpeedSetting);  // Alignement des négatifs
    }

    // Ligne 3 : Vitesse absolue (AbsSpeed)
    lcd_gotoxy(1, 3); // Texte statique
    printf_lcd("AbsSpeed:");
    lcd_gotoxy(14 - 3, 3); // Place le dernier chiffre à la colonne 14
    printf_lcd("%3d", pData->absSpeed); // Affiche la valeur

    // Ligne 4 : Angle (Angle)
    lcd_gotoxy(1, 4); // Texte statique
    printf_lcd("Angle:");
    lcd_gotoxy(14 - 3, 4); // Place le dernier chiffre à la colonne 14
    printf_lcd("%3d", pData->absAngle); // Affiche la valeur
}




// Execution PWM et gestion moteur à partir des informations dans la structure
void GPWM_ExecPWM(S_pwmSettings *pData) {
    static uint16_t PulseWidthOC2;
    static uint16_t PulseWidthOC3;

    // Contrôle de l'état du pont en H en fonction de la vitesse
    if (pData->SpeedSetting < 0) {
        PLIB_PORTS_PinSet(PORTS_ID_0, AIN1_HBRIDGE_PORT, AIN1_HBRIDGE_BIT);
        PLIB_PORTS_PinClear(PORTS_ID_0, AIN2_HBRIDGE_PORT, AIN2_HBRIDGE_BIT);
    } else if (pData->SpeedSetting > 0) {
        PLIB_PORTS_PinClear(PORTS_ID_0, AIN1_HBRIDGE_PORT, AIN1_HBRIDGE_BIT);
        PLIB_PORTS_PinSet(PORTS_ID_0, AIN2_HBRIDGE_PORT, AIN2_HBRIDGE_BIT);
    } else {
        PLIB_PORTS_PinClear(PORTS_ID_0, AIN1_HBRIDGE_PORT, AIN1_HBRIDGE_BIT);
        PLIB_PORTS_PinClear(PORTS_ID_0, AIN2_HBRIDGE_PORT, AIN2_HBRIDGE_BIT);
    }

    // Calcul de la largeur d'impulsion pour OC2 (moteur DC)
    PulseWidthOC2 = (pData->absSpeed * 124) / 100;  // Période du Timer 2
    DRV_OC0_PulseWidthSet(PulseWidthOC2);

    // Calcul de la largeur d'impulsion pour OC3 (servomoteur)
    PulseWidthOC3 = ((pData->absAngle * 4374) / 90) + 2999;  // 4374 pour 50% de la plage
    DRV_OC1_PulseWidthSet(PulseWidthOC3);
}


// Execution PWM software
void GPWM_ExecPWMSoft(S_pwmSettings *pData)
{
    static uint8_t RPMCnt = 0;

    // Si la valeur absolue de la vitesse est supérieure au compteurRpc, éteindre la LED
    if (pData->absSpeed > RPMCnt)
    {
        BSP_LEDOff(BSP_LED_2);
    }
    else
    {
        // Sinon, allumer la LED
        BSP_LEDOn(BSP_LED_2);
    }

    // Incrémente le compteurRpc
    RPMCnt++;

    // Remet à zéro le compteurRpc s'il dépasse la valeur 99
    if (RPMCnt > 99)
    {
        RPMCnt = 0;
    }
}

