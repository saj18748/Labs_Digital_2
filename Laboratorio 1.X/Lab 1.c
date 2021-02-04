/*
 * File:   Laboratorio_1.c
 * Author: Yefry Elias Sajquiy Vargas
 *
 * Fecha: 28/01/2021
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
//          Declaracion de variables y funciones                              //
//----------------------------------------------------------------------------//

void setup(void);  
//funciones que se definen en la ultima parte del codigo
void semaforo(void);
void cont_uno(void);
void cont_dos(void);
int  flag = 0; 


//----------------------------------------------------------------------------//
//                              Codigo principal                              //
//----------------------------------------------------------------------------//

void main(void){
    
    setup();
    
    while(1)
    {  
        if ((PORTBbits.RB0 == 1) && (!flag))        // se veifica el RB0 encender el semaforo
        {   semaforo();}                                  
        
        if ((PORTBbits.RB1 == 1) && (flag))         // se verifica el RB1 para acticar el contador 1 del jugador 1
        {  cont_uno();                               
           __delay_ms(100); }                       // se utliza un delay de 100 ms para que sirva como anti-rebote
        
        if ((PORTBbits.RB2 == 1) && (flag))          // se verifica el RB1 para acticar el contador 2 el jugador 2
        {  cont_dos();
           __delay_ms(100); }   
    } 
}

//------------------------------------------------------------------------------
//  CONFIGURACION DE LOS PUERTOS  
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

void semaforo(void)         // Configuracion del contador del semaforo
{
    PORTE = 1;                  // PORTE igual a 1 para empezar el conteo 
    __delay_ms(100);
   
    // se hace un corrimieto de bits hacia la izquierda para prdenr cada led del semaforo
    // se utliza un delay de 100 ms para que sirva como anti-rebote
    for(int i=0; i<=2; i++)     
    {   PORTE = PORTE <<1;      
        __delay_ms(200);    }
    
    // se ponen los puetos en 0 para que se comience el contador desde 0
    flag = 1;                   
    PORTD = 0;
    PORTB = 0;
    PORTC = 0; 
}

void cont_uno(void){               // Configuracion del contador del jugador 1
    
    if (PORTC == 0)                // se verifica que pueto C este en cero      
    {   PORTC = PORTC++; }         // Se empieza con la suma
    else
    {
        PORTC = PORTC << 1;         // se hace el desplazamiento de bits cada vez que se pulsa
        if (PORTCbits.RC7 == 1)     // cuando el puerto RC7 = 1 se pasa a a encender el puerto RB3, para el ganador
        {   PORTBbits.RB3 = 1;
            PORTC = 255;            // Si el jugador uno llega primero se encenderan todos los leds del puerto C
            flag = 0;
        }
        else 
        {   PORTBbits.RB3 = 0; }    // si no ha llegado RC7 = 1 no se enciende
                 
    }
}

void cont_dos(void){                // Configuracion del contador del jugador 1
    if (PORTD == 0)                 // se verifica que pueto D este en cero
    {   PORTD = PORTD++; }          // Se empieza con la suma
    
    else
    {
        PORTD = PORTD << 1;         // se hace el desplazamiento de bits cada vez que se pulsa
        if (PORTDbits.RD7 == 1)     // cuando el puerto RD7 = 1 se pasa a a encender el puerto RB4, para el ganador
        {   PORTBbits.RB4 = 1;
            PORTD   = 255;          // Cuado el jugador 2 lelga primero se encenderan todos los del del puerto D
            flag = 0;
        }
        else
        {   PORTBbits.RB4 = 0;  }   // si no ha llegado RD7 = 1 no se enciende
    }
}

//-----------------------------------------------------------------------------
//              FIN   XD
//-----------------------------------------------------------------------------