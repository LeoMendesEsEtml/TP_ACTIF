/*--------------------------------------------------------*/
// Mc32GestI2cEEprom.h - Gestion I2C de l'EEPROM du MCP79411
// Description : Fonctions de lecture/�criture sur la m�moire EEPROM int�gr�e
//               au composant MCP79411 via le bus I2C.
// Auteur : C. Huber
// Version : V1.6 (12.04.2016)
// Compilateur : XC32 V1.40 & Harmony 1_06
/*--------------------------------------------------------*/

#ifndef MC32GEST_I2C_EEPROM_H
#define	MC32GEST_I2C_EEPROM_H

#include <stdint.h> // Inclusion des types standard (uint8_t, uint16_t, etc.)

// Adresse I2C pour la lecture depuis l'EEPROM du MCP79411 (7 bits + bit R/W � 1)
#define MCP79411_EEPROM_R    0xAF // Adresse I2C utilis�e pour une lecture

// Adresse I2C pour l'�criture dans l'EEPROM du MCP79411 (7 bits + bit R/W � 0)
#define MCP79411_EEPROM_W    0xAE // Adresse I2C utilis�e pour une �criture

// Adresse de d�but de l'EEPROM interne (0x00)
#define MCP79411_EEPROM_BEG  0x00 // Premi�re adresse m�moire disponible

// Adresse de fin de l'EEPROM interne (0x7F pour 128 octets = 1 Kbits)
#define MCP79411_EEPROM_END  0x7F // Derni�re adresse valide pour lecture/�criture

// Fonction d'initialisation de l'I2C pour la communication avec le MCP79411
void I2C_InitMCP79411(void);

// Fonction de lecture de donn�es depuis l'EEPROM du MCP79411
// Param�tres :
//   - DstData : pointeur vers le tampon de destination des donn�es lues
//   - EEpromAddr : adresse de d�part dans l'EEPROM (entre 0x00 et 0x7F)
//   - NbBytes : nombre total d'octets � lire
void I2C_ReadSEEPROM(void *DstData, uint32_t EEpromAddr, uint16_t NbBytes);

// Fonction d'�criture de donn�es dans l'EEPROM du MCP79411
// Param�tres :
//   - SrcData : pointeur vers les donn�es � �crire
//   - EEpromAddr : adresse de d�part dans l'EEPROM (entre 0x00 et 0x7F)
//   - NbBytes : nombre total d'octets � �crire
void I2C_WriteSEEPROM(void *SrcData, uint32_t EEpromAddr, uint16_t NbBytes);

#endif	/* MC32GEST_I2C_EEPROM_H */
