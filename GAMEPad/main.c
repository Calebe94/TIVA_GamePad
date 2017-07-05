#include<stdint.h>
#include<stdio.h>
#include<stdlib.h>
#include"Pins.h"
#include"tm4c123gh6pm.h"
#include"ADC.h"
#include"system.h"
#include"UART.h"

SERIAL USB,BT;

void setup(){
    SYSCTL_RCGCGPIO_R|=SYSCTL_RCGC2_GPIOB|SYSCTL_RCGC2_GPIOC|SYSCTL_RCGC2_GPIOD;
    while(SYSCTL_RCGCGPIO_R&(SYSCTL_RCGC2_GPIOB|SYSCTL_RCGC2_GPIOC|SYSCTL_RCGC2_GPIOD) == 0);
    PortB();
    PortC();
    PortD();
    ADC_Init();
    SysTick_Init(200000);
    PortB_Interrupt();
}

void SysTick_Handler(){
    char keys[8];

    uint8_t x_value = Joystick_Map(ADC_Read(X_AIN), 0, 4095, 0, 100);
    uint8_t y_value = Joystick_Map(ADC_Read(Y_AIN), 0, 4095, 0, 100);

    keys[0] = (char)(0b01000000)|(PAUSE<<4)|(ACT_A<<3)|(ACT_B<<2)|(ACT_X<<1)|(ACT_Y<<0);
    keys[1] = (char)(0b01000000)|(D_UP<<5|D_DOWN<<4|D_LEFT<<3|D_RIGHT<<2|ACT_R<<1|ACT_L<<0);

    keys[2] = (char)(0b01000000)|(x_value&0b1111);
    keys[3] = (char)(0b01000000)|((x_value&0b11110000)>>4);

    keys[4] = (char)(0b01000000)|(y_value&0b1111);
    keys[5] = (char)(0b01000000)|((y_value&0b11110000)>>4);

    keys[6] = (char)'\n';
    keys[7] = (char)'\0';

    print(&BT,keys);
    print(&USB,keys);
}

void Start_Handler(){
    GPIO_PORTB_ICR_R = !START;
    SysTick_Handler();
}

int main(void) {
    setup();

    USB = USB_begin(9600);
    BT  = Bluetooth_begin(9600);

    do{
        __asm("WFI");
    }while(1);
}
