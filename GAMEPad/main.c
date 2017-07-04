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

void SysTick_Handler(void){

    char action[] = "S: ;A: ;B: ;X: ;Y: ;AL: ;AR: ;";
    char directional[] = "U: ;D: ;R: ;L: ;";
    char dualshock[] = "AX:    ;AY:    ;\n";

    action[2] = (char)48|PAUSE;
    action[6] = (char)48|ACT_A;
    action[10]= (char)48|ACT_B;
    action[14]= (char)48|ACT_X;
    action[18]= (char)48|ACT_Y;
    action[23]= (char)48|ACT_L;
    action[28]= (char)48|ACT_R;

    directional[2] = (char)48|D_UP;
    directional[6] = (char)48|D_DOWN;
    directional[10] =(char)48|D_RIGHT;
    directional[14] =(char)48|D_LEFT;

    uint8_t milhar,centena,dezena,unidade;
    uint16_t x_value = Joystick_Map(ADC_Read(X_AIN), 0, 4095, 0, 100);
    uint16_t y_value = Joystick_Map(ADC_Read(Y_AIN), 0, 4095, 0, 100);

    // X axis value conversion
    milhar =(uint8_t)(x_value/1000);
    centena=(uint8_t)(x_value-(milhar*1000))/100;
    dezena =(uint8_t)(x_value-(milhar*1000)-(centena*100))/10;
    unidade=(uint8_t)(x_value-(milhar*1000)-(centena*100)-(dezena*10));

    dualshock[3] = (char)48|milhar;
    dualshock[4] = (char)48|centena;
    dualshock[5] = (char)48|dezena;
    dualshock[6] = (char)48|unidade;

    // Y axis value conversion
    milhar =(uint8_t)(y_value/1000);
    centena=(uint8_t)(y_value-(milhar*1000))/100;
    dezena =(uint8_t)(y_value-(milhar*1000)-(centena*100))/10;
    unidade=(uint8_t)(y_value-(milhar*1000)-(centena*100)-(dezena*10));

    dualshock[11] = (char)48|milhar;
    dualshock[12] = (char)48|centena;
    dualshock[13] = (char)48|dezena;
    dualshock[14] = (char)48|unidade;

    print(&USB, action);
    print(&USB, directional);
    print(&USB, dualshock);

    print(&BT, action);
    print(&BT, directional);
    print(&BT, dualshock);
}

void Start_Handler(){
    GPIO_PORTB_ICR_R = !START;
    SysTick_Handler();
}

int main(void) {
    setup();

    //USB = USB_begin(19200);
    USB = USB_begin(9600);
    BT  = Bluetooth_begin(9600);

    do{
        __asm("WFI");
    }while(1);
}
