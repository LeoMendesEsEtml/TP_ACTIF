/*--------------------------------------------------------*/
// Mc32NVMUtil.h
/*--------------------------------------------------------*/
//	Description :	Utilitaire gestion �criture dans memoire programme (NVM)
//	Auteur 		: 	C. HUBER
//      Cr�ation	: 	17.02.2015
//      Sur la base de l'exemple Harmony sous :
//      C:\microchip\harmony\v1_00\apps\examples\peripheral\nvm\flash_modify
//  Environnement d'origine :
//  	Version KIT     PCB 11020_B
//		Version		:	V1.61
//		Compilateur	:	XC32 V1.40 + Harmony 1.06
//
//  LISTE DES MODIFICATIONS :
//	24.03.16		CHR  correction dans NVMpageErase
//  08.03.17 v1.61	SCA  correction attente fin �criture dans NVMwriteRow
//                  compilateur xc32 1.42 avec Harmony 1.08   
//
/*--------------------------------------------------------*/

#ifndef FLASH_UTIL_H
#define FLASH_UTIL_H

#include <stdint.h>
#include <stdbool.h>

// Taille d'une page Flash (1 KB pour effacement)
#define FLASH_PAGE_SIZE_BYTES   1024

// Taille d'une row (�criture ligne) : 32 mots = 128 octets
#define FLASH_ROW_SIZE_BYTES    128
#define FLASH_ROW_WORDS         32

// Adresse Flash utilis�e pour stocker les donn�es utilisateur
// Assure-toi que cette page est libre dans ton .ld (ex: derni�re page)
#define FLASH_USER_PAGE_ADDR    0x1FC000

// �crit une row compl�te (32 mots) � baseAddress
bool Flash_WriteRow(uint32_t baseAddress, const uint32_t* data);

// Lit wordCount mots depuis baseAddress et les place dans outData
void Flash_Read(uint32_t baseAddress, uint32_t* outData, uint32_t wordCount);

// Sauvegarde un num�ro de s�rie 32 bits en Flash
void Flash_StoreSerial(uint32_t serial);

// Charge le num�ro de s�rie depuis la Flash
uint32_t Flash_LoadSerial(void);

#endif // FLASH_UTIL_H

