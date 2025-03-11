// Tp3  manipulation MenuGen avec PEC12
// C. HUBER  10/02/2015 pour SLO2 2014-2015
// Fichier MenuGen.c
// Gestion du menu  du générateur
// Traitement cyclique à 10 ms
#include <stdint.h>                   
#include <stdbool.h>
#include "app.h"
#include "MenuGen.h"
#include "Mc32DriverLcd.h"
#include "GesPec12.h"
#include "Mc32NVMUtil.h"

//S_Pec12_Descriptor Pec12;

// Initialisation du menu et des paramètres
void MENU_Initialize(S_ParamGen *pParam) 
{
    
}

void MENU_Display(S_ParamGen *pParam, uint8_t selection)
{
    const char MenuFormes [4] [21] = { "Sinus", "Triangle", "DentDeScie", "Carre" };
    ClearLcd();
    lcd_bl_on();
    
    lcd_gotoxy(2, 1);
    printf_lcd("Forme =");
    lcd_gotoxy(11,1);
    printf_lcd("%s", MenuFormes[pParam->Forme]);
    
    lcd_gotoxy(2, 2);
    printf_lcd("Freq [Hz]");
    lcd_gotoxy(13,2);
    printf_lcd("%d", pParam->Frequence);

    lcd_gotoxy(2, 3);
    printf_lcd("Ampl [mV]");
    lcd_gotoxy(13,3);
    printf_lcd("%d", pParam->Amplitude);
    
    lcd_gotoxy(2, 4);
    printf_lcd("Offest [mV]");
    lcd_gotoxy(13,4);
    printf_lcd("%d", (int)pParam->Offset);
   
}

