#ifndef __GAMEPAD_H__
    #define __GAMEPAD_H__
#endif

#include"ADC.h"
#include"system.h"
#include"UART.h"

void printf_Dir(SERIAL *uart, unsigned int up, unsigned int down, unsigned int left, unsigned int right);

void printf_Act(SERIAL *uart, uint32_t a, uint32_t b, uint32_t x, uint32_t y, uint32_t al, uint32_t ar);

void printf_Analog(SERIAL *uart, int32_t x_value, int32_t y_value);
