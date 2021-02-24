/*
 * File:   contador 8 bits.c
 * Author: Yefry Sajquiy
 *
 * Created on 16 de febrero de 2021, 10:53 PM
 */

//------------------------------------------------------------------------------
// CONFIG1
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
#define SCK_SLAVE TRISC3
#define SDO_SLAVE TRISC5
#define SS_SLAVE TRISA5

#include <xc.h>

//----------------------------------------------------------------------------//
//          Declaracion de variables                                          
//----------------------------------------------------------------------------//

void setup(void); 
void inc_cont_BI(void);     // incrementa contador binario
void dec_cont_BI(void);     // decremetna contador binario

//----------------------------------------------------------------------------//
//                              Codigo principal                              
//----------------------------------------------------------------------------//

void main(void) {
    
    setup();        // se llama ala configuracion de los pines
    
    while (1) {
        if(PORTAbits.RA1 == 1)      // cuando RA = 1 se incrementa el contador
        { inc_cont_BI();}

        if (PORTAbits.RA2 == 1)     // cuando RA = 1 se decrementa el contador
        {  dec_cont_BI();}
    }
    return; 
 }

//------------------------------------------------------------------------------
//  CONFIGURACION DE LOS PUERTOS  
//------------------------------------------------------------------------------

void setup(void) {
    // Establecemos los puertos como digitales  
    ANSEL = 0;
    ANSELH = 0;

    // PUERTO A - push buttons
    TRISA = 0b00000011;
    PORTA = 0;

    // PUETO B - Salida el contador en los leds
    TRISB = 0;
    PORTB = 0;

    // para la comunicacion UART
    TRISC = 0;
    PORTC = 0;

    TRISD = 0;
    PORTD = 0;

    TRISE = 0;
    PORTE = 0;
}
//------------------------------------------------------------------------------
//  CONFIGURACION DE LAS FUNCIONES
//------------------------------------------------------------------------------

void inc_cont_BI(void){
    __delay_ms(50);
    PORTD = PORTD++;        // se suma una unidad al contador
}

void dec_cont_BI(void){
    __delay_ms(100);
    PORTD = PORTD--;       // se le resta una unidad al contador
} 

//-----------------------------------------------------------------------------
//              FIN   XD
//-----------------------------------------------------------------------------