void MENU_Execute(S_ParamGen *pParam) {
    static MenuState_t menu = MENU_FORME_SEL;
    static uint8_t Timer_S9 = 0; // Timer pour la détection de l'appui long sur S9
    const char MenuFormes[4][21] = {"Sinus", "Triangle", "DentDeScie", "Carre"};

    switch (menu) {
        case MENU_FORME_SEL:
            if (Pec12IsPlus()) {
                menu = MENU_FREQ_SEL;
                ClearLcd();
                Pec12ClearPlus();
            }
            if (Pec12IsMinus()) {
                menu = MENU_OFFSET_SEL;
                ClearLcd();
                Pec12ClearMinus();
            }
            if (Pec12IsOK()) {  
                menu = MENU_FORME_EDIT;
                ClearLcd();
                Pec12ClearOK();
            }
            if (S9IsOK() && Timer_S9 >= 200) {  
                menu = MENU_FORME_EDIT;
                Timer_S9 = 0;
                ClearLcd();
                S9ClearOK();
            }
            MENU_Display(pParam, 1);
            lcd_gotoxy(1, 1);
            printf_lcd("*");
            break;

        case MENU_FORME_EDIT:
            if (Pec12IsPlus()) {
                pParam->Forme = (pParam->Forme + 1) % 4;
                Pec12ClearPlus();
                ClearLcd();
            }
            if (Pec12IsMinus()) {
                pParam->Forme = (pParam->Forme - 1 + 4) % 4;
                Pec12ClearMinus();
                ClearLcd();
            }
            if (Pec12IsOK()) {  
                menu = MENU_FORME_SEL;
                Pec12ClearOK();
                ClearLcd();
            }
            if (S9IsOK()) {  
                menu = MENU_FORME_SEL;
                pParam->Forme = NVM_ReadParam()->Forme;
                ClearLcd();
                S9ClearOK();
            }
            MENU_Display(pParam, 1);
            lcd_gotoxy(1, 1);
            printf_lcd("?");
            break;

        case MENU_FREQ_SEL:
            if (Pec12IsPlus()) {
                menu = MENU_AMPL_SEL;
                ClearLcd();
                Pec12ClearPlus();
            }
            if (Pec12IsMinus()) {
                menu = MENU_FORME_SEL;
                ClearLcd();
                Pec12ClearMinus();
            }
            if (Pec12IsOK()) {
                menu = MENU_FREQ_EDIT;
                ClearLcd();
                Pec12ClearOK();
            }
            MENU_Display(pParam, 2);
            lcd_gotoxy(1, 2);
            printf_lcd("*");
            break;

        case MENU_FREQ_EDIT:
            if (Pec12IsPlus()) {
                pParam->Frequence += 10;
                if (pParam->Frequence > 2000) pParam->Frequence = 20;
                Pec12ClearPlus();
                ClearLcd();
            }
            if (Pec12IsMinus()) {
                pParam->Frequence -= 10;
                if (pParam->Frequence < 20) pParam->Frequence = 2000;
                Pec12ClearMinus();
                ClearLcd();
            }
            if (Pec12IsOK()) {
                menu = MENU_FREQ_SEL;
                Pec12ClearOK();
                ClearLcd();
            }
            if (S9IsOK()) {
                menu = MENU_FREQ_SEL;
                pParam->Frequence = NVM_ReadParam()->Frequence;
                ClearLcd();
                S9ClearOK();
            }
            MENU_Display(pParam, 2);
            lcd_gotoxy(1, 2);
            printf_lcd("?");
            break;

        case MENU_AMPL_SEL:
            if (Pec12IsPlus()) {
                menu = MENU_OFFSET_SEL;
                ClearLcd();
                Pec12ClearPlus();
            }
            if (Pec12IsMinus()) {
                menu = MENU_FREQ_SEL;
                ClearLcd();
                Pec12ClearMinus();
            }
            if (Pec12IsOK()) {
                menu = MENU_AMPL_EDIT;
                ClearLcd();
                Pec12ClearOK();
            }
            MENU_Display(pParam, 3);
            lcd_gotoxy(1, 3);
            printf_lcd("*");
            break;

        case MENU_AMPL_EDIT:
            if (Pec12IsPlus()) {
                pParam->Amplitude += 100;
                if (pParam->Amplitude > 10000) pParam->Amplitude = 0;
                Pec12ClearPlus();
                ClearLcd();
            }
            if (Pec12IsMinus()) {
                pParam->Amplitude -= 100;
                if (pParam->Amplitude < 0) pParam->Amplitude = 10000;
                Pec12ClearMinus();
                ClearLcd();
            }
            if (Pec12IsOK()) {
                menu = MENU_AMPL_SEL;
                Pec12ClearOK();
                ClearLcd();
            }
            if (S9IsOK()) {
                menu = MENU_AMPL_SEL;
                pParam->Amplitude = NVM_ReadParam()->Amplitude;
                ClearLcd();
                S9ClearOK();
            }
            MENU_Display(pParam, 3);
            lcd_gotoxy(1, 3);
            printf_lcd("?");
            break;

        case MENU_OFFSET_SEL:
            if (Pec12IsPlus()) {
                menu = MENU_FORME_SEL;
                ClearLcd();
                Pec12ClearPlus();
            }
            if (Pec12IsMinus()) {
                menu = MENU_AMPL_SEL;
                ClearLcd();
                Pec12ClearMinus();
            }
            if (Pec12IsOK()) {
                menu = MENU_OFFSET_EDIT;
                ClearLcd();
                Pec12ClearOK();
            }
            MENU_Display(pParam, 4);
            lcd_gotoxy(1, 4);
            printf_lcd("*");
            break;

        case MENU_OFFSET_EDIT:
            if (Pec12IsPlus()) {
                pParam->Offset += 100;
                if (pParam->Offset > 5000) pParam->Offset = -5000;
                Pec12ClearPlus();
                ClearLcd();
            }
            if (Pec12IsMinus()) {
                pParam->Offset -= 100;
                if (pParam->Offset < -5000) pParam->Offset = 5000;
                Pec12ClearMinus();
                ClearLcd();
            }
            if (Pec12IsOK()) {
                menu = MENU_OFFSET_SEL;
                Pec12ClearOK();
                ClearLcd();
            }
            if (S9IsOK()) {
                menu = MENU_OFFSET_SEL;
                pParam->Offset = NVM_ReadParam()->Offset;
                ClearLcd();
                S9ClearOK();
            }
            MENU_Display(pParam, 4);
            lcd_gotoxy(1, 4);
            printf_lcd("?");
            break;

        case MENU_SAUVEGARDE:
            if (S9IsOK()) {
                menu = MENU_FORME_SEL;
                Timer_S9 = 0;
                ClearLcd();
            }
            if (Pec12IsOK()) {
                NVM_WriteBlock((uint32_t *) pParam, sizeof(S_ParamGen));
                lcd_gotoxy(6, 2);
                printf_lcd("Sauvegarde OK !");
                menu = MENU_FORME_SEL;
                Timer_S9 = 0;
            }
            break;
    }

    Pec12ClearInactivity();
    Pec12ClearPlus();
    Pec12ClearMinus();
    Pec12ClearOK();
    Pec12ClearESC();
    S9ClearOK();
}






