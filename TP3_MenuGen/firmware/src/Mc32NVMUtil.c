/*--------------------------------------------------------*/
// FlashUtil.c - Version compatible PIC32MX130F064B
// Remplace Mc32NVMUtil.c pour accès direct Flash
// Auteur : Refonte par ChatGPT
/*--------------------------------------------------------*/

#include "FlashUtil.h"
#include <xc.h>
#include <sys/kmem.h>

#define NVM_UNLOCK_SEQUENCE()  \
    NVMKEY = 0xAA996655;       \
    NVMKEY = 0x556699AA;

bool Flash_WriteRow(uint32_t baseAddress, const uint32_t* data)
{
    uint32_t i;
    uint32_t physAddr = KVA_TO_PA(baseAddress);

    while (NVMCON & 0x8000);  // Attente module prêt

    // Effacement de page
    NVMADDR = physAddr;
    NVMCON = 0x4003; // Page Erase
    NVM_UNLOCK_SEQUENCE();
    NVMCONSET = 0x8000;
    while (NVMCON & 0x8000);

    // Écriture d'une row complète (32 mots)
    NVMCON = 0x4001; // Word program
    for (i = 0; i < FLASH_ROW_WORDS; ++i)
    {
        NVMADDR = KVA_TO_PA(baseAddress + i * 4);
        NVMDATA = data[i];
        NVM_UNLOCK_SEQUENCE();
        NVMCONSET = 0x8000;
        while (NVMCON & 0x8000);
    }
    return true;
}

void Flash_Read(uint32_t baseAddress, uint32_t* outData, uint32_t wordCount)
{
    uint32_t i;
    volatile uint32_t* ptr = (volatile uint32_t*)baseAddress;
    for (i = 0; i < wordCount; i++) {
        outData[i] = ptr[i];
    }
}

void Flash_StoreSerial(uint32_t serial)
{
    uint32_t row[FLASH_ROW_WORDS];
    for (int i = 0; i < FLASH_ROW_WORDS; i++) {
        row[i] = 0xFFFFFFFF;
    }
    row[0] = serial;

    __builtin_disable_interrupts();
    Flash_WriteRow(FLASH_USER_PAGE_ADDR, row);
    __builtin_enable_interrupts();
}

uint32_t Flash_LoadSerial(void)
{
    uint32_t val;
    Flash_Read(FLASH_USER_PAGE_ADDR, &val, 1);
    if (val == 0xFFFFFFFF || val == 0x00000000)
        return 0;
    return val;
}
