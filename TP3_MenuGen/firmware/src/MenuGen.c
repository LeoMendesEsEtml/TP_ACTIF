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
S_ParamGen pParamSave;
//S_Pec12_Descriptor Pec12;

// Initialisation du menu et des paramètres
void MENU_Initialize(S_ParamGen *pParam) 
{

}

void MENU_Display(S_ParamGen *pParam, uint8_t menu) {
    const char MenuFormes [4] [21] = {"Sinus", "Triangle", "DentDeScie", "Carre"};
    ClearLcd();

    if (menu < 9) {
        lcd_gotoxy(2, 1);
        printf_lcd("Forme =");
        lcd_gotoxy(11, 1);
        printf_lcd("%s", MenuFormes[pParam->Forme]);

        lcd_gotoxy(2, 2);
        printf_lcd("Freq [Hz]");
        lcd_gotoxy(13, 2);
        printf_lcd("%d", pParam->Frequence);

        lcd_gotoxy(2, 3);
        printf_lcd("Ampl [mV]");
        lcd_gotoxy(13, 3);
        printf_lcd("%d", pParam->Amplitude);

        lcd_gotoxy(2, 4);
        printf_lcd("Offest [mV]");
        lcd_gotoxy(13, 4);
        printf_lcd("%d", (int) pParam->Offset);

        if (menu <= 4) {
            lcd_gotoxy(1, menu);
            printf_lcd("*");
        } else {
            menu = menu - 4;
            lcd_gotoxy(1, menu);
            printf_lcd("?");
        }
    } else {
        lcd_gotoxy(2, 2);
        printf_lcd("Sauvegarde ?");
        lcd_gotoxy(2, 3);
        printf_lcd("(appui long)");
    }
}

