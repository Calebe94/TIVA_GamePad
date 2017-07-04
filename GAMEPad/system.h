/*
 Arquivo irá conter as funções utilizadas pelo Sistema.
 Funções como: delay, SysTickInit, ADCInit, ADCRead, entre outras
 */
#ifndef __SYSTEM_H__
#define __SYSTEM_H__
#endif

#include<stdint.h>
#include"tm4c123gh6pm.h"
#include"Pins.h"

void PortB_Interrupt(void);

void PortB(void);

void PortC(void);

void PortD(void);

uint32_t read_buttons(void);

unsigned int ticks_microsseconds(unsigned int microsseconds);

void SysTick_Init(unsigned int reaload);

void delay(unsigned int delay);

// Esta função será chamada a cada 50ms através da Interrupção do SisTick
extern void SendData();

// Esta função será chamada cada vez que o botão Start for pressionado.
extern void StartPressed();
