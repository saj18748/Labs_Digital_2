//Universidad del valle de Guatemala
//Laboratorio # 6
//Yefry Sajquiy - 18748

//*****************************************************************************

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"

//*****************************************************************************


#ifdef DEBUG
void
__error__(char *pcFilename, uint32_t ui32Line)
{
    while(1);
}
#endif

//*****************************************************************************
// Semaforo
//*****************************************************************************
int main(void){

    SysCtlClockSet(SYSCTL_SYSDIV_64|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);

    volatile uint32_t ui32Loop;
    int i, FLAG;   // Para anti rebote


    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

    //
    // Check if the peripheral access is enabled.
    //
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF))
    {
    }

    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3);     //  Pines INPUT
    GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);  // PULL UP

    //
    // Loop forever.
    //
    while(1){   // Inicio de anti rebote

        if(GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_4) == 0){
            FLAG = 1;
        }
        else if (GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_4) == 16) {
            if(FLAG == 1){

                // inicio de secuencia de semaforo
                FLAG = 0;
                GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, GPIO_PIN_3);
                SysCtlDelay(2000000);

                for (i = 0; i<5; i++){  //
                    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, GPIO_PIN_3);
                    SysCtlDelay(200000);
                    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, 0);
                    SysCtlDelay(200000);
                }

                GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, GPIO_PIN_1 | GPIO_PIN_3);
                SysCtlDelay(2000000);

                GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, GPIO_PIN_1);
                SysCtlDelay(2000000);
            }
        }
    }
}
