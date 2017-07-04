#ifndef __ADC_H__
#define __ADC_H__
#endif

#include<stdint.h>
#include"tm4c123gh6pm.h"
#include"Pins.h"

void ADC_Init();

unsigned long ADC_Read(unsigned int AINx);

int32_t Joystick_Map(int32_t value, int32_t known_min,  int32_t known_max, int32_t min, int32_t max);
