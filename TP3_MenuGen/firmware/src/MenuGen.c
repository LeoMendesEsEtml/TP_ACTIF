// Tp3  manipulation MenuGen avec PEC12
// C. HUBER  10/02/2015 pour SLO2 2014-2015
// Fichier MenuGen.c
// Gestion du menu  du générateur
// Traitement cyclique à 10 ms
#include <stdint.h>                   
#include <stdbool.h>
#include "MenuGen.h"
#include "Mc32DriverLcd.h"


// Initialisation du menu et des paramètres
void MENU_Initialize(S_ParamGen *pParam) {
    lcd_gotoxy(2, 1);
    printf_lcd("Forme ="); 

    lcd_gotoxy(2, 2);
    printf_lcd("Freq [Hz]"); 

    lcd_gotoxy(2, 3);
    printf_lcd("Ampl [mV]");
    
    lcd_gotoxy(2, 4);
    printf_lcd("Offest [mV]");
}


// Execution du menu, appel cyclique depuis l'application
void MENU_Execute(S_ParamGen *pParam)
{
    
}




