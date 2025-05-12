//--------------------------------------------------------
// Mc32gestI2cEEprom.C
//--------------------------------------------------------
// Gestion I2C de la SEEPROM du MCP79411 (Solution exercice)
// Description : Fonctions pour EEPROM MCP79411
// Auteur : C. HUBER
// Date : 26.05.2014
// Version : V1.0
// Compilateur : XC32 V1.31
//--------------------------------------------------------

#include "Mc32gest_I2c_Eeprom.h"          // Inclusion de l'ent�te associ�e � ce fichier
#include "Mc32_I2cUtilCCS.h"             // Inclusion des fonctions de base pour l'I2C

// Fonction d'initialisation de la communication I2C avec le composant MCP79411
void I2C_InitMCP79411(void)
{
    bool Fast = true;                    // Vitesse rapide activ�e pour l'I2C
    i2c_init(Fast);                      // Initialisation du module I2C avec cette vitesse
}

// Fonction d'�criture dans l'EEPROM du MCP79411
void I2C_WriteSEEPROM(void *SrcData, uint32_t EEpromAddr, uint16_t NbBytes)
{
    uint8_t i = 0;                       // Indice pour la boucle sur les octets d'une page
    uint8_t y = 0;                       // Indice pour la boucle sur le nombre de pages
    uint8_t *i2cData = SrcData;          // Pointeur vers les donn�es sources � �crire
    uint8_t NbBytesPage = 0;            // Nombre d'octets � �crire pour la page en cours

    // Boucle principale sur chaque page de 8 octets
    for (y = 0; y <= (NbBytes / 8); y++)
    {
        // Si on est sur la derni�re page, calcul du nombre restant d'octets � �crire
        if (y == (NbBytes / 8))
        {
            NbBytesPage = NbBytes - 8 * y; // Derni�re page : reste des octets
        }
        else
        {
            NbBytesPage = 8;               // Pages pleines : 8 octets � �crire
        }

        // Attente d'un accus� de r�ception avant de commencer l'�criture
        do
        {
            i2c_start();                   // D�marre la communication I2C
        } while (!i2c_write(MCP79411_EEPROM_W)); // �met l'adresse d'�criture tant qu'il n'y a pas d'ACK

        // �mission de l'adresse m�moire dans l'EEPROM
        i2c_write((uint8_t)EEpromAddr + (y * 8));

        // Boucle sur les octets � �crire dans cette page
        for (i = 0; i < NbBytesPage; i++)
        {
            i2c_write(i2cData[i + (y * 8)]); // �criture des octets un par un
        }

        i2c_stop();                         // Fin de la transmission pour cette page
    }
}

// Fonction de lecture depuis l'EEPROM du MCP79411
void I2C_ReadSEEPROM(void *DstData, uint32_t EEpromAddr, uint16_t NbBytes)
{
    uint8_t i = 0;                         // Indice pour parcourir les octets � lire
    uint8_t *i2cData = DstData;            // Pointeur vers le tableau de destination

    // Phase d'initialisation de la lecture : positionnement de l'adresse m�moire
    do
    {
        i2c_start();                       // D�marre une communication I2C
    } while (!i2c_write(MCP79411_EEPROM_W)); // Envoie l'adresse d'�criture pour fixer l'adresse interne

    i2c_write((uint8_t)EEpromAddr);        // Adresse m�moire interne � lire

    i2c_reStart();                         // Red�marre la communication en mode lecture

    i2c_write(MCP79411_EEPROM_R);          // Envoie l'adresse de lecture (READ)

    // Lecture des octets demand�s, sauf le dernier
    for (i = 0; i < NbBytes - 1; i++)
    {
        i2cData[i] = i2c_read(1);          // Lecture avec acquittement (ACK)
    }

    i2cData[i] = i2c_read(0);              // Derni�re lecture sans ACK (NACK)

    i2c_stop();                            // Fin de la transmission I2C
}
