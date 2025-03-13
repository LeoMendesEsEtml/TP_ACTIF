// GesPec12.c  Canevas pour r�alisation  
// C. HUBER    09/02/2015

// Fonctions pour la gestion du Pec12
//
//
// Principe : Il est n�cessaire d'appeler cycliquement la fonction ScanPec12
//            avec un cycle de 1 ms
//
//  Pour la gestion du Pec12, il y a 9 fonctions � disposition :
//       Pec12IsPlus       true indique un nouveau incr�ment
//       Pec12IsMinus      true indique un nouveau d�cr�ment
//       Pec12IsOK         true indique action OK
//       Pec12IsESC        true indique action ESC
//       Pec12NoActivity   true indique abscence d'activit� sur PEC12
//  Fonctions pour quittance des indications
//       Pec12ClearPlus    annule indication d'incr�ment
//       Pec12ClearMinus   annule indication de d�cr�ment
//       Pec12ClearOK      annule indication action OK
//       Pec12ClearESC     annule indication action ESC
//
//
//---------------------------------------------------------------------------


#include "GesPec12.h"
#include "Mc32Debounce.h"
#include "Mc32DriverLcd.h"

#define AFK_TIME 5000 // Dur�e d'inactivit� avant extinction du r�tro�clairage

// Descripteurs des signaux
S_SwitchDescriptor DescrA;
S_SwitchDescriptor DescrB;
S_SwitchDescriptor DescrPB;
S_SwitchDescriptor DescrS9;

// Structures pour le PEC12 et le bouton S9
S_Pec12_Descriptor Pec12;
S_PB_Descriptor S9;

void Pec12Init(void)
{
    // Initialisation des descripteurs de touches
    DebounceInit(&DescrA);
    DebounceInit(&DescrB);
    DebounceInit(&DescrPB);
    DebounceInit(&DescrS9);

    // Initialisation des variables du PEC12
    Pec12.Inc = 0;
    Pec12.Dec = 0;
    Pec12.OK = 0;
    Pec12.ESC = 0;
    Pec12.NoActivity = 0;
    Pec12.PressDuration = 0;
    Pec12.InactivityDuration = 0;

    S9.OK = 0;
    Pec12.ESC = 0;
    Pec12.NoActivity = 0;
    Pec12.PressDuration = 0;
    Pec12.InactivityDuration = 0;
}

void ScanBtn(bool ValA, bool ValB, bool ValPB, bool ValS9)
{   
    // Anti-rebond sur A, B, PB et S9
    DoDebounce(&DescrA, ValA);
    DoDebounce(&DescrB, ValB);
    DoDebounce(&DescrPB, ValPB);
    DoDebounce(&DescrS9, ValS9);

    // ================================
    // D�tection de l'incr�ment / d�cr�ment
    // ================================
    if (DebounceIsPressed(&DescrB)) {
        DebounceClearPressed(&DescrB);
        Pec12.NoActivity = 1; // R�initialise l'inactivit�

        if (DebounceGetInput(&DescrA) == 0) {
            Pec12.Inc = 1; // Incr�mentation
            Pec12.Dec = 0; // S'assure que d�cr�ment est d�sactiv�
        } else {
            Pec12.Dec = 1; // D�cr�mentation
            Pec12.Inc = 0; // S'assure que incr�ment est d�sactiv�
        }
    }

    // ================================
    // Gestion du bouton poussoir (PB)
    // ================================
    if (DebounceIsPressed(&DescrPB)) {
        Pec12.NoActivity = 1;
        DebounceClearPressed(&DescrPB);
        Pec12.PressDuration = 0;
    } 
    else if (DebounceGetInput(&DescrPB) == 0) {
        Pec12.PressDuration++;
    }       
    else if (DebounceIsReleased(&DescrPB)) {
        DebounceClearReleased(&DescrPB);

        if (Pec12.PressDuration < 500) {
            Pec12.OK = 1; // Appui bref ? OK
        } else {
            Pec12.ESC = 1; // Appui long ? ESC
        }
        
        Pec12.PressDuration = 0; // R�initialisation apr�s traitement
    }

    // ================================
    // Gestion du bouton S9
    // ================================
    static uint8_t lastS9State = 1;
    if (ValS9 == 0 && lastS9State == 1) {
        S9.OK = 1; // D�tection d'un appui sur S9
    } else {
        S9.OK = 0;
    }
    lastS9State = ValS9;

    // ================================
    // Gestion de l'inactivit�
    // ================================
    if ((Pec12.NoActivity == 0)) {
        if (Pec12.InactivityDuration >= AFK_TIME) {
            lcd_bl_off();
        }
        else {
            Pec12.InactivityDuration++;
        }
    } else {
        Pec12ClearInactivity();
        lcd_bl_on();
    }
   
}


// ================================
// Fonctions de test des �v�nements
// ================================
bool Pec12IsPlus(void) { return (Pec12.Inc); }
bool Pec12IsMinus(void) { return (Pec12.Dec); }
bool Pec12IsOK(void) { return (Pec12.OK); }
bool Pec12IsESC(void) { return (Pec12.ESC); }
bool Pec12NoActivity(void) { return (Pec12.NoActivity); }
bool S9IsOK(void) { return (S9.OK); }

// ================================
// Fonctions pour annuler les �v�nements
// ================================
void Pec12ClearPlus(void) { Pec12.Inc = 0; }
void Pec12ClearMinus(void) { Pec12.Dec = 0; }
void Pec12ClearOK(void) { Pec12.OK = 0; }
void Pec12ClearESC(void) { Pec12.ESC = 0; }
void Pec12ClearInactivity(void) { Pec12.NoActivity = 0; Pec12.InactivityDuration = 0; }
void S9ClearOK(void) { S9.OK = 0; }