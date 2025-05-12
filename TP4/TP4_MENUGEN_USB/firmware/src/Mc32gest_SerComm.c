// Mc32Gest_SerComm.C
// fonction d'émission et de réception des message
// transmis en USB CDC
// Canevas TP4 SLO2 2015-2015


#include "app.h"
#include "Mc32gest_SerComm.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


// Fonction de réception d'un message
// Permet de mettre à jour les paramètres du générateur à partir d'une trame reçue
// Format attendu de la trame :
// Exemple : !S=TF=2000A=10000O=+5000W=0#
// Exemple : !S=PF=2000A=10000O=-5000W=1#

bool GetMessage(int8_t *USBReadBuffer, S_ParamGen *pParam, bool *SaveTodo)
{
    // Déclaration des pointeurs vers les différentes sections de la trame
    char *pt_Forme = NULL;       // Pointeur vers le champ S= (forme du signal)
    char *pt_Frequence = NULL;   // Pointeur vers le champ F= (fréquence)
    char *pt_Amplitude = NULL;   // Pointeur vers le champ A= (amplitude)
    char *pt_Offset = NULL;      // Pointeur vers le champ O= (offset)
    char *pt_Sauvegarde = NULL;  // Pointeur vers le champ W= (demande de sauvegarde)

    // Étape 1 : Vérifie le début et la fin de la trame
    // Une trame valide commence par '!' et contient un '#' de terminaison
    if (USBReadBuffer[0] != '!')
    {
        return false; // La trame ne commence pas par le caractère '!'
    }

    if (strchr((char*)USBReadBuffer, '#') == NULL)
    {
        return false; // Le caractère '#' de fin de trame est manquant
    }

    // Étape 2 : Recherche des champs spécifiques dans la trame
    // Utilisation de strstr pour localiser chaque paramètre attendu
    pt_Forme      = strstr((char*)USBReadBuffer, "S="); // Forme du signal (S=)
    pt_Frequence  = strstr((char*)USBReadBuffer, "F="); // Fréquence (F=)
    pt_Amplitude  = strstr((char*)USBReadBuffer, "A="); // Amplitude (A=)
    pt_Offset     = strstr((char*)USBReadBuffer, "O="); // Offset (O=)
    pt_Sauvegarde = strstr((char*)USBReadBuffer, "W="); // Sauvegarde (W=)

    // Vérifie que tous les champs ont bien été trouvés
    if (!pt_Forme || !pt_Frequence || !pt_Amplitude || !pt_Offset || !pt_Sauvegarde)
    {
        return false; // Un ou plusieurs champs obligatoires sont absents
    }

    // Étape 3 : Décodage de la forme du signal
    // Le caractère juste après 'S=' détermine le type de forme
    // Exemples : T = Triangle, S = Sinus, C = Carré, D = Dent de scie
    switch (pt_Forme[2])
    {
        case 'T':
            pParam->Forme = SignalTriangle;    // Signal de forme triangulaire
            break;
        case 'S':
            pParam->Forme = SignalSinus;       // Signal de forme sinusoïdale
            break;
        case 'C':
            pParam->Forme = SignalCarre;       // Signal de forme carrée
            break;
        case 'D':
            pParam->Forme = SignalDentDeScie;  // Signal de forme dent de scie
            break;
        default:
            return false; // Caractère de forme inconnu, trame invalide
    }

    // Étape 4 : Extraction et conversion des valeurs numériques
    // On extrait les entiers avec atoi en sautant les 2 premiers caractères (ex: F=)
    pParam->Frequence = atoi(pt_Frequence + 2);   // Fréquence en [Hz]
    pParam->Amplitude = atoi(pt_Amplitude + 2);   // Amplitude en [mV]
    pParam->Offset    = atoi(pt_Offset + 2);      // Offset en [mV]

    // Étape 5 : Analyse du champ W= pour savoir si une sauvegarde est demandée
    int wVal = atoi(pt_Sauvegarde + 2); // Récupère la valeur 0 ou 1 après W=
    if (wVal == 1)
    {
        *SaveTodo = true;  // Indique qu'une sauvegarde doit être effectuée
    }
    else
    {
        *SaveTodo = false; // Aucune demande de sauvegarde
    }

    // Étape 6 : Tous les champs sont valides et correctement traités
    return true; // Trame décodée avec succès
}

// Fonction d'envoi d'un message structuré via USB
// Cette fonction prépare une trame à transmettre vers le PC en fonction des
// paramètres du générateur et de l'état de sauvegarde.
// Format attendu de la trame envoyée :
// Exemple : !S=TF=2000A=10000O=+5000W=0#  (sans demande de sauvegarde)
// Exemple : !S=TF=2000A=10000O=+5000W=1#  (acknowledgement de sauvegarde)

void SendMessage(int8_t *USBSendBuffer, S_ParamGen *pParam, bool Saved)
{
    // Variable locale pour stocker le caractère représentant la forme du signal
    char formeChar = 'S'; // Valeur par défaut (sinus)

    // Conversion de l'enum interne en caractère unique à insérer dans la trame
    switch (pParam->Forme) {
        case SignalTriangle:
            formeChar = 'T'; // T pour Triangle
            break;

        case SignalSinus:
            formeChar = 'S'; // S pour Sinus
            break;

        case SignalCarre:
            formeChar = 'C'; // C pour Carré
            break;

        case SignalDentDeScie:
            formeChar = 'D'; // D pour Dent de scie
            break;

        default:
            formeChar = 'X'; // X utilisé en cas de forme inconnue
            break;
    }

    // Détermine la valeur à insérer dans le champ W=
    // W=1 si la sauvegarde a été demandée et traitée, sinon W=0
    int saveFlag;
    if (Saved == true) {
        saveFlag = 1; // Indique que la sauvegarde a été faite
    } else {
        saveFlag = 0; // Indique qu'aucune sauvegarde n'est effectuée
    }

    // Construction finale de la trame à envoyer en format texte ASCII
    // Le résultat est stocké dans le tampon USBSendBuffer
    // Utilisation de sprintf pour concaténer tous les champs dans le format suivant :
    // !S=<Forme>F=<Frequence>A=<Amplitude>O=<Offset>W=<Sauvegarde>#
    sprintf((char*)USBSendBuffer,
            "!S=%cF=%dA=%dO=%dW=%d#",
            formeChar,               // Caractère représentant la forme du signal
            pParam->Frequence,       // Fréquence actuelle du générateur [Hz]
            pParam->Amplitude,       // Amplitude crête [mV]
            pParam->Offset,          // Offset (peut être négatif) [mV]
            saveFlag);               // 1 si sauvegarde, 0 sinon
}

