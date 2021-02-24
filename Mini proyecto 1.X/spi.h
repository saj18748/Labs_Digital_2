#include "spi.h"
 
////////////////////////////////////////////////////////////////////////////////
//// SPI INITIATE FUNCTION
////////////////////////////////////////////////////////////////////////////////
 
void spiInit(Spi_Type sType, Spi_Data_Sample sDataSample, Spi_Clock_Idle sClockIdle, Spi_Transmit_Edge sTransmitEdge)
{
 
 if(sType & 0x04) // Slave Mode Selected ( 00100xxx & 00000100 = 00000100 )
 {
 SSPSTAT = sTransmitEdge; // Wrinting SSPSTAT Register (x0000000)
 
 TRISCbits.TRISC3 = 1; // Setting Serial Clock as Input
 TRISCbits.TRISC4 = 1; // Master Output Slave Input (MOSI) - SDO as input
 TRISCbits.TRISC5 = 0; // Master Input Slave Output (MISO) - SDI as output
 TRISCbits.TRISC7 = 1; // Slave Select (SS) as input
 
 }
 else // Master Mode Selected ( 00000000 )
 {
 SSPSTAT = sDataSample | sTransmitEdge; // Wrinting SSPSTAT Register (x0000000 | 0x000000)
 
 TRISCbits.TRISC3 = 0; // Setting Serial Clock as Output 
 TRISCbits.TRISC4 = 1; // Master Input Slave Output (MISO) - SDI as input
 TRISCbits.TRISC5 = 0; // Master Output Slave Input (MOSI) - SDO as output 
 TRISCbits.TRISC7 = 0; // Slave Select (SS) as output
 
 }
 
 SSPCON = sType | sClockIdle; // Writing SSPCON Register (00100xxx | 000x0000)
}
 
////////////////////////////////////////////////////////////////////////////////
//// SPI DATA WRITE FUNCTION
////////////////////////////////////////////////////////////////////////////////
 
void spiWrite(char dat) // Write data to SPI bus
{
 SSPBUF = dat;
}
 
////////////////////////////////////////////////////////////////////////////////
//// SPI DATA READY FUNCTION
////////////////////////////////////////////////////////////////////////////////
 
unsigned spiDataReady() //Check whether the data is ready to read
{
 if(SSPSTATbits.BF)
 return 1;
 else
 return 0;
}
 
////////////////////////////////////////////////////////////////////////////////
//// SPI READ FUNCTION
////////////////////////////////////////////////////////////////////////////////
 
static void spiReceiveWait()
{
 while ( !SSPSTATbits.BF ); // Check if the recieve is complete (SSPBUS full)
}
 
char spiRead() //REad the received data
{
 spiReceiveWait(); // wait until the all bits receive
 return(SSPBUF); // read the received data from the buffer
}
 