/*
 * File:   sensor1.c
 * Author: Yefry Sajquiy
 
 */

//------------------------------------------------------------------------------
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

#define _XTAL_FREQ  8000000
// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include<stdint.h>
#include <xc.h>

#define SCK_SLAVE TRISC3
#define SDO_SLAVE TRISC5
#define SS_SLAVE TRISA5



void setup();           // configuracion de los puertos 
void ADC_Init(void);    // configuracion del ADC

unsigned int ADC_Read(unsigned char channel)  // configuracion de la lectura dle ADC
{
  if(channel > 7)              //el rango del canal es de 0 a 7
    return 0;

  ADCON0 &= 0xC5;              // se limpia el canal
  ADCON0 |= channel<<3;        // se selecciona el canal 
  __delay_ms(2);               
  GO_nDONE = 1;                // se inicia la convercion
  while(GO_nDONE);             // se espera a que se haga la convercion
  return (ADRESH<<8);          // se regresa para completar el conteo de 8 bits
}

//----------------------------------------------------------------------------//
//                              Codigo principal                              
//----------------------------------------------------------------------------//

void main()
{
  unsigned int VT=0;  // valor de temperatura
  unsigned int ADCV;
  
  // se llaman a las  funcines definidas
  
  setup();
  ADC_Init();                   

   while(1){               // se realiza la lectura del ADC
    VT = ADC_Read(0);            
      
   
    PORTB = VT>>8;           // se muestra en le puerto B       
    __delay_ms(3);        
    
    ADCV = (VT*5)/1024;
    
    if ( ADCV<= 16)
    {PORTD = 0b00000001;}
    
    else if ( ADCV >= 17 && ADCV <=22 )
    {PORTD = 0b00000011;}
    
    else if ( ADCV >= 23)
    {PORTD = 0b00000111;}
   } 
  return;
}

//------------------------------------------------------------------------------
//  CONFIGURACION DE LAS FUNCIONES
//------------------------------------------------------------------------------

void ADC_Init(void)
{
  ADCON0 = 0x81;             //Se configura el A,como entrada analogoa  
  ADCON1 = 0x00;              //Pines como entrada analogica y configura el voltaje de regerencia 
}

void setup(void){
    
  TRISA = 0xFF;         //entrada analogica
  
  TRISB = 0x00;          // salida del valor adc  
  
  TRISC = 0;             // uso para la comunicacion SPI   
  PORTC = 0;
  
  TRISD = 0;
  PORTD = 0;
}

//-----------------------------------------------------------------------------
//              FIN   XD
//----------------------------------------------------------------------------------------------------