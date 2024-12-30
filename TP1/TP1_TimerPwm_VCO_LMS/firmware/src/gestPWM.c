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

// Obtention vitesse et angle (mise à jour des 4 champs de la structure)
void GPWM_GetSettings(S_pwmSettings *pData)    
{
    #define TAILLE_MOYENNE_ADC 10
    // Lecture du convertisseur AD
    static uint8_t adcIndex = 0;
   
    //Variables statiques pour ADC1
    static uint16_t adc1Values[ADC1_NUM_SAMPLES] = {0};  // Tableau circulaire
    static uint32_t adc1Sum = 0; 
    static uint32_t averageAdc1 = 0;
    
    // Somme pour la moyenne
                       // Index actuel
    //Variables statiques pour ADC1
    static uint16_t adc2Values[ADC1_NUM_SAMPLES] = {0};  // Tableau circulaire
    static uint32_t adc2Sum = 0;                         // Somme pour la moyenne
    static uint32_t averageAdc2 = 0;    
    APP_DATA appData;

    
    // Lire les valeurs du convertisseur analogique-numérique
    appData.AdcRes = BSP_ReadAllADC();
    adc1Values[adcIndex] = appData.AdcRes.Chan0;
    adc2Values[adcIndex] = appData.AdcRes.Chan1;    
   
    adc1Sum = adc1Sum + adc1Values[adcIndex]; 
    adc2Sum = adc2Sum + adc2Values[adcIndex]; 
            
    adcIndex++;
    
    if (adcIndex > 9)
    {
        averageAdc1 = adc1Sum / ADC1_NUM_SAMPLES;
        averageAdc2 = adc2Sum / ADC2_NUM_SAMPLES;
        adcIndex = 0; 
        adc1Sum = 0;
        adc2Sum = 0; 
    }
    
    // Conversion
    ADC1_Conversion(averageAdc1, pData);
    ADC2_Conversion(averageAdc2, pData);     
}

// Affichage des informations en exploitant la structure
void GPWM_DispSettings(S_pwmSettings *pData)
{
    lcd_gotoxy(1,1); // Positionne le curseur à la première ligne
    printf_lcd("TP1 PWM 2024-25"); // Affiche un texte d'introduction
    lcd_gotoxy(1,2); 
    printf_lcd("Speed setting %d", pData->SpeedSetting); 
    lcd_gotoxy(1,3);
    printf_lcd("absSpeed: %d", pData->absSpeed);           
    lcd_gotoxy(1,4);
    printf_lcd("Angle: %d", pData->absAngle);     
}

// Execution PWM et gestion moteur à partir des informations dans la structure
void GPWM_ExecPWM(S_pwmSettings *pData)
{
    static uint16_t PulseWidthOC2;
    static uint16_t PulseWidthOC3;

    // Contrôle de l'état du pont en H en fonction de la vitesse
    if (pData->SpeedSetting < 0)
    {
        PLIB_PORTS_PinSet(PORTS_ID_0, AIN1_HBRIDGE_PORT, AIN1_HBRIDGE_BIT);
        PLIB_PORTS_PinClear(PORTS_ID_0, AIN2_HBRIDGE_PORT, AIN2_HBRIDGE_BIT);
    }
    else if (pData->SpeedSetting > 0)
    {
        PLIB_PORTS_PinClear(PORTS_ID_0, AIN1_HBRIDGE_PORT, AIN1_HBRIDGE_BIT);
        PLIB_PORTS_PinSet(PORTS_ID_0, AIN2_HBRIDGE_PORT, AIN2_HBRIDGE_BIT);
    }
    else
    {
        PLIB_PORTS_PinClear(PORTS_ID_0, AIN1_HBRIDGE_PORT, AIN1_HBRIDGE_BIT);
        PLIB_PORTS_PinClear(PORTS_ID_0, AIN2_HBRIDGE_PORT, AIN2_HBRIDGE_BIT);
    }

    // Calcul de la largeur d'impulsion (Pulse Width) pour la sortie OC2 en fonction de la vitesse
    PulseWidthOC2 = (pData->absSpeed * DRV_TMR1_PeriodValueGet()) / 100;
    DRV_OC0_PulseWidthSet( PulseWidthOC2);

    // Calcul de la largeur d'impulsion (Pulse Width) pour la sortie OC3 en fonction de l'angle
    PulseWidthOC3 = ((pData->absAngle * 9000) / 180) + 2999;
    DRV_OC0_PulseWidthSet( PulseWidthOC3); 
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

void ADC1_Conversion(uint32_t adc1RawValue,S_pwmSettings *pData) 
{
    static uint8_t adc1MappedSpeed = 0;                  // Valeur mappée (0-198)
    static int8_t adc1SignedSpeed = 0;                   // Vitesse signée (-99 à +99)
    static uint8_t adc1AbsSpeed = 0;                     // Vitesse absolue (0 à 99)
    
    // Conversion de la moyenne en plage de 0 à 198
    adc1MappedSpeed = (adc1RawValue * ADC1_VALUE_MAX) / ADC1_MAX;

    // Calcul de la vitesse signée (-99 à +99)
    adc1SignedSpeed = adc1MappedSpeed - (ADC1_VALUE_MAX / 2);

    // Calcul de la vitesse absolue (0 à 99)
    if (adc1SignedSpeed < 0) {
        adc1AbsSpeed = -adc1SignedSpeed;
    } 
    else 
    {
        adc1AbsSpeed = adc1SignedSpeed;
    }

    // Mise à jour de la structure
    pData->SpeedSetting = adc1SignedSpeed;
    pData->absSpeed =  adc1AbsSpeed;
}

void ADC2_Conversion(uint32_t adc2RawValue,S_pwmSettings *pData) 
{

    // Variables statiques pour ADC2
    static uint16_t adc2Values[ADC2_NUM_SAMPLES] = {0};  // Tableau circulaire
    static uint32_t adc2Sum = 0;                         // Somme pour la moyenne
    static uint8_t adc2Index = 0;                        // Index actuel

    static uint16_t adc2MappedAngle = 0;                    // Angle absolu (0-180)
    static int8_t adc2SignedAngle = 0;                   // Angle signé (-90 à +90)

    // Mise à jour de la moyenne glissante
    adc2Sum = adc2Sum - adc2Values[adc2Index];
    adc2Values[adc2Index] = adc2RawValue;
    adc2Sum = adc2Sum + adc2RawValue;
    adc2Index = (adc2Index + 1) % ADC2_NUM_SAMPLES;

    // Calcul de la moyenne de l'ADC
    uint16_t avgAdc2Value = adc2Sum / ADC2_NUM_SAMPLES;

    // Conversion en angle absolu (0° à 180°)
    adc2MappedAngle = (avgAdc2Value * ADC2_ANGLE_MAX) / ADC2_MAX;

    // Conversion en angle signé (-90° à +90°)
    adc2SignedAngle = adc2MappedAngle - ADC2_ANGLE_OFFSET;

    // Mise à jour de la structure
    pData->AngleSetting = adc2SignedAngle;   
}
