// Ecole supérieure SL229_MINF TP
// Manipulation Tp3_MenuGen
// Créé le 9 Mai 2006 CHR
// Version 2016  du 03.02.2016
// Modif 2015 : utilisation de stdint.h
// Modif 2016 : ajout Duty pour PWM
// Modif 2018 SCA : suppression PWM et duty
// Definition pour le menuGen

#ifndef DEFMENUGEN_H
#define DEFMENUGEN_H

#include <stdint.h>

#define MAGIC 0x123455AA
#define SELECT 0
#define EDIT 1

typedef enum  { SignalSinus, SignalTriangle, SignalDentDeScie, SignalCarre } E_FormesSignal;

// Structure des paramètres du générateur
typedef struct {
      E_FormesSignal Forme;
      int16_t Frequence;
      int16_t Amplitude;
      int16_t Offset;
      uint32_t Magic;
} S_ParamGen;

typedef enum {
    MENU_INIT = 0,
    MENU_FORME_SEL = 1,
    MENU_FREQ_SEL = 2,
    MENU_AMPL_SEL = 3, 
    MENU_OFFSET_SEL = 4,        
    MENU_FORME_EDIT = 5,
    MENU_FREQ_EDIT = 6,
    MENU_AMPL_EDIT = 7,
    MENU_OFFSET_EDIT = 8,
    MENU_SAUVEGARDE = 9,
    MENU_SAVEINFO = 10        
} MenuState_t;
#endif