void MENU_Execute(S_ParamGen *pParam) {
    static MenuState_t menu = MENU_INIT;
    static uint8_t saveOk = 0;
    static uint8_t RefreshMenu = 0;
    static uint8_t wait2s = 0;


    switch (menu) {
        case MENU_INIT:
            NVM_ReadBlock((uint32_t*) & pParamSave, sizeof (S_ParamGen));
            //Test pour vérifier si MaGIC = MAGIC 
            if (pParamSave.Magic == MAGIC) {
                // Sauvegarde des valeurs récupérées
                *pParam = pParamSave;
                lcd_gotoxy(1, 4);
                printf_lcd("Donnees restaurees");
            } else {
                lcd_gotoxy(1, 4);
                printf_lcd("Donnees par defaut");

                // Initialisation des valeurs du générateur
                pParam->Amplitude = 0;
                pParam->Forme = SignalSinus;
                pParam->Frequence = 20;
                pParam->Magic = MAGIC;
                pParam->Offset = 0;
            }
            MENU_Display(pParam, MENU_FORME_SEL);
            menu = MENU_FORME_SEL;
            break;

        case MENU_FORME_SEL:
            if (RefreshMenu == 1) {
                RefreshMenu = 0;
                MENU_Display(pParam, MENU_FORME_SEL);
            }
            if (Pec12IsPlus()) {
                menu = MENU_FREQ_SEL;
                RefreshMenu = 1;
                Pec12ClearPlus();
            }
            if (Pec12IsMinus()) {
                menu = MENU_OFFSET_SEL;
                RefreshMenu = 1;
                Pec12ClearMinus();
            }
            if (Pec12IsOK()) {
                menu = MENU_FORME_EDIT;
                pParamSave = *pParam;
                RefreshMenu = 1;
                Pec12ClearOK();
            }

            break;

        case MENU_FORME_EDIT:
            if (RefreshMenu == 1) {
                RefreshMenu = 0;
                MENU_Display(pParam, MENU_FORME_EDIT);
            }
            if (Pec12IsPlus()) {
                pParam->Forme = (pParam->Forme + 1) % 4;
                RefreshMenu = 1;
                Pec12ClearPlus();

            }
            if (Pec12IsMinus()) {
                pParam->Forme = (pParam->Forme - 1 + 4) % 4;
                RefreshMenu = 1;
                Pec12ClearMinus();
            }
            if (Pec12IsOK()) {
                menu = MENU_FORME_SEL;
                RefreshMenu = 1;
                Pec12ClearOK();
            }
            if (Pec12IsESC()) {
                menu = MENU_FORME_SEL;
                pParam->Forme = pParamSave.Forme;
                RefreshMenu = 1;
                Pec12ClearESC();
            }

            if (S9IsOK()) {
                menu = MENU_SAUVEGARDE;
                RefreshMenu = 1;
                S9ClearOK();
            }
            break;

        case MENU_FREQ_SEL:
            if (RefreshMenu == 1) {
                RefreshMenu = 0;
                MENU_Display(pParam, MENU_FREQ_SEL);
            }
            if (Pec12IsPlus()) {
                menu = MENU_AMPL_SEL;
                RefreshMenu = 1;
                Pec12ClearPlus();
            }
            if (Pec12IsMinus()) {
                menu = MENU_FORME_SEL;
                RefreshMenu = 1;
                Pec12ClearMinus();
            }
            if (Pec12IsOK()) {
                menu = MENU_FREQ_EDIT;
                pParamSave = *pParam;
                RefreshMenu = 1;
                Pec12ClearOK();
            }
            break;

        case MENU_FREQ_EDIT:
            if (RefreshMenu == 1) {
                RefreshMenu = 0;
                MENU_Display(pParam, MENU_FREQ_EDIT);
            }
            if (Pec12IsPlus()) {
                pParam->Frequence += 20;
                if (pParam->Frequence > 2000) {
                    pParam->Frequence = 20;
                }
                RefreshMenu = 1;
                Pec12ClearPlus();
            }
            if (Pec12IsMinus()) {
                pParam->Frequence -= 20;
                if (pParam->Frequence < 20) {
                    pParam->Frequence = 2000;
                }
                RefreshMenu = 1;
                Pec12ClearMinus();
            }
            if (Pec12IsOK()) {
                menu = MENU_FREQ_SEL;
                RefreshMenu = 1;
                Pec12ClearOK();
            }
            if (Pec12IsESC()) {
                menu = MENU_FREQ_SEL;
                pParam->Frequence = pParamSave.Frequence;
                RefreshMenu = 1;
                Pec12ClearESC();
            }
            if (S9IsOK()) {
                menu = MENU_SAUVEGARDE;
                RefreshMenu = 1;
                S9ClearOK();
            }
            break;

        case MENU_AMPL_SEL:
            if (RefreshMenu == 1) {
                RefreshMenu = 0;
                MENU_Display(pParam, MENU_AMPL_SEL);
            }
            if (Pec12IsPlus()) {
                menu = MENU_OFFSET_SEL;
                RefreshMenu = 1;
                Pec12ClearPlus();
            }
            if (Pec12IsMinus()) {
                menu = MENU_FREQ_SEL;
                RefreshMenu = 1;
                Pec12ClearMinus();
            }
            if (Pec12IsOK()) {
                menu = MENU_AMPL_EDIT;
                pParamSave = *pParam;
                RefreshMenu = 1;
                Pec12ClearOK();
            }

            break;

        case MENU_AMPL_EDIT:
            if (RefreshMenu == 1) {
                RefreshMenu = 0;
                MENU_Display(pParam, MENU_AMPL_EDIT);
            }
            if (Pec12IsPlus()) {
                pParam->Amplitude += 100;
                if (pParam->Amplitude > 10000) {
                    pParam->Amplitude = 0;
                }
                RefreshMenu = 1;
                Pec12ClearPlus();
            }
            if (Pec12IsMinus()) {
                pParam->Amplitude -= 100;
                if (pParam->Amplitude < 0) {
                    pParam->Amplitude = 10000;
                }
                RefreshMenu = 1;
                Pec12ClearMinus();
            }
            if (Pec12IsOK()) {
                menu = MENU_AMPL_SEL;
                RefreshMenu = 1;
                Pec12ClearOK();
            }
            if (Pec12IsESC()) {
                menu = MENU_AMPL_SEL;
                pParam->Amplitude = pParamSave.Amplitude;
                RefreshMenu = 1;
                Pec12ClearESC();
            }
            if (S9IsOK()) {
                menu = MENU_SAUVEGARDE;
                RefreshMenu = 1;
                S9ClearOK();
            }
            break;

        case MENU_OFFSET_SEL:
            if (RefreshMenu == 1) {
                RefreshMenu = 0;
                MENU_Display(pParam, MENU_OFFSET_SEL);
            }
            if (Pec12IsPlus()) {
                menu = MENU_FORME_SEL;
                RefreshMenu = 1;
                Pec12ClearPlus();
            }
            if (Pec12IsMinus()) {
                menu = MENU_AMPL_SEL;
                RefreshMenu = 1;
                Pec12ClearMinus();
            }
            if (Pec12IsOK()) {
                menu = MENU_OFFSET_EDIT;
                pParamSave = *pParam;
                RefreshMenu = 1;
                Pec12ClearOK();
            }

            break;

        case MENU_OFFSET_EDIT:
            if (RefreshMenu == 1) {
                RefreshMenu = 0;
                MENU_Display(pParam, MENU_OFFSET_EDIT);
            }
            if (Pec12IsPlus()) {
                pParam->Offset += 100;
                if (pParam->Offset > 5000) pParam->Offset = -5000;
                RefreshMenu = 1;
                Pec12ClearPlus();
            }
            if (Pec12IsMinus()) {
                pParam->Offset -= 100;
                if (pParam->Offset < -5000) pParam->Offset = 5000;
                RefreshMenu = 1;
                Pec12ClearMinus();
            }
            if (Pec12IsOK()) {
                menu = MENU_OFFSET_SEL;
                RefreshMenu = 1;
                Pec12ClearOK();
            }
            if (Pec12IsESC()) {
                menu = MENU_OFFSET_SEL;
                pParam->Offset = pParamSave.Offset;
                RefreshMenu = 1;
                Pec12ClearESC();
            }
            if (S9IsOK()) {
                menu = MENU_SAUVEGARDE;
                RefreshMenu = 1;
                S9ClearOK();
            }

            break;

        case MENU_SAUVEGARDE:
            if (RefreshMenu == 1) {
                RefreshMenu = 0;
                MENU_Display(pParam, MENU_SAUVEGARDE);
            }

            if (S9IsESC()) {
                menu = MENU_SAVEINFO;
                saveOk = 1;
                RefreshMenu = 1;
                S9ClearESC();
            }
            else if ((Pec12IsPlus()) || (Pec12IsMinus()) || (Pec12IsOK())) {

                menu = MENU_SAVEINFO;
                saveOk = 0;
                RefreshMenu = 1;
            }
            break;
            
        case MENU_SAVEINFO:
            if (RefreshMenu == 1) {
                RefreshMenu = 0;
                ClearLcd();
                if (saveOk == 1) {
                    lcd_gotoxy(2, 3);
                    NVM_WriteBlock((uint32_t*) pParam, sizeof (S_ParamGen));
                    printf_lcd("Sauvegarde OK");
                } else {
                    lcd_gotoxy(2, 3);
                    printf_lcd("Sauvegarde ANNULEE!");
                }
            }
            wait2s++;
            if (wait2s == 200) {
                menu = MENU_FORME_SEL;
                RefreshMenu = 1;
            }
            break;
    }
}






