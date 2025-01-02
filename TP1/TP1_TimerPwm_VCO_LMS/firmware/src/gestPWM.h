#ifndef GestPWM_H
#define GestPWM_H

/*--------------------------------------------------------*/
// GestPWM.h
/*--------------------------------------------------------*/
// Description : Gestion des PWM 
//               pour TP1 2016-2017
//
// Auteur       : C. HUBER
//
// Version      : V1.1
// Compilateur  : XC32 V1.42 + Harmony 1.08
//
// Modification : 1.12.2023 SCA : enlevé decl. PWMData extern
//
/*--------------------------------------------------------*/

<<<<<<< Updated upstream
#include <stdint.h>

// Définitions constantes ADC1
#define ADC1_MAX 1023         // Valeur maximale de l'ADC (10 bits)
#define ADC1_VALUE_MAX 198    // Plage mappée (0 à 198)

// Définitions constantes ADC2
#define ADC2_MAX 1023         // Valeur maximale de l'ADC (10 bits)
=======
#include <stdint.h>                  // Types standard (uint8_t, etc.)
#include "app.h"                    // Dépendances applicatives
#include "bsp.h"                    // Gestion des ADC et matériel de base
#include "Mc32DriverLcd.h"          // Pilote pour écran LCD
#include "Mc32DriverAdc.h"          // Pilote pour ADC
#include "peripheral/oc/plib_oc.h"  // Pilote pour Output Compare

/*--------------------------------------------------------*/
// Définitions des constantes
/*--------------------------------------------------------*/

// Définitions constantes ADC1
#define ADC_SAMPLING_SIZE 10  // Taille des buffers pour moyennes glissantes
#define ADC1_MAX 1023         // Résolution maximale de l'ADC (10 bits)
#define ADC1_VALUE_MAX 198    // Plage mappée pour vitesse (0 à 198)

// Définitions constantes ADC2
#define ADC2_MAX 1023         // Résolution maximale de l'ADC (10 bits)
>>>>>>> Stashed changes
#define ADC2_ANGLE_MAX 180    // Plage angulaire (0° à 180°)
#define ADC2_ANGLE_OFFSET 90  // Décalage pour angle (-90° à +90°)

<<<<<<< Updated upstream
=======
// Gestions des Output compare 
#define PWM_OC2_SCALE 125    // Échelle pour le calcul de la largeur d'impulsion OC2
#define PWM_OC2_DIV 99       // Diviseur pour normaliser la largeur d'impulsion OC2

#define PWM_OC3_MIN 749      // Valeur minimale pour la largeur d'impulsion OC3
#define PWM_OC3_MAX 2999     // Valeur maximale pour la largeur d'impulsion OC3
#define PWM_OC3_DIV 180      // Diviseur pour normaliser la largeur d'impulsion OC3
>>>>>>> Stashed changes
/*--------------------------------------------------------*/
// Définition de la structure S_pwmSettings
/*--------------------------------------------------------*/

/**
 * @brief Structure contenant les paramètres pour la gestion des PWM.
 */
typedef struct {
    uint8_t absSpeed;    // Vitesse absolue (0 à 99)
    uint8_t absAngle;    // Angle absolu (0 à 180)
    int8_t SpeedSetting; // Consigne de vitesse (-99 à +99)
    int8_t AngleSetting; // Consigne d'angle (-90 à +90)
} S_pwmSettings;

<<<<<<< Updated upstream
=======
/*--------------------------------------------------------*/
// Prototypes des fonctions
/*--------------------------------------------------------*/
>>>>>>> Stashed changes

/**
 * @brief Initialise la structure PWM et configure le matériel associé.
 * @param pData Pointeur vers la structure S_pwmSettings à initialiser.
 */
void GPWM_Initialize(S_pwmSettings *pData);

<<<<<<< Updated upstream
// Ces 4 fonctions ont pour paramètre un pointeur sur la structure S_pwmSettings.
void GPWM_GetSettings(S_pwmSettings *pData);    // Obtention vitesse et angle
void GPWM_DispSettings(S_pwmSettings *pData);    // Affichage
void GPWM_ExecPWM(S_pwmSettings *pData);         // Execution PWM et gestion moteur.
void GPWM_ExecPWMSoft(S_pwmSettings *pData);     // Execution PWM software.
void ADC1_Conversion(void);
void ADC2_Conversion(void);
=======
/**
 * @brief Lit les données des ADC pour calculer la vitesse et l'angle.
 * @param pData Pointeur vers la structure S_pwmSettings à mettre à jour.
 */
void GPWM_GetSettings(S_pwmSettings *pData);
>>>>>>> Stashed changes

/**
 * @brief Affiche les paramètres PWM (vitesse et angle) sur un écran LCD.
 * @param pData Pointeur vers la structure S_pwmSettings à afficher.
 */
void GPWM_DispSettings(S_pwmSettings *pData);

/**
 * @brief Exécute la PWM pour le contrôle du moteur en fonction des consignes.
 * @param pData Pointeur vers la structure S_pwmSettings utilisée pour le contrôle.
 */
void GPWM_ExecPWM(S_pwmSettings *pData);

/**
 * @brief Génère une PWM logicielle pour simuler un signal PWM.
 * @param pData Pointeur vers la structure S_pwmSettings utilisée pour la génération.
 */
void GPWM_ExecPWMSoft(S_pwmSettings *pData);

#endif // GestPWM_H
