//------------------------------------------------------------------------------
/*
 * File:   Mini proyec.c
 * Author: Yefry Sajquiy
 *
 * Created on 12 de febrero de 2021, 08:47 AM
 */
//------------------------------------------------------------------------------

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
//          Declaracion de variables y funciones                              //
//----------------------------------------------------------------------------//

void setup (void);
void inc_cont (void);
void dec_cont (void);



//----------------------------------------------------------------------------//
//                              Codigo principal                              //
//----------------------------------------------------------------------------//
void main(void) {
    
    return;
}





//------------------------------------------------------------------------------
//  CONFIGURACION DE LOS PUERTOS Y BLOQUES DE VARIABLES
//------------------------------------------------------------------------------

void setup(void){
    // Establecemos los puertos como digitales  
    ANSEL = 0;     
    ANSELH = 0;
    
// Puerto E como salida para el semaforo
    TRISE = 0;    
    PORTE = 0;     
    
    TRISC = 0;        
    PORTC = 0;      
    
// Puerto del jugador 2
    TRISD= 0;       
    PORTD = 0;    
  
// Entradas de los push buttons
    TRISB = 0B00000111;     
    PORTB = 0;         
}

//-----------------------------------------------------------------------------

void inc_cont(void){
    
}

void dec_cont(void){
    
}


//-----------------------------------------------------------------------------
//              FIN   XD
//-----------------------------------------------------------------------------