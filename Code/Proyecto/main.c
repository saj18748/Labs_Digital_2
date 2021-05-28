//Yefry Elias Sajquiy Vargas - 18748
// Proyecto Final

// Se incluyen las librerias

#include <stdint.h>
#include <stdbool.h>
#include "inc/tm4c123gh6pm.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_ints.h"
#include "driverlib/sysctl.h"
#include "driverlib/interrupt.h"
#include "driverlib/gpio.h"
#include "driverlib/timer.h"
#include "driverlib/systick.h"
#include "driverlib/uart.h"
#include "driverlib/pin_map.h"

//----------- Funciones-----------------------------------

void UART1config(void);
void display(uint8_t valor);


// Declaracion de variables ------------------------------

uint8_t Parqueo1;
uint8_t Parqueo2;
uint8_t Parqueo3;
uint8_t Parqueo4;
uint8_t Disp = 0;
uint8_t suma = 0;

//--------------- PROGRAMA PRINCIPAL -------------------------------------
void main(void)

//----------------- CONFIGURACION DE SETUP -----------------------------------

{   //Configuracion de reloj a 40MHz
    SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
    //Se activan los puertos E, C y A

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);

    //COnfiguracion de salida de los LEDs
    GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE, GPIO_PIN_4|GPIO_PIN_5);
    GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7);
    GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6);

    //Configuracion de entrada de los push
    GPIOPinTypeGPIOInput(GPIO_PORTC_BASE, GPIO_PIN_6|GPIO_PIN_7);
    GPIOPinTypeGPIOInput(GPIO_PORTE_BASE, GPIO_PIN_2|GPIO_PIN_3);
    //IntMasterEnable();
    UART1config();

//------------------ LOOP ---------------------------------------------------------
    while(1){
        //Lectura de los push
        Parqueo1 = GPIOPinRead(GPIO_PORTE_BASE, GPIO_PIN_2);
        Parqueo2 = GPIOPinRead(GPIO_PORTE_BASE, GPIO_PIN_3);
        Parqueo3 = GPIOPinRead(GPIO_PORTC_BASE, GPIO_PIN_6);
        Parqueo4 = GPIOPinRead(GPIO_PORTC_BASE, GPIO_PIN_7);

        //Se leen los datos de cada parqueo
        //si esta en cero la luz verde se enciende y en 1 se encienden los azules
        // PARQUEO 1
        if (Parqueo1 == 0){ //Parqueo 1 esta ocupado
            GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_4|GPIO_PIN_5, 16); //Se enciende led azul
            Disp &= ~(1); //Clear del bit 0
        }
        //Parqueo 1 esta disponible
        else{
            GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_4|GPIO_PIN_5, 32); //Se enciende led verde
            Disp |= 1;   //Set del bit 0
        }

        // PARQUEO 2
        //Parqueo 2 esta ocupado
        if (Parqueo2 == 0){
            GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_2|GPIO_PIN_3, 4); //Se enciende led azul
            Disp &= ~(2); //Clear del bit 1
        }
        //Parqueo 2 esta disponible
        else{
            GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_2|GPIO_PIN_3, 8); //Se enciende led verde
            Disp |= 2;   //Set del bit 1
        }

        // PARQUEO 3
        //Parqueo 3 esta ocupado
        if (Parqueo3 == 0){
            GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_4|GPIO_PIN_5, 16); //Se enciende led azul
            Disp &= ~(4); //Clear del bit 2
        }
        //Parqueo 3 esta disponible
        else{
            GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_4|GPIO_PIN_5, 32); //Se enciende led verde
            Disp |= 4;   //Set del bit 2
        }

        //  PARQUEO 4
        //Parqueo 4 esta ocupado
        if (Parqueo4 == 0){
            GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_6|GPIO_PIN_7, 64); //Se enciende led azul
            Disp &= ~(8); //Clear del bit 3
        }
        //Parqueo 4 esta disponible
        else{
            GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_6|GPIO_PIN_7, 128); //Se enciende led verde
            Disp |= 8;   //Set del bit 3
        }

        //suma de cada boton que se pulsa, no importa cual se presione primero, contara desde uno
        if (1 & Disp){
                    suma+=1;
                }
        if (2 & Disp){
                    suma+=1;
                }
        if (4 & Disp){
                    suma+=1;
                }
        if (8 & Disp){
                    suma+=1;
                }

        display(suma); //Se despliega en el display la cantidad total de parqueos disponibles
        UARTCharPut(UART1_BASE, Disp); //Se envía el valor de Disp al ESP32
        suma = 0;  //Se resetea el valor de suma para la proxima lectura de la disponibilidad

    }

}

//**********************************FUNCIONES*********************************************



void UART1config(void){

    //Aqui se configura el UART1

    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART1);//Se Activa clock para UART1
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);//Se activa clock para puerto C de la tiva
    GPIOPinConfigure(GPIO_PC4_U1RX);
    GPIOPinConfigure(GPIO_PC5_U1TX);
    GPIOPinTypeUART(GPIO_PORTC_BASE, GPIO_PIN_4|GPIO_PIN_5); //Se activan los pines 6 y 7 del puerto D
    UARTConfigSetExpClk(UART1_BASE,SysCtlClockGet(), 115200, UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE);
    UARTEnable(UART1_BASE);
   // UARTIntEnable(UART2_BASE, UART_INT_RT | UART_INT_RX); //Se activa interrupcion cada vez que se reciba un dato
   // UARTIntRegister(UART2_BASE, UARTIntHandler); //Se le coloca el nombre a la funcion del handler
}


void display(uint8_t valor){
    //Dependiendo del valor del parametro se encienden ciertos leds del display para mostrar visualmente el numero correspondiente
    switch(valor){
        case 0:
            GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6, 95); //Se encienden los pines para mostrar el 0
            break;
        case 1:
                    GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6, 80); //Se encienden los pines para mostrar el 1
                    break;
        case 2:
                    GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6, 62); //Se encienden los pines para mostrar el 2
                    break;
        case 3:
                    GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6, 122); //Se encienden los pines para mostrar el 3
                    break;
        case 4:
                    GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6, 113); //Se encienden los pines para mostrar el 4
                    break;
    }

}
