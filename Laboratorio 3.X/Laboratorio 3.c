/*
 * File:   Laboratorio 3.c
 * Author: Yefry Sajquiy
 *
 * Created on 5 de febrero de 2021, 08:40 AM
 */

//------------------------------------------------------------------------------
// CONFIG_1
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

#define RS  RD2
#define EN  RD3
#define D4  RD4
#define D5  RD5
#define D6  RD6
#define D7  RD7

#include <xc.h>
#include    "LCD.h"

//
//----------------------------------------------------------------------------//
//          Declaracion de variables y funciones                              //
//----------------------------------------------------------------------------//

void setup(void);
void ADC_Init(void);
char s[20];


unsigned int ADC_Read(unsigned char channel)
{
  if(channel > 7)              //Channel range is 0 ~ 7
    return 0;

  ADCON0 &= 0xC5;              //Clearing channel selection bits
  ADCON0 |= channel<<3;        //Setting channel selection bits
  __delay_ms(2);               //Acquisition time to charge hold capacitor
  GO_nDONE = 1;                //Initializes A/D conversion
  while(GO_nDONE);             //Waiting for conversion to complete
  return (ADRESH<<8); //Return result
}
//-----------------------------------------------------------------------------
// Progra principal 
//-----------------------------------------------------------------------------

void main()
{
  unsigned int a;
  unsigned int volt;
  unsigned int voltaje;
  setup ();
  ADC_Init();                   //Initialize ADC
  Lcd_Init();

  while(1){
      
    a = ADC_Read(0);            //Read Analog Channel 0
                   //Write Lower bits to PORTB
    PORTB = a>>8;               //Write Higher 2 bits to PORTC
    __delay_ms(50); 
   
    Lcd_Clear();
    Lcd_Set_Cursor(1,1);
    Lcd_Write_String("Laboratorio #3");
    Lcd_Set_Cursor(2,1);
    Lcd_Write_String("Yefry Sajquiy");
    __delay_ms(100);
    Lcd_Clear();
    Lcd_Set_Cursor(1,1);
    Lcd_Write_String("18748");
    Lcd_Set_Cursor(2,1);
    Lcd_Write_String("Digital 2");
    __delay_ms(100);
    
    volt = ADC_Read(0);
    voltaje = (volt*0.5)/1023;
    
    Lcd_Clear();
    Lcd_Set_Cursor(1,1);
    Lcd_Write_String("Voltaje");
    __delay_ms(100);
    Lcd_Clear();
    Lcd_Set_Cursor(2,1);
    Lcd_Write_String("Voltaje",voltaje);
    
    for(a=0;a<15;a++)
    {
        __delay_ms(300);
        Lcd_Shift_Left();
    }

    for(a=0;a<15;a++)
    {
        __delay_ms(300);
        Lcd_Shift_Right();
    }

    Lcd_Clear();
    Lcd_Set_Cursor(2,1);
    Lcd_Write_Char('e');
    Lcd_Write_Char('S');
    __delay_ms(200);
  }
  return;
  
}

//-----------------------------------------------------------------------------
//   Declaracion de los bloques de progra
//-----------------------------------------------------------------------------

void setup(void){
  TRISA = 0xFF;                 //Analog pins as Input
  TRISB = 0x00;                 //Port B as Output
  
  TRISC = 0;        
  PORTC = 0;      
    
// Puerto del jugador 2
   TRISD= 0x00;   
    
}

void ADC_Init(void)
{
  ADCON0 = 0x81;               //Turn ON ADC and Clock Selection
  ADCON1 = 0x00;               //All pins as Analog Input and setting Reference Voltages
}