#include <12F675.h>
#DEVICE ADC=8
#fuses INTRC_IO,NOWDT,NOPROTECT,NOMCLR
#use delay(clock=4000000)



#use fast_io(A)
//#BYTE    WPU   =   0x95

//    PINES   //////////

#define  pPulsador    PIN_A0      //Gatillo accionamiento
#define  pLed1seg     PIN_A1     //
#define  pReleCamp    PIN_A4      //Digital-Salida
#define  pReleLamp    PIN_A5      //Digital-Salida


int  const  kInmuni  =  50;
int16  const  k1seg    =  490;//500
int const   k1Min =  60;
int const   k5Min =  5;
int const   k30Min   = 30;
int const   kCampana = 10;

int16  r1Seg= k1Seg;
int8  r1Min =  k1Min;
int8  r5Min =  k5Min;
int8  r30Min   =  k30Min;
int8  rCampana=kCampana;

int1  f1Seg  = 0;
int1  f1Min   =0;
int1  f5Min =  0;
int1  f30Min   =0;
int1  fRele=0;    //imagen del estado del rele
int1  fPulsador=0;
int8  rInmuni=kInmuni;


// INTERRUPCIONES ////////////////////////////////////////////////////////////

#int_RTCC
void RTCC_isr() {                      // Interrupción Timer 0
   if (input(pPulsador)){
      if(--rInmuni==0){
         rInmuni=kInmuni;
         fPulsador=1;
      }
   }
   else
      rInmuni=kInmuni;
      
   if (--r1Seg==0){
   output_toggle(PlED1sEG);
      r1Seg= k1Seg;
      f1Seg=1;
      if(--r1Min==0){
         r1Min=k1Min;
         f1Min=1;
         if(--r5Min==0){
            r5Min=k5Min;
            f5Min=1;
         }
         if(--r30Min==0){
            r30Min=k30Min;
            f30Min=1;
         }
      }
   }
}


void main() {
//Configuracion puertos
Setup_comparator(NC_NC_NC_NC);   //Comparador OFF
port_a_pullups(FALSE);
SETUP_ADC_PORTS(NO_ANALOGS );
SET_TRIS_a(0b11001101);            //Direccion de los pines e o s
//Configuracion Oscilador
SETUP_TIMER_0(RTCC_INTERNAL|RTCC_DIV_8);
//WPU = 0;

//estado inicial
output_low(pReleCamp);
output_low(pReleLamp);
fRele=0;
rInmuni=kInmuni;
rCampana=kCampana;
//Interrupciones
ENABLE_INTERRUPTS(INT_RTCC);     //Interrupcion por timer0
ENABLE_INTERRUPTS(GLOBAL);

   while (TRUE) {
         if(f30Min){
             f30Min=0;
             output_high(pReleCamp);
             output_high(pReleLamp);
             f5Min=0;
             fRele=1;
         }
         if(f1Seg){
            f1Seg=0;
            if (f5Min){
               f5Min=0;
               if(fRele){
                  output_low(pReleLamp);
                  fRele=0;
               }
            }
             if(fRele){
               if(--rCampana==0){
                  rCampana=kCampana;
                  output_low(pReleCamp);
               }
             }
         }//fin f1Seg
        if(fPulsador){//si presiono pulsador
            fPulsador=0;
            r1Seg= k1Seg;
            r1Min =  k1Min;
            r5Min =  k5Min;
            r30Min   =  k30Min;
            rCampana=kCampana;  
            output_low(pReleCamp);
            output_low(pReleLamp);
         }
         }//Fin While infinito   
}//Fin Main

