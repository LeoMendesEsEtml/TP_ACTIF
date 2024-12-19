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
    // Exemple de lecture des ADC et mise à jour de la structure
    // pData->SpeedSetting = ReadADC1();
    // pData->AngleSetting = ReadADC2();
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
    // Lecture ADC
    ADC1_Conversion();
    ADC2_Conversion();     

    // Mettre à jour les paramètres du moteur à partir de la structure pData
    HBridgeControl(pData->SpeedSetting, pData->absSpeed, pData->absAngle);
}

// Execution PWM software
void GPWM_ExecPWMSoft(S_pwmSettings *pData)
{
    // Execution PWM software
    // À ajouter selon la logique du logiciel
}

void HBridgeControl(int8_t speed, uint8_t absSpeed, uint16_t absAngle) {
    // **Étape 1 : Gestion de la direction du pont en H**
    SetMotorDirection(speed);

    // **Étape 2 : Configuration pour OC2 (vitesse PWM)**
    uint16_t oc2PulseWidth = (absSpeed * PWM_MAX) / 99;  // absSpeed varie de 0 à 99
    PLIB_OC_PulseWidth16BitSet(2, oc2PulseWidth);

    // **Étape 3 : Configuration pour OC3 (angle PWM)**
    uint16_t oc3PulseWidth = (absAngle * PWM_MAX) / ANGLE_MAX;  // absAngle varie de 0 à 180
    PLIB_OC_PulseWidth16BitSet(3, oc3PulseWidth);
}

void SetMotorDirection(int8_t speed) {
    if (speed < 0) {
        // Configurer le pont en H pour tourner dans la direction négative
        STBY_HBRIDGE_BIT
    } else {
        // Configurer le pont en H pour tourner dans la direction positive
    }
}

void ADC1_Process(uint16_t adc1RawValue) {

    // Variables statiques pour ADC1
    static uint16_t adc1Values[ADC1_NUM_SAMPLES] = {0};  // Tableau circulaire
    static uint32_t adc1Sum = 0;                         // Somme pour la moyenne
    static uint8_t adc1Index = 0;                        // Index actuel

    static uint8_t adc1MappedSpeed = 0;                  // Valeur mappée (0-198)
    static int8_t adc1SignedSpeed = 0;                   // Vitesse signée (-99 à +99)
    static uint8_t adc1AbsSpeed = 0;                     // Vitesse absolue (0 à 99)

    // Mise à jour de la moyenne glissante
    adc1Sum -= adc1Values[adc1Index];
    adc1Values[adc1Index] = adc1RawValue;
    adc1Sum += adc1RawValue;
    adc1Index = (adc1Index + 1) % ADC1_NUM_SAMPLES;

    // Calcul de la moyenne de l'ADC
    uint16_t avgAdc1Value = adc1Sum / ADC1_NUM_SAMPLES;

    // Conversion de la moyenne en plage de 0 à 198
    adc1MappedSpeed = (avgAdc1Value * ADC1_VALUE_MAX) / ADC1_MAX;

    // Calcul de la vitesse signée (-99 à +99)
    adc1SignedSpeed = adc1MappedSpeed - (ADC1_VALUE_MAX / 2);

    // Calcul de la vitesse absolue (0 à 99)
    adc1AbsSpeed = (adc1SignedSpeed < 0) ? -adc1SignedSpeed : adc1SignedSpeed;

    // Mise à jour de la structure
    PWMData.absSpeed = adc1AbsSpeed;
    PWMData.SpeedSetting = adc1SignedSpeed;
}

void ADC2_Process(uint16_t adc2RawValue) {

    // Variables statiques pour ADC2
    static uint16_t adc2Values[ADC2_NUM_SAMPLES] = {0};  // Tableau circulaire
    static uint32_t adc2Sum = 0;                         // Somme pour la moyenne
    static uint8_t adc2Index = 0;                        // Index actuel

    static uint16_t adc2MappedAngle = 0;                    // Angle absolu (0-180)
    static int8_t adc2SignedAngle = 0;                   // Angle signé (-90 à +90)

    // Mise à jour de la moyenne glissante
    adc2Sum -= adc2Values[adc2Index];
    adc2Values[adc2Index] = adc2RawValue;
    adc2Sum += adc2RawValue;
    adc2Index = (adc2Index + 1) % ADC2_NUM_SAMPLES;

    // Calcul de la moyenne de l'ADC
    uint16_t avgAdc2Value = adc2Sum / ADC2_NUM_SAMPLES;

    // Conversion en angle absolu (0° à 180°)
    adc2MappedAngle = (avgAdc2Value * ADC2_ANGLE_MAX) / ADC2_MAX;

    // Conversion en angle signé (-90° à +90°)
    adc2SignedAngle = adc2MappedAngle - ADC2_ANGLE_OFFSET;

    // Mise à jour de la structure
    PWMData.absAngle = adc2MappedAngle;
    PWMData.AngleSetting = adc2SignedAngle;
}
