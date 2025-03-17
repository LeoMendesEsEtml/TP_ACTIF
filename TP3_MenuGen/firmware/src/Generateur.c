// Canevas manipulation GenSig avec menu
// C. HUBER  09/02/2015
// Fichier Generateur.C
// Gestion  du générateur

// Prévu pour signal de 40 echantillons

// Migration sur PIC32 30.04.2014 C. Huber


#include "Generateur.h"
#include "DefMenuGen.h"
#include "Mc32gestSpiDac.h"
#include "Mc32NVMUtil.h"
#include "system_config.h"
#include "Mc32DriverLcd.h"

// T.P. 2016 100 echantillons
#define MAX_ECH 100  // Nombre d'échantillons par période
#define DAC_MIN 0          // Valeur minimale du DAC (LSB)
#define DAC_MAX 65535      // Valeur maximale du DAC (LSB)

#define CLAMP(value, min, max) ((value < min) ? min : (value > max) ? max : value)

S_ParamGen valParaGen;
int32_t tb_tabValSig[MAX_ECH];  // Tableau contenant les valeurs d'échantillons
int32_t tb_tabValSig2[MAX_ECH];

// Initialisation du générateur
void GENSIG_Initialize(S_ParamGen *pParam) {

}

// Mise à jour de la période d'échantillonnage
void GENSIG_UpdatePeriode(S_ParamGen *pParam) {
    uint16_t Periode;
    uint32_t nbr_ech;
    uint32_t frequ_presc;

    // Nombre total d'échantillons dans une période
    nbr_ech = MAX_ECH;

    // Calcul de la fréquence effective du timer
    frequ_presc = FREQU_SYS / PRESC_TIM3;

    // Calcul de la nouvelle période d'échantillonnage
    Periode = frequ_presc / (nbr_ech * pParam->Frequence);

    // Mise à jour du timer 3
    PLIB_TMR_Period16BitSet(TMR_ID_3, Periode);
}

// Mise à jour du signal (forme, amplitude, offset)
void GENSIG_UpdateSignal(S_ParamGen *pParam) {
    uint8_t echantillons;
    uint16_t amplitude = pParam->Amplitude;
    int16_t offset = pParam->Offset;
    uint8_t compt_sig;

    // Tableau précalculé du sinus (100 points)
    const float tbSignalSinus[MAX_ECH] = {
        0.0000,  0.0628,  0.1253,  0.1874,  0.2487,  0.3090,  0.3681,  0.4258,  0.4818,  0.5358,
        0.5878,  0.6374,  0.6845,  0.7290,  0.7705,  0.8090,  0.8443,  0.8763,  0.9048,  0.9298,
        0.9511,  0.9686,  0.9823,  0.9921,  0.9980,  1.0000,  0.9980,  0.9921,  0.9823,  0.9686,
        0.9511,  0.9298,  0.9048,  0.8763,  0.8443,  0.8090,  0.7705,  0.7290,  0.6845,  0.6374,
        0.5878,  0.5358,  0.4818,  0.4258,  0.3681,  0.3090,  0.2487,  0.1874,  0.1253,  0.0628,
        0.0000, -0.0628, -0.1253, -0.1874, -0.2487, -0.3090, -0.3681, -0.4258, -0.4818, -0.5358,
       -0.5878, -0.6374, -0.6845, -0.7290, -0.7705, -0.8090, -0.8443, -0.8763, -0.9048, -0.9298,
       -0.9511, -0.9686, -0.9823, -0.9921, -0.9980, -1.0000, -0.9980, -0.9921, -0.9823, -0.9686,
       -0.9511, -0.9298, -0.9048, -0.8763, -0.8443, -0.8090, -0.7705, -0.7290, -0.6845, -0.6374,
       -0.5878, -0.5358, -0.4818, -0.4258, -0.3681, -0.3090, -0.2487, -0.1874, -0.1253, -0.0628
    };

    switch (pParam->Forme) {
        case SignalSinus:
            for (echantillons = 0; echantillons < MAX_ECH; echantillons++) {
                tb_tabValSig[echantillons] = CLAMP((tbSignalSinus[echantillons] * amplitude) + offset, DAC_MIN, DAC_MAX);
            }
            break;

        case SignalTriangle:
            for (compt_sig = 0; compt_sig < MAX_ECH / 2; compt_sig++) {
                tb_tabValSig[compt_sig] = CLAMP(((2 * amplitude * compt_sig) / (MAX_ECH / 2)) - amplitude + offset, DAC_MIN, DAC_MAX);
            }
            for (compt_sig = MAX_ECH / 2; compt_sig < MAX_ECH; compt_sig++) {
                tb_tabValSig[compt_sig] = CLAMP(((-2 * amplitude * (compt_sig - (MAX_ECH / 2))) / (MAX_ECH / 2)) + amplitude + offset, DAC_MIN, DAC_MAX);
            }
            break;

        case SignalDentDeScie:
            for (compt_sig = 0; compt_sig < MAX_ECH; compt_sig++) {
                tb_tabValSig[compt_sig] = CLAMP(((amplitude * 2 * compt_sig) / MAX_ECH) - amplitude + offset, DAC_MIN, DAC_MAX);
            }
            break;

        case SignalCarre:
            for (compt_sig = 0; compt_sig < MAX_ECH; compt_sig++) {
                if (compt_sig < MAX_ECH / 2) {
                    tb_tabValSig[compt_sig] = CLAMP(offset + amplitude, DAC_MIN, DAC_MAX);
                } else {
                    tb_tabValSig[compt_sig] = CLAMP(offset - amplitude, DAC_MIN, DAC_MAX);
                }
            }
            break;

        default:
            break;
    }

    // Conversion mV en valeurs DAC
    for (echantillons = 0; echantillons < MAX_ECH; echantillons++) {
        tb_tabValSig2[echantillons] = (((tb_tabValSig[echantillons] - AMPLITUDE_MIN) * PAS_MAXIMUM) / 20000);
    }
}

// Exécution du générateur (appelée dans l'ISR Timer3)
void GENSIG_Execute(void) {
    static uint16_t EchNb = 0;

    SPI_WriteToDac(0, tb_tabValSig2[EchNb]);  // Envoi sur canal 0
    EchNb++;
    EchNb = EchNb % MAX_ECH;
}