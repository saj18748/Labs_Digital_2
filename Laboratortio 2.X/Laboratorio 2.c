/*
 * File:   Laboratorio 2.c
 * Author: Yefry Sajquiy
 *
 * Created on 29 de enero de 2021, 08:33 AM
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


#include <xc.h>

//----------------------------------------------------------------------------//
//          Declaracion de variables                                          
//----------------------------------------------------------------------------//

void setup(void); 
void inc_cont_BI(void);     // incrementa contador binario
void dec_cont_BI(void);
//----------------------------------------------------------------------------//
//                              Codigo principal                              
//----------------------------------------------------------------------------//

void main(void) {
    setup();
    while (1) {
        if(PORTAbits.RA1 == 1)
        { inc_cont_BI();}
        
        if (PORTAbits.RA2 == 1)
        {  dec_cont_BI();}
    }
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

    // PUERTO C - salida para los transistores
    TRISC = 0;
    PORTC = 0;

    // PUERTO D - salida para los display
    TRISD = 0;
    PORTD = 0;

    // Puerto E como salida para el semaforo
    TRISE = 0;
    PORTE = 0;
}
//------------------------------------------------------------------------------
//  CONFIGURACION DE LAS FUNCIONES
//------------------------------------------------------------------------------

void inc_cont_BI(void){
    __delay_ms(100);
    PORTB = PORTB++;
}

void dec_cont_BI(void){
    __delay_ms(100);
    PORTB = PORTB--;
}