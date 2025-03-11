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


// d�finitions des types qui seront utilis�s dans cette application

#include "GesPec12.h"
#include "Mc32Debounce.h"
#include "Mc32DriverLcd.h"

#define INACTIVITY_THRESHOLD 5000
#define PRESS_THRESHOLD 500
// Descripteur des sinaux
S_SwitchDescriptor DescrA;
S_SwitchDescriptor DescrB;
S_SwitchDescriptor DescrPB;
S_SwitchDescriptor DescrS9;

// Structure pour les traitement du Pec12
S_Pec12_Descriptor Pec12;
// Structure pour les traitement du S9
S_PB_Descriptor S9;



//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// Principe utilisation des fonctions
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//
//
// ScanPec12 (bool ValA, bool ValB, bool ValPB)
//              Routine effectuant la gestion du Pec12
//              recoit la valeur des signaux et du boutons
//
// s'appuie sur le descripteur global.
// Apr�s l'appel le descripteur est mis � jour

// Comportement du PEC12
// =====================

// Attention 1 cran g�n�re une pulse compl�te (les 4 combinaisons)
// D'ou traitement uniquement au flanc descendand de B

// Dans le sens horaire CW:
//     __________                      ________________
// B:            |____________________|
//     ___________________                       _________
// A:                     |_____________________|                    

// Dans le sens anti-horaire CCW:
//     ____________________                      _________
// B:                      |____________________|
//     __________                       __________________
// A:            |_____________________|        

void ScanBtn(bool ValA, bool ValB, bool ValPB, bool ValS9) {
    // Traitement anti-rebond sur A, B, PB et S9
    DoDebounce(&DescrA, ValA);
    DoDebounce(&DescrB, ValB);
    DoDebounce(&DescrPB, ValPB);
    DoDebounce(&DescrS9, ValS9);

    // D�tection du flanc descendant sur B pour d�terminer la rotation
    if (DebounceIsReleased(&DescrB)) {
        DebounceClearReleased(&DescrB);
        Pec12.InactivityDuration = 0;  // R�initialisation de l'inactivit�

        if (DebounceGetInput(&DescrA) == 0) {
            Pec12.Inc = 1;
            Pec12.Dec = 0;
        } else {
            Pec12.Inc = 0;
            Pec12.Dec = 1;
        }
        Pec12.NoActivity = 0;
    } else {
        // Remettre � z�ro si pas de rotation d�tect�e
        Pec12.Inc = 0;
        Pec12.Dec = 0;
    }

    // Gestion du bouton poussoir du PEC12 (PB)
    if (DebounceIsPressed(&DescrPB)) {
        Pec12.OK = 1;
        Pec12.ESC = 0;
        Pec12.NoActivity = 0;
        DebounceClearPressed(&DescrPB);
    } else if (DebounceIsReleased(&DescrPB)) {
        Pec12.OK = 0;
        Pec12.ESC = 1;
        DebounceClearReleased(&DescrPB);
    }

    // Gestion du bouton S9 (Sauvegarde) ? Appuy� = 1, Rel�ch� = 0
    if (DebounceIsPressed(&DescrS9)) {
        S9.OK = 1;
        S9.NoActivity = 0;
        DebounceClearPressed(&DescrS9);
    } else if (DebounceIsReleased(&DescrS9)) {
        S9.OK = 0;
        DebounceClearReleased(&DescrS9);
    }

    // Gestion de l?inactivit�
    if (Pec12.InactivityDuration < INACTIVITY_THRESHOLD) {
        Pec12.InactivityDuration++;
    } else {
        Pec12.NoActivity = 1;
        lcd_bl_off();
    }
}

void Pec12Init (void)
{
   // Initialisation des descripteurs de touches Pec12
   DebounceInit(&DescrA);
   DebounceInit(&DescrB);
   DebounceInit(&DescrPB);
   DebounceInit(&DescrS9);
   
   // Init de la structure PEc12
    Pec12.Inc = 0;             // �v�nement incr�ment  
    Pec12.Dec = 0;             // �v�nement d�cr�ment 
    Pec12.OK = 0;              // �v�nement action OK
    Pec12.ESC = 0;             // �v�nement action ESC
    Pec12.NoActivity = 0;      // Indication d'activit�
    Pec12.PressDuration = 0;   // Pour dur�e pression du P.B.
    Pec12.InactivityDuration = 0; // Dur�e inactivit�
  
 } // Pec12Init

//       Pec12IsPlus       true indique un nouveau incr�ment
bool Pec12IsPlus    (void) {
   return (Pec12.Inc);
}

//       Pec12IsMinus      true indique un nouveau d�cr�ment
bool Pec12IsMinus    (void) {
   return (Pec12.Dec);
}

//       Pec12IsOK         true indique action OK
bool Pec12IsOK    (void) {
   return (Pec12.OK);
}

//       Pec12IsESC        true indique action ESC
bool Pec12IsESC    (void) {
   return (Pec12.ESC);
}

//       Pec12NoActivity   true indique abscence d'activit� sur PEC12
bool Pec12NoActivity    (void) {
   return (Pec12.NoActivity);
}

//  Fonctions pour quittance des indications
//       Pec12ClearPlus    annule indication d'incr�ment
void Pec12ClearPlus   (void) {
   Pec12.Inc = 0;
}

//       Pec12ClearMinus   annule indication de d�cr�ment
void Pec12ClearMinus   (void) {
   Pec12.Dec = 0;
}

//       Pec12ClearOK      annule indication action OK
void Pec12ClearOK   (void) {
   Pec12.OK = 0;
}

//       Pec12ClearESC     annule indication action ESC
void Pec12ClearESC   (void) {
   Pec12.ESC = 0;
}

void Pec12ClearInactivity   (void) {
  Pec12.NoActivity = 0;
  Pec12.InactivityDuration = 0;
}

//       S9IsOK          true indique action OK
bool S9IsOK    (void) {
   return (S9.OK);
}

//       Pec12ClearOK      annule indication action OK
void S9ClearOK   (void) {
   S9.OK = 0;
}
