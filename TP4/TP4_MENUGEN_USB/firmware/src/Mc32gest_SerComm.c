// Mc32Gest_SerComm.C
// fonction d'�mission et de r�ception des message
// transmis en USB CDC
// Canevas TP4 SLO2 2015-2015


#include "app.h"
#include "Mc32gest_SerComm.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


// Fonction de reception  d'un  message
// Met � jour les param�tres du generateur a partir du message recu
// Format du message
//  !S=TF=2000A=10000O=+5000D=100W=0#
//  !S=PF=2000A=10000O=-5000D=100W=1#


bool GetMessage(int8_t *USBReadBuffer, S_ParamGen *pParam, bool *SaveTodo)
{
    // Pointeurs vers les segments dans la trame
    char *pt_Forme      = NULL;
    char *pt_Frequence  = NULL;
    char *pt_Amplitude  = NULL;
    char *pt_Offset     = NULL;
    char *pt_Sauvegarde = NULL;

    // 1) V�rifier d�but et fin de la trame
    //    - Commence par '!'
    //    - Se termine quelque part par '#'
    if (USBReadBuffer[0] != '!')
    {
        return false; // pas le bon format
    }
    // Cherche un '#'
    if (strchr((char*)USBReadBuffer, '#') == NULL)
    {
        return false; // pas de fin
    }

    // 2) Recherche des tokens
    //    Exemple attendu: !S=TF=2000A=10000O=+5000W=1#
    //    On va chercher "S", "F", "A", "O", "W"
    pt_Forme      = strstr((char*)USBReadBuffer, "S=");
    pt_Frequence  = strstr((char*)USBReadBuffer, "F=");
    pt_Amplitude  = strstr((char*)USBReadBuffer, "A=");
    pt_Offset     = strstr((char*)USBReadBuffer, "O=");
    pt_Sauvegarde = strstr((char*)USBReadBuffer, "WP=");


    // Contr�le que tout a �t� trouv�
    if (!pt_Forme || !pt_Frequence || !pt_Amplitude || !pt_Offset || !pt_Sauvegarde)
    {
        return false; // param�tre(s) manquant(s)
    }

    // 3) D�codage de la forme. On suppose "S=" est suivi d'un caract�re T/S/C/D
    //    par ex. "!S=TF=2000..." => le 'T' est pt_Forme[2]
    switch (pt_Forme[2])
    {
        case 'T': 
            pParam->Forme = SignalTriangle;    
            break;
        case 'S': 
            pParam->Forme = SignalSinus;       
            break;
        case 'C': 
            pParam->Forme = SignalCarre;       
            break;
        case 'D': 
            pParam->Forme = SignalDentDeScie;  
            break;
        default:
            return false; // Forme inconnue
    }

    // 4) Mise � jour des param�tres num�riques (ex: F=2000 => atoi(pt_Frequence+2))
    pParam->Frequence = atoi(pt_Frequence  + 2);  
    pParam->Amplitude = atoi(pt_Amplitude  + 2);  
    pParam->Offset    = atoi(pt_Offset     + 2);  

    // 5) R�cup�ration de W= (Sauvegarde demand�e ?)
    int wVal = atoi(pt_Sauvegarde + 2);
    if (wVal == 1)
        *SaveTodo = true;
    else
        *SaveTodo = false;

    // 6) Tout est correct
    return true;  
} // GetMessage


// Fonction d'envoi d'un  message
// Rempli le tampon d'�mission pour USB en fonction des param�tres du g�n�rateur
// Format du message
// !S=TF=2000A=10000O=+5000D=25WP=0#
// !S=TF=2000A=10000O=+5000D=25WP=1#    // ack sauvegarde



void SendMessage(int8_t *USBSendBuffer, S_ParamGen *pParam, bool Saved )
{
    // Convertit la forme interne en lettre
    char formeChar = 'S';
    switch (pParam->Forme) {
        case SignalTriangle:
            formeChar = 'T';
            break;

        case SignalSinus:
            formeChar = 'S';
            break;

        case SignalCarre:
            formeChar = 'C';
            break;

        case SignalDentDeScie:
            formeChar = 'D';
            break;

        default:
            formeChar = 'X'; // Inconnu
            break;
    }


    // WP=1 si la sauvegarde a �t� faite, 0 sinon
    int saveFlag;
    if (Saved == true) {
        saveFlag = 1;
    } else {
        saveFlag = 0;
    }
    
    // Construction de la trame final
    // Format exemple: "!S=TF=2000A=10000O=-1500WP=1#"
    // On g�re l'offset sign� : %d convient
    sprintf((char*)USBSendBuffer,
            "!S=%cF=%dA=%dO=%dWP=%d#",
            formeChar,
            pParam->Frequence,
            pParam->Amplitude,
            pParam->Offset,
            saveFlag);   
} // SendMessage
