#ifndef GestPWM_H
#define GestPWM_H
/*--------------------------------------------------------*/
// GestPWM.h
/*--------------------------------------------------------*/
//	Description :	Gestion des PWM 
//			        pour TP1 2016-2017
//
//	Auteur 		: 	C. HUBER
//
//	Version		:	V1.1
//	Compilateur	:	XC32 V1.42 + Harmony 1.08
//
//  Modification : 1.12.2023 SCA : enleve decl. PWMData extern
//
/*--------------------------------------------------------*/

#include <stdint.h>

// Définitions constantes ADC1
#define ADC1_MAX 1023         // Valeur maximale de l'ADC (10 bits)
#define ADC1_VALUE_MAX 198    // Plage mappée (0 à 198)

// Définitions constantes ADC2
#define ADC2_MAX 1023         // Valeur maximale de l'ADC (10 bits)
#define ADC2_ANGLE_MAX 180    // Plage angulaire (0° à 180°)
#define ADC2_ANGLE_OFFSET 90  // Décalage angulaire (-90° à +90°)

/*--------------------------------------------------------*/
// Définition des fonctions prototypes
/*--------------------------------------------------------*/

typedef struct {
    uint8_t absSpeed;    // vitesse 0 à 99
    uint8_t absAngle;    // Angle  0 à 180
    int8_t SpeedSetting; // consigne vitesse -99 à +99
    int8_t AngleSetting; // consigne angle  -90 à +90
} S_pwmSettings;


void GPWM_Initialize(S_pwmSettings *pData);

// Ces 4 fonctions ont pour paramètre un pointeur sur la structure S_pwmSettings.
void GPWM_GetSettings(S_pwmSettings *pData);    // Obtention vitesse et angle
void GPWM_DispSettings(S_pwmSettings *pData);    // Affichage
void GPWM_ExecPWM(S_pwmSettings *pData);         // Execution PWM et gestion moteur.
void GPWM_ExecPWMSoft(S_pwmSettings *pData);     // Execution PWM software.
void ADC1_Conversion(void);
void ADC2_Conversion(void);

#endif
