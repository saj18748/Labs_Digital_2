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
#include "driverlib/uart.h"
#include "driverlib/pin_map.h"

//*****************************************************************************
//
// The error routine that is called if the driver library encounters an error.
//
//*****************************************************************************
#ifdef DEBUG
void
__error__(char *pcFilename, uint32_t ui32Line) {
    while(1);
}
#endif

//Variables Globales
uint32_t LED = GPIO_PIN_1;
unsigned char temporal = 'a';
unsigned char temporal2 = 'f';
char time = 0;
char FLAG = 0;

//Prototipado
extern void Timer0IntHandler(void);
extern void UARTIntHandler(void);

int main(void) {
    // Utiliza el oscilador principal, con el cristal de 16MHz y el PLL y divido dentro de 5 para llegar a 40
    SysCtlClockSet(SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ | SYSCTL_USE_PLL | SYSCTL_SYSDIV_5);

    // Activa el puerto F
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF));

    //Activa interrupciones generales
    IntMasterEnable();

    // Activa Timer0
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_TIMER0));
    TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);
    TimerLoadSet(TIMER0_BASE, TIMER_A, SysCtlClockGet()/2 - 1);
    TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
    TimerIntRegister(TIMER0_BASE, TIMER_A, Timer0IntHandler);
    IntEnable(INT_TIMER0A);
    TimerEnable(TIMER0_BASE, TIMER_A);

    // Activa UART
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOA));
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_UART0));
    GPIOPinConfigure(0x00000001); // RX
    GPIOPinConfigure(0x00000401); // TX --> ver pin_map.h
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
    UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), 115200, UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE);
    UARTFIFOEnable(UART0_BASE);
    IntEnable(INT_UART0);
    UARTIntEnable(UART0_BASE, UART_INT_RX | UART_INT_RT);
    UARTIntClear(UART0_BASE, UART_INT_RX | UART_INT_RT);
    UARTIntRegister(UART0_BASE,UARTIntHandler);
    UARTEnable(UART0_BASE);

    // Coloca como salida los pines 1, 2 y 3 del puerto F (los pines de los LEDs)
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3);
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, 0);

    while(1);
}

void Timer0IntHandler(void) {
    // Clear the timer interrupt
    TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
    switch(time){
    case 0:
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, LED);
        time++;
        break;
    case 1:
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, 0);
        time = 0;
        break;
    }
}

void UARTIntHandler(void) {
    // Clear the timer interrupt
    UARTIntClear(UART0_BASE, UART_INT_RX | UART_INT_RT);
    if (UARTCharsAvail(UART0_BASE)){
        temporal = UARTCharGet(UART0_BASE);
    }
    if(temporal2 != temporal) {
        IntEnable(INT_TIMER0A);
        if(temporal == 'r') {
            LED = GPIO_PIN_1;
            temporal2 = temporal;
            temporal = 'a';
        }
        else if(temporal == 'b') {
            LED = GPIO_PIN_2;
            temporal2 = temporal;
            temporal = 'a';
        }
        else if(temporal == 'g') {
            LED = GPIO_PIN_3;
            temporal2 = temporal;
            temporal = 'a';
        }
        else{
        }
    }
    else{
        switch(FLAG){
            case 0:
                IntDisable(INT_TIMER0A);
                FLAG++;
                break;
            case 1:
                IntEnable(INT_TIMER0A);
                FLAG = 0;
                break;
        }
    }
}
