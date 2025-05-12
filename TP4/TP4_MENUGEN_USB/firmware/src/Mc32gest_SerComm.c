// Mc32Gest_SerComm.C
// fonction d'�mission et de r�ception des message
// transmis en USB CDC
// Canevas TP4 SLO2 2015-2015


#include "app.h"
#include "Mc32gest_SerComm.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


// Fonction de r�ception d'un message
// Permet de mettre � jour les param�tres du g�n�rateur � partir d'une trame re�ue
// Format attendu de la trame :
// Exemple : !S=TF=2000A=10000O=+5000W=0#
// Exemple : !S=PF=2000A=10000O=-5000W=1#

bool GetMessage(int8_t *USBReadBuffer, S_ParamGen *pParam, bool *SaveTodo)
{
    // D�claration des pointeurs vers les diff�rentes sections de la trame
    char *pt_Forme = NULL;       // Pointeur vers le champ S= (forme du signal)
    char *pt_Frequence = NULL;   // Pointeur vers le champ F= (fr�quence)
    char *pt_Amplitude = NULL;   // Pointeur vers le champ A= (amplitude)
    char *pt_Offset = NULL;      // Pointeur vers le champ O= (offset)
    char *pt_Sauvegarde = NULL;  // Pointeur vers le champ W= (demande de sauvegarde)

    // �tape 1 : V�rifie le d�but et la fin de la trame
    // Une trame valide commence par '!' et contient un '#' de terminaison
    if (USBReadBuffer[0] != '!')
    {
        return false; // La trame ne commence pas par le caract�re '!'
    }

    if (strchr((char*)USBReadBuffer, '#') == NULL)
    {
        return false; // Le caract�re '#' de fin de trame est manquant
    }

    // �tape 2 : Recherche des champs sp�cifiques dans la trame
    // Utilisation de strstr pour localiser chaque param�tre attendu
    pt_Forme      = strstr((char*)USBReadBuffer, "S="); // Forme du signal (S=)
    pt_Frequence  = strstr((char*)USBReadBuffer, "F="); // Fr�quence (F=)
    pt_Amplitude  = strstr((char*)USBReadBuffer, "A="); // Amplitude (A=)
    pt_Offset     = strstr((char*)USBReadBuffer, "O="); // Offset (O=)
    pt_Sauvegarde = strstr((char*)USBReadBuffer, "W="); // Sauvegarde (W=)

    // V�rifie que tous les champs ont bien �t� trouv�s
    if (!pt_Forme || !pt_Frequence || !pt_Amplitude || !pt_Offset || !pt_Sauvegarde)
    {
        return false; // Un ou plusieurs champs obligatoires sont absents
    }

    // �tape 3 : D�codage de la forme du signal
    // Le caract�re juste apr�s 'S=' d�termine le type de forme
    // Exemples : T = Triangle, S = Sinus, C = Carr�, D = Dent de scie
    switch (pt_Forme[2])
    {
        case 'T':
            pParam->Forme = SignalTriangle;    // Signal de forme triangulaire
            break;
        case 'S':
            pParam->Forme = SignalSinus;       // Signal de forme sinuso�dale
            break;
        case 'C':
            pParam->Forme = SignalCarre;       // Signal de forme carr�e
            break;
        case 'D':
            pParam->Forme = SignalDentDeScie;  // Signal de forme dent de scie
            break;
        default:
            return false; // Caract�re de forme inconnu, trame invalide
    }

    // �tape 4 : Extraction et conversion des valeurs num�riques
    // On extrait les entiers avec atoi en sautant les 2 premiers caract�res (ex: F=)
    pParam->Frequence = atoi(pt_Frequence + 2);   // Fr�quence en [Hz]
    pParam->Amplitude = atoi(pt_Amplitude + 2);   // Amplitude en [mV]
    pParam->Offset    = atoi(pt_Offset + 2);      // Offset en [mV]

    // �tape 5 : Analyse du champ W= pour savoir si une sauvegarde est demand�e
    int wVal = atoi(pt_Sauvegarde + 2); // R�cup�re la valeur 0 ou 1 apr�s W=
    if (wVal == 1)
    {
        *SaveTodo = true;  // Indique qu'une sauvegarde doit �tre effectu�e
    }
    else
    {
        *SaveTodo = false; // Aucune demande de sauvegarde
    }

    // �tape 6 : Tous les champs sont valides et correctement trait�s
    return true; // Trame d�cod�e avec succ�s
}

// Fonction d'envoi d'un message structur� via USB
// Cette fonction pr�pare une trame � transmettre vers le PC en fonction des
// param�tres du g�n�rateur et de l'�tat de sauvegarde.
// Format attendu de la trame envoy�e :
// Exemple : !S=TF=2000A=10000O=+5000W=0#  (sans demande de sauvegarde)
// Exemple : !S=TF=2000A=10000O=+5000W=1#  (acknowledgement de sauvegarde)

void SendMessage(int8_t *USBSendBuffer, S_ParamGen *pParam, bool Saved)
{
    // Variable locale pour stocker le caract�re repr�sentant la forme du signal
    char formeChar = 'S'; // Valeur par d�faut (sinus)

    // Conversion de l'enum interne en caract�re unique � ins�rer dans la trame
    switch (pParam->Forme) {
        case SignalTriangle:
            formeChar = 'T'; // T pour Triangle
            break;

        case SignalSinus:
            formeChar = 'S'; // S pour Sinus
            break;

        case SignalCarre:
            formeChar = 'C'; // C pour Carr�
            break;

        case SignalDentDeScie:
            formeChar = 'D'; // D pour Dent de scie
            break;

        default:
            formeChar = 'X'; // X utilis� en cas de forme inconnue
            break;
    }

    // D�termine la valeur � ins�rer dans le champ W=
    // W=1 si la sauvegarde a �t� demand�e et trait�e, sinon W=0
    int saveFlag;
    if (Saved == true) {
        saveFlag = 1; // Indique que la sauvegarde a �t� faite
    } else {
        saveFlag = 0; // Indique qu'aucune sauvegarde n'est effectu�e
    }

    // Construction finale de la trame � envoyer en format texte ASCII
    // Le r�sultat est stock� dans le tampon USBSendBuffer
    // Utilisation de sprintf pour concat�ner tous les champs dans le format suivant :
    // !S=<Forme>F=<Frequence>A=<Amplitude>O=<Offset>W=<Sauvegarde>#
    sprintf((char*)USBSendBuffer,
            "!S=%cF=%dA=%dO=%dW=%d#",
            formeChar,               // Caract�re repr�sentant la forme du signal
            pParam->Frequence,       // Fr�quence actuelle du g�n�rateur [Hz]
            pParam->Amplitude,       // Amplitude cr�te [mV]
            pParam->Offset,          // Offset (peut �tre n�gatif) [mV]
            saveFlag);               // 1 si sauvegarde, 0 sinon
}

