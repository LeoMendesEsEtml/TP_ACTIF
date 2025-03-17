// Canevas manipulation GenSig avec menu
// C. HUBER  09/02/2015
// Fichier Generateur.C
// Gestion  du g�n�rateur

// Pr�vu pour signal de 40 echantillons

// Migration sur PIC32 30.04.2014 C. Huber


#include "Generateur.h"
#include "DefMenuGen.h"
#include "Mc32gestSpiDac.h"
#include "Mc32NVMUtil.h"
#include "system_config.h"
#include "Mc32DriverLcd.h"

// T.P. 2016 100 echantillons
#define MAX_ECH 100 //nombre d'�chantillons par p�riode

S_ParamGen valParaGen;
int32_t tb_tabValSig[MAX_ECH]; // tableau qui contient la valeur de chaque �chantillons d'une p�riode
int32_t tb_tabValSig2[MAX_ECH];


// Initialisation du g�n�rateur
void  GENSIG_Initialize(S_ParamGen *pParam)
{
}
  

// Mise � jour de la p�riode d'�chantillonnage
void GENSIG_UpdatePeriode(S_ParamGen *pParam)
{
    uint16_t Periode = 0;          // Variable pour stocker la nouvelle p�riode d'�chantillonnage
    uint32_t nbr_ech;              // Nombre total d'�chantillons � prendre par p�riode
    uint32_t frequ_presc;          // Fr�quence du timer apr�s application du pr�scaler
    
    // Calcule du nombre d'�chantillons en fonction de la fr�quence sp�cifi�e dans pParam
    nbr_ech = MAX_ECH * pParam->Frequence;
    
    // Calcule de la fr�quence effective du timer en divisant la fr�quence du syst�me par le pr�scaler
    frequ_presc = FREQU_SYS / PRESC_TIM3;
    
    // Calcule de la nouvelle p�riode d'�chantillonnage
    Periode = frequ_presc / nbr_ech;
    
    // Mise � jour la p�riode du timer 3 avec la nouvelle valeur calcul�e
    PLIB_TMR_Period16BitSet(TMR_ID_3, Periode);
}


// Mise � jour du signal (forme, amplitude, offset)
void  GENSIG_UpdateSignal(S_ParamGen *pParam)
{
    uint8_t echantillons;
    uint16_t amplitude;
    int16_t offset;
    uint8_t compt_sig;
    //�chantillon sinus
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
    float tbSignalDentDeScie[MAX_ECH];
 
    amplitude = pParam->Amplitude;
    offset = pParam->Offset; 
    
    for (echantillons = 0; echantillons < MAX_ECH; echantillons++){
       
        switch(pParam->Forme){
            
            case SignalSinus:
                tb_tabValSig[echantillons] = ((tbSignalSinus[echantillons] * amplitude) + offset);
                break;
              
            case SignalTriangle:
                
                for (compt_sig = 0;compt_sig < MAX_ECH/2; compt_sig++){
                    
                    tb_tabValSig[compt_sig] = ((2 * amplitude * compt_sig)+5000/ MAX_ECH)-offset;            
                }
                for(compt_sig = MAX_ECH/2;compt_sig < MAX_ECH; compt_sig++){
                    
                    tb_tabValSig[compt_sig] = ((2 * amplitude *(MAX_ECH - compt_sig))+5000/ MAX_ECH)-offset;
                }
                
                break;
                
            case SignalDentDeScie:
                for (compt_sig = 0;compt_sig < MAX_ECH; compt_sig++){
                    
                    if(tb_tabValSig[compt_sig] == amplitude){
                        tb_tabValSig[compt_sig] = -amplitude + offset;
                    }
                    if(tb_tabValSig[compt_sig] == 0){
                        tb_tabValSig[compt_sig] = -amplitude + offset;
                    }
                    else{
                        tb_tabValSig[compt_sig] = (tb_tabValSig[compt_sig -1] + ((amplitude*2)/MAX_ECH))+ offset;
                    }  
                }
                

                
//                if(tb_tabValSig[echantillons] == AMPLITUDE_MAX){
//                    tb_tabValSig[echantillons] = -10000;
//                }
//                else{
//                    tb_tabValSig[echantillons] = tb_tabValSig[echantillons] + 200;
//                }

                break;
                
            case SignalCarre:
                for (compt_sig = 0; compt_sig < MAX_ECH; compt_sig++){
                    
                    if(compt_sig < MAX_ECH / 2){
                        tb_tabValSig[compt_sig] = offset + amplitude;         
                    }
                    else{
                        tb_tabValSig[compt_sig] = offset - amplitude;     
                    }  
                }                
                
                break;
                
            default:
                break;
        }
        
        
    }
    // caclule de mV � LSB pour le DAC
    for (echantillons = 0; echantillons < MAX_ECH; echantillons++){
        
        tb_tabValSig2[echantillons] =  (((tb_tabValSig[echantillons] -  AMPLITUDE_MIN)* PAS_MAXIMUM) / 20000);
        
    }
}


// Execution du g�n�rateur
// Fonction appel�e dans Int timer3 (cycle variable variable)

// Version provisoire pour test du DAC � modifier
void  GENSIG_Execute(void)
{
   static uint16_t EchNb = 0;
   const uint16_t Step = 65535 / MAX_ECH;

   SPI_WriteToDac(0, tb_tabValSig2[EchNb]);      // sur canal 0
   EchNb++;
   EchNb = EchNb % MAX_ECH;
}
