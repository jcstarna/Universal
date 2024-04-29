#include <12F675.h>
#DEVICE ADC=10
#fuses INTRC_IO,NOWDT,NOPROTECT,NOMCLR
#use delay(clock=4000000)



#use fast_io(A)
//#BYTE    WPU   =   0x95

//    PINES   //////////

#define  pRele        PIN_A5      //Digital-Salida

#define  vBat        0
#define  refSup      1
#define  refInf      2

int  const  kInmuni  =  300;
int  const  k1seg    =  500;
int  const  kPausa   =  2;



int16  r1Seg= k1Seg;


int1  f1Seg  = 0;
int1  p1Seg = 0;
int1  fFallaSup=0;
int1  fFallaInf=0;


int16  rInmuni=kInmuni;
int16  rInmuniSup=kInmuni;
int16  rInmuniInf=kInmuni;


int16 rVBat=0;
int16 rRefSup=0;
int16 rRefInf=0;

int   rinmunidad=kInmuni;

// INTERRUPCIONES ////////////////////////////////////////////////////////////

#int_RTCC
void RTCC_isr() {                      // Interrupción Timer 0
      if(--r1Seg==0){
         f1Seg=1;
         r1Seg= k1Seg;
      }
}


void main() {
//Configuracion puertos
Setup_comparator(NC_NC_NC_NC);   //Comparador OFF
port_a_pullups(FALSE);

SET_TRIS_a(0b11001111);            //Direccion de los pines e o s

//Configuracion Analogicas
setup_adc(ADC_CLOCK_DIV_8);
SETUP_ADC_PORTS(sAN0|sAN1|sAN2|VSS_VDD);
//Configuracion Oscilador
SETUP_TIMER_0(RTCC_INTERNAL|RTCC_DIV_128);
//WPU = 0;

//estado inicial
output_high(pRele);

SET_ADC_CHANNEL(refInf);     //canal de bateria
delay_us(100);
rRefInf = read_adc();


//Interrupciones
ENABLE_INTERRUPTS(INT_RTCC);     //Interrupcion por timer0
ENABLE_INTERRUPTS(GLOBAL);

   while (TRUE) {
      if(f1Seg){
         p1Seg=1;
         f1Seg=0;
        }
      else
         p1Seg=0;
         
      if (p1Seg){
        
      SET_ADC_CHANNEL(2);     //referencia inferior
      delay_us(100);
      rRefInf = read_adc();
      
      //SET_ADC_CHANNEL(1);    //referencia superior
      //delay_us(100);
      rRefSup = rRefInf + (rRefInf * 2)/100; 
      
      SET_ADC_CHANNEL(0);    //canal de bateria
      delay_us(100);
      rvBat = read_adc();

       if (rVBat <= rRefInf){ //comparacion por baja
          if(--rInmuniInf==0){
            output_low(pRele);
            rInmuniInf=kInmuni;
          }   
       }
       else
           rInmuniInf=kInmuni;
           
       if (rVBat > rRefSup){ //comparacion por alta
          if(--rInmuniSup==0){
            output_high(pRele);
            rInmuniSup=kInmuni;
          }   
       }
       else
           rInmuniSup=kInmuni;          
           
      }//fin if 1 segundo
   }//Fin While infinito   
}//Fin Main
