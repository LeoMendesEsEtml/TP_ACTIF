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
    
    lcd_gotoxy(1,selection);
    printf_lcd("*");
}

void MENU_Execute(S_ParamGen *pParam) {
    static uint8_t selection = 1;
    static bool editing = false;
    static const uint16_t minValues[4] = {0, 20, 0, -5000};
    static const uint16_t maxValues[4] = {3, 2000, 10000, 5000};
    static const uint16_t stepValues[4] = {1, 20, 100, 100};

    if (editing == false) {
        if (Pec12IsPlus() == true) {
            Pec12ClearPlus();
            selection++;
            if (selection >= 4) {
                selection = 1;
            }
        }
        if (Pec12IsMinus() == true) {
            Pec12ClearMinus();
            selection--;
            if (selection < 1) {
                selection = 3;
            }
        }
        if (Pec12IsOK() == true) {
            Pec12ClearOK();
            editing = true;
        }
        MENU_Display(pParam,selection);
    } else {
        if (Pec12IsPlus() == true) {
            Pec12ClearPlus();
            if (selection == 0) {
                pParam->Forme = pParam->Forme + 1;
                if (pParam->Forme > maxValues[0]) {
                    pParam->Forme = minValues[0];
                }
            } else if (selection == 1) {
                pParam->Frequence = pParam->Frequence + stepValues[1];
                if (pParam->Frequence > maxValues[1]) {
                    pParam->Frequence = minValues[1];
                }
            } else if (selection == 2) {
                pParam->Amplitude = pParam->Amplitude + stepValues[2];
                if (pParam->Amplitude > maxValues[2]) {
                    pParam->Amplitude = minValues[2];
                }
            } else if (selection == 3) {
                pParam->Offset = pParam->Offset + stepValues[3];
                if (pParam->Offset > maxValues[3]) {
                    pParam->Offset = minValues[3];
                }
            }
            MENU_Display(pParam, selection);
        }
        if (Pec12IsMinus() == true) {
            Pec12ClearMinus();
            if (selection == 0) {
                pParam->Forme = pParam->Forme - 1;
                if (pParam->Forme < minValues[0]) {
                    pParam->Forme = maxValues[0];
                }
            } else if (selection == 1) {
                pParam->Frequence = pParam->Frequence - stepValues[1];
                if (pParam->Frequence < minValues[1]) {
                    pParam->Frequence = maxValues[1];
                }
            } else if (selection == 2) {
                pParam->Amplitude = pParam->Amplitude - stepValues[2];
                if (pParam->Amplitude < minValues[2]) {
                    pParam->Amplitude = maxValues[2];
                }
            } else if (selection == 3) {
                pParam->Offset = pParam->Offset - stepValues[3];
                if (pParam->Offset < minValues[3]) {
                    pParam->Offset = maxValues[3];
                }
            }
        }
        if (Pec12IsOK() == true) {
            Pec12ClearOK();
            editing = false;
        }
        if (Pec12IsESC() == true) {
            Pec12ClearESC();
            editing = false;
        }
        if (S9IsOK() == true) {
            S9ClearOK();
            NVM_WriteBlock((uint32_t *) pParam, sizeof (S_ParamGen));
            lcd_gotoxy(2, 4);
            printf_lcd("Sauvegarde OK !");
        } else {
            MENU_Display(pParam, selection);
        }
    }
}





