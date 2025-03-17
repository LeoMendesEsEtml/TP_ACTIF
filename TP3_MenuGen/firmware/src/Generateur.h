#ifndef Generateur_h
#define Generateur_h

// TP3 MenuGen 2016
// C. HUBER  03.02.2016
// Fichier Generateur.h
// Prototypes des fonctions du g�n�rateur  de signal

#include <math.h>
#include <stdint.h>
#include <stdbool.h>

#include "DefMenuGen.h"

//d�finition des constantes
#define FREQU_SYS 80000000 //fr�quence du timer 3
#define ECHANTILLONS_MAX 100 //nombre max d'�chantillons
#define AMPLITUDE_MAX 10000
#define AMPLITUDE_MIN -10000
#define AMPLITUDE_SUR_2 5000
#define PAS_MAXIMUM 65535
#define PRESC_TIM3 64



// Initialisation du  g�n�rateur
void  GENSIG_Initialize(S_ParamGen *pParam);


// Mise � jour de la periode d'�chantillonage
void  GENSIG_UpdatePeriode(S_ParamGen *pParam);


// Mise � jour du signal (forme, amplitude, offset)
void  GENSIG_UpdateSignal(S_ParamGen *pParam);

// A appeler dans int Timer3
void  GENSIG_Execute(void);


#endif