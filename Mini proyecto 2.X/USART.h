#ifndef USART_H
#define	USART_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h>

void initUART(void);
uint8_t ASCII(uint8_t valor);

#endif	/* USART_H */