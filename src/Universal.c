#include <12F683.h>
#DEVICE ADC=8
#fuses INTRC_IO,NOWDT,NOPROTECT,NOMCLR
#use delay(clock=4000000)



#use fast_io(A)
//#BYTE    WPU   =   0x95

//    PINES   //////////

#define  pGatillo     PIN_A1      //Gatillo accionamiento
#define  pModoPulso   PIN_A2      //1 activa rele, 0, desactiva rele
#define  pModoCont    PIN_A3      //1 pulso activa, 1 pulso desactiva
#define  pRele        PIN_A4      //Digital-Salida
#define  pRele1        PIN_A5      //Digital-Salida


int  const  kInmuni  =  50;
int  const  k1seg    =  500;
int  const  kPausa   =  2;



int16  r1Seg= k1Seg;


int1  fDir  = 0;
int1  fInv    =0;
int1  fAuxIn   =0;
int1  fTimerOn=0;
int1  fPausa=0;
int1  fRele=0;    //imagen del estado del rele
int1  fGatillo=0;
int1 fTecPres=0;
int8  rInmuni=kInmuni;


// INTERRUPCIONES ////////////////////////////////////////////////////////////

#int_RTCC
void RTCC_isr() {                      // Interrupción Timer 0
//teclado
   if(input(pGatillo)){
       if(!fTecPres){
         if(--rInmuni==0){
            fGatillo=1;
            fTecPres=1;
         }
       }
   }
   else
   { 
      fGatillo=0;
      rInmuni=kInmuni;
      fTecPres=0;
   }

   if (--r1Seg==0){
      r1Seg= k1Seg;
      
   }
}


void main() {
//Configuracion puertos
Setup_comparator(NC_NC_NC_NC);   //Comparador OFF
port_a_pullups(FALSE);
SETUP_ADC_PORTS(NO_ANALOGS );
SET_TRIS_a(0b11001111);            //Direccion de los pines e o s
//Configuracion Oscilador
SETUP_TIMER_0(RTCC_INTERNAL|RTCC_DIV_8);
//WPU = 0;

//estado inicial
output_low(pRele);
fRele=0;
rInmuni=kInmuni;

//Interrupciones
ENABLE_INTERRUPTS(INT_RTCC);     //Interrupcion por timer0
ENABLE_INTERRUPTS(GLOBAL);

   while (TRUE) {
      output_low(pRele1);
      /// modo continuo
      if (input(pModoCont)){
         //presiona gatillo
         if(fGatillo & !fRele){
            fRele=1;
            fGatillo=0;
         }
         if(fGatillo & fRele){
            fRele=0;  
            fGatillo=0;
         }
      }
      /// modo pulso
      if (input(pModoPulso)){
         if (fGatillo)
            fRele=1;
         else
            fRele=0;
      }
      
      if(!input(pModoPulso)& !input(pModoCont)){
         output_low(pRele);
         fRele=0;
      }
      else{
         if (fRele)
            output_high(pRele);
         else
            output_low(pRele);
      }
      //aca modo continuo
   }//Fin While infinito   
}//Fin Main
