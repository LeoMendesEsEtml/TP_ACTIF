/*--------------------------------------------------------*/
// Mc32GestI2cEEprom.h - Gestion I2C de l'EEPROM du MCP79411
// Description : Fonctions de lecture/écriture sur la mémoire EEPROM intégrée
//               au composant MCP79411 via le bus I2C.
// Auteur : C. Huber
// Version : V1.6 (12.04.2016)
// Compilateur : XC32 V1.40 & Harmony 1_06
/*--------------------------------------------------------*/

#ifndef MC32GEST_I2C_EEPROM_H
#define	MC32GEST_I2C_EEPROM_H

#include <stdint.h> // Inclusion des types standard (uint8_t, uint16_t, etc.)

// Adresse I2C pour la lecture depuis l'EEPROM du MCP79411 (7 bits + bit R/W à 1)
#define MCP79411_EEPROM_R    0xAF // Adresse I2C utilisée pour une lecture

// Adresse I2C pour l'écriture dans l'EEPROM du MCP79411 (7 bits + bit R/W à 0)
#define MCP79411_EEPROM_W    0xAE // Adresse I2C utilisée pour une écriture

// Adresse de début de l'EEPROM interne (0x00)
#define MCP79411_EEPROM_BEG  0x00 // Première adresse mémoire disponible

// Adresse de fin de l'EEPROM interne (0x7F pour 128 octets = 1 Kbits)
#define MCP79411_EEPROM_END  0x7F // Dernière adresse valide pour lecture/écriture

// Fonction d'initialisation de l'I2C pour la communication avec le MCP79411
void I2C_InitMCP79411(void);

// Fonction de lecture de données depuis l'EEPROM du MCP79411
// Paramètres :
//   - DstData : pointeur vers le tampon de destination des données lues
//   - EEpromAddr : adresse de départ dans l'EEPROM (entre 0x00 et 0x7F)
//   - NbBytes : nombre total d'octets à lire
void I2C_ReadSEEPROM(void *DstData, uint32_t EEpromAddr, uint16_t NbBytes);

// Fonction d'écriture de données dans l'EEPROM du MCP79411
// Paramètres :
//   - SrcData : pointeur vers les données à écrire
//   - EEpromAddr : adresse de départ dans l'EEPROM (entre 0x00 et 0x7F)
//   - NbBytes : nombre total d'octets à écrire
void I2C_WriteSEEPROM(void *SrcData, uint32_t EEpromAddr, uint16_t NbBytes);

#endif	/* MC32GEST_I2C_EEPROM_H */
