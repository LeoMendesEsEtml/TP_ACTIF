// GesPec12.c  Canevas pour réalisation  
// C. HUBER    09/02/2015

// Fonctions pour la gestion du Pec12
//
//
// Principe : Il est nécessaire d'appeler cycliquement la fonction ScanPec12
//            avec un cycle de 1 ms
//
//  Pour la gestion du Pec12, il y a 9 fonctions à disposition :
//       Pec12IsPlus       true indique un nouveau incrément
//       Pec12IsMinus      true indique un nouveau décrément
//       Pec12IsOK         true indique action OK
//       Pec12IsESC        true indique action ESC
//       Pec12NoActivity   true indique abscence d'activité sur PEC12
//  Fonctions pour quittance des indications
//       Pec12ClearPlus    annule indication d'incrément
//       Pec12ClearMinus   annule indication de décrément
//       Pec12ClearOK      annule indication action OK
//       Pec12ClearESC     annule indication action ESC
//
//
//---------------------------------------------------------------------------


// définitions des types qui seront utilisés dans cette application

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
// Après l'appel le descripteur est mis à jour

// Comportement du PEC12
// =====================

// Attention 1 cran génère une pulse complète (les 4 combinaisons)
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
    // Traitement antirebond sur A, B et PB
    DoDebounce(&DescrA, ValA);
    DoDebounce(&DescrB, ValB);
    DoDebounce(&DescrPB, ValPB);
    DoDebounce(&DescrS9, ValS9);

    //gestion rotation codeur
    if (DebounceIsPressed(&DescrB) && (DebounceGetInput(&DescrA) == 0)) {
        Pec12.Dec = 0;
        Pec12.Inc = 1;
        Pec12.NoActivity = 0;
        DebounceClearPressed(&DescrB);
    } else if (DebounceIsPressed(&DescrB) && (DebounceGetInput(&DescrA) == 1)) {
        Pec12.Inc = 0;
        Pec12.Dec = 1;
        Pec12.NoActivity = 0;
        DebounceClearPressed(&DescrB);
    }

    //gestion enfoncement bouton codeur
    if (DebounceIsPressed(&DescrPB)) {  //btn blanc d'appui
        DebounceClearPressed(&DescrB);
        Pec12.PressDuration = 0;
        Pec12.NoActivity = 0;
    }
    else if (DebounceGetInput(&DescrPB) == 0)  //btn maintenu enfoncé
    {
        Pec12.PressDuration++;
        Pec12.NoActivity = 0;
    }       
    else if (DebounceIsReleased(&DescrPB)) {//btn blanc relachement
        DebounceClearPressed(&DescrPB);
        if (Pec12.PressDuration >= PRESS_THRESHOLD) {
            Pec12.OK = 0;
            Pec12.ESC = 1;
        } else {
            Pec12.ESC = 0;
            Pec12.OK = 1;
        }
        Pec12.PressDuration = 0;
        Pec12.NoActivity = 0;
    }

//    //gestion bouton S9
//    if (DebounceIsPressed(&DescrS9)) {
//        DebounceClearPressed(&DescrS9);
//        S9.PressDuration++;
//        S9.NoActivity = 0;
////        if (DebounceIsReleased(&DescrS9)) {
////            DebounceClearPressed(&DescrS9);
//        }
//    }
//    else if ()
//
//    if (DebounceIsReleased(&DescrS9)) {
//        S9.PressDuration = 0;
//        S9.NoActivity = 0;
//        if (S9.PressDuration >= PRESS_THRESHOLD) {
//            S9.OK = 1;
//        }
//        DebounceClearReleased(&DescrS9);
//
//    }

    if (Pec12.InactivityDuration < INACTIVITY_THRESHOLD)    //dernière activité < 5 sec
    {
        Pec12.InactivityDuration++;
    }
    else //inactif depuis >= 5 sec
    {
        Pec12.NoActivity = 1;
    }
    
//    if ((Pec12.Dec == 0) && (Pec12.Inc == 0) && (DescrPB.bits.KeyValue == 1) && (S9.PressDuration == 0)) {
//        if ((Pec12.InactivityDuration < INACTIVITY_THRESHOLD) &&
//                (S9.InactivityDuration < INACTIVITY_THRESHOLD)) {
//            Pec12.InactivityDuration++;
//            S9.InactivityDuration++;
//        } else {
//            lcd_bl_off();
//            Pec12.NoActivity = 1;
//            S9.NoActivity = 1;
//        }
//    } else if ((Pec12.NoActivity == 1)&&(S9.NoActivity == 1)) {
//        lcd_bl_on();
//        Pec12.NoActivity = 0;
//        S9.NoActivity = 0;
//    }
} // ScanPec12


void Pec12Init (void)
{
   // Initialisation des descripteurs de touches Pec12
   DebounceInit(&DescrA);
   DebounceInit(&DescrB);
   DebounceInit(&DescrPB);
   DebounceInit(&DescrS9);
   
   // Init de la structure PEc12
    Pec12.Inc = 0;             // événement incrément  
    Pec12.Dec = 0;             // événement décrément 
    Pec12.OK = 0;              // événement action OK
    Pec12.ESC = 0;             // événement action ESC
    Pec12.NoActivity = 0;      // Indication d'activité
    Pec12.PressDuration = 0;   // Pour durée pression du P.B.
    Pec12.InactivityDuration = 0; // Durée inactivité
  
 } // Pec12Init

//       Pec12IsPlus       true indique un nouveau incrément
bool Pec12IsPlus    (void) {
   return (Pec12.Inc);
}

//       Pec12IsMinus      true indique un nouveau décrément
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

//       Pec12NoActivity   true indique abscence d'activité sur PEC12
bool Pec12NoActivity    (void) {
   return (Pec12.NoActivity);
}

//  Fonctions pour quittance des indications
//       Pec12ClearPlus    annule indication d'incrément
void Pec12ClearPlus   (void) {
   Pec12.Inc = 0;
}

//       Pec12ClearMinus   annule indication de décrément
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
