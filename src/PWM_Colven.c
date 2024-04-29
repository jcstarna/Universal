#include <12F683.h>
#DEVICE ADC=8
#fuses INTRC_IO,NOWDT,NOPROTECT,NOMCLR
#use delay(clock=8000000)



#use fast_io(A)
//#BYTE    WPU   =   0x95

//    PINES   //////////
#define  pCicPWM        PIN_A5  //ciclo pwm 2ms y luego otro pwm  
#define  pIniPWM        PIN_A4  //solo pwm inicial    


int  const  kInmuni  =  5;
int  const  kTPwmIni  = 50;
int  const  kPausa   =  2;

unsigned int8   duty=0;

int1  fDir  = 0;
int1  fInv    =0;
int1  fAuxIn   =0;
int1  fTimerOn=0;
int1  fPwmIni=0;
int1  fRele=0;    //imagen del estado del rele
int1  fGatillo=0;
int1  fTecPres=0;
int8  rInmuni=kInmuni;
int8  rTPwmIni=kTPwmIni;

// INTERRUPCIONES ////////////////////////////////////////////////////////////

#int_RTCC
void RTCC_isr() {                      // Interrupción Timer 0
//control de tiempo de pwm
   if (fPwmIni){
      if(--rTPwmIni==0){
         rTPwmIni=kTPwmIni;
         fPwmIni=0;
      }
   }
}


void main() {
//Configuracion puertos
Setup_comparator(NC_NC_NC_NC);   //Comparador OFF
port_a_pullups(FALSE);
SETUP_ADC_PORTS(sAN1||sAN0);
SET_TRIS_a(0b00110011);            //Direccion de los pines e o s
//Configuracion Oscilador
SETUP_TIMER_0(RTCC_INTERNAL|RTCC_DIV_32);

//PWM
//The cycle time will be (1/clock)*4*t2div*(period+1)
setup_timer_2(T2_DIV_BY_1, 180, 1);    //(1/8000000)*1*1*128= 0.000064s -> 15khz
setup_ccp1(CCP_PWM);                   // Configure CCP1 as a PWM

  setup_adc(adc_clock_internal);
  set_adc_channel( 0 );


//Interrupciones
ENABLE_INTERRUPTS(INT_RTCC);     //Interrupcion por timer0/
ENABLE_INTERRUPTS(GLOBAL);
fPwmIni=1;
duty=read_adc();

   while (TRUE) {
   if(input(pCicPWM)){// logica de 200ms a un pwm y luego a otro
      if(fPwmIni){
         set_adc_channel( 0 );
         delay_us(100);
         duty=read_adc();
         set_pwm1_duty(duty);
      }
      else{
         set_adc_channel( 1 );
         delay_us(100);
         duty=read_adc();
         set_pwm1_duty(duty);
      }
   }
   else if (input(pIniPWM)){            //logica todo en pwm inicial solamente
      set_adc_channel( 0 );
      delay_us(100);
      duty=read_adc();
      set_pwm1_duty(duty);
   }
   else
      set_pwm1_duty(255);
   }//Fin While infinito   
}//Fin Main


