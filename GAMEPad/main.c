
#include<stdint.h>
#include"Pins.h"

// Global Variables
uint32_t DIRECTIONAL=0,ACTION_P=0,ACTION_S=0,pressed=0;

void PortB(void);
void PortC(void);
void PortD(void);
void setup(void);
void loop (void);
uint32_t read_buttons(void);

int main(void) {

	setup();

    loop();
}


void PortB(){
    GPIO_PORTB_DIR_R|= ACL|ACR|START;
    GPIO_PORTB_DATA_R = 0;
    GPIO_PORTB_PUR_R|= !ACL|!ACR|!START;
    GPIO_PORTB_DEN_R|= !ACL|!ACR|!START;
}

void PortC(){
    GPIO_PORTC_DIR_R|= UP|RIGHT|LEFT|DOWN;
    GPIO_PORTC_DATA_R = 0;
    GPIO_PORTC_PUR_R|= !UP|!RIGHT|!LEFT|!DOWN;
    GPIO_PORTC_DEN_R|= !UP|!RIGHT|!LEFT|!DOWN;
}
void PortD(){
    GPIO_PORTD_DIR_R|= A|B|X|Y;
    GPIO_PORTD_DATA_R = 0;
    GPIO_PORTD_PUR_R|= !A|!B|!X|!Y;
    GPIO_PORTD_DEN_R|= !A|!B|!X|!Y;
}

void setup(){
    SYSCTL_RCGCGPIO_R|=SYSCTL_RCGC2_GPIOB|SYSCTL_RCGC2_GPIOC|SYSCTL_RCGC2_GPIOD;
    while(SYSCTL_RCGCGPIO_R&(SYSCTL_RCGC2_GPIOB|SYSCTL_RCGC2_GPIOC|SYSCTL_RCGC2_GPIOD) == 0);
    PortC();
    PortB();
    PortD();
}


void loop(){

    do{

        pressed = read_buttons();

    }while(1);
}


uint32_t read_buttons(){

    DIRECTIONAL = GPIO_PORTC_DATA_R&(0b011110000);
    ACTION_P = GPIO_PORTD_DATA_R&(0b1111);
    ACTION_S    = GPIO_PORTB_DATA_R&(0b01110);
    ACTION_S<<=7;
    return (DIRECTIONAL|ACTION_P|ACTION_S);
}
