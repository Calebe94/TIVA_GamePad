#ifndef __UART_H__
    #define __UART_H__
#endif

#include<stdlib.h>
#include<stdint.h>
#include"tm4c123gh6pm.h"

typedef struct{
    volatile uint32_t *FR;
    volatile uint32_t *DR;
}SERIAL;

SERIAL USB,BT;

SERIAL begin(char port, uint32_t RX,uint32_t TX);

char read(SERIAL *serial);

void write(SERIAL *serial, char character);

void print(SERIAL *serial, char *string);

SERIAL USB_begin(uint32_t baudrate);

SERIAL Bluetooth_begin(uint32_t baudrate);
