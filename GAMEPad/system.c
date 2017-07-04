#include"system.h"

void PortB_Interrupt(){
    NVIC_EN0_R = 1 << 1;
    GPIO_PORTB_IEV_R = START; // Ativa Interrupção para o Nível Baixo
    GPIO_PORTB_IM_R  =!START;
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

void delay(unsigned int delay){
    register unsigned int i;
    SYSCTL_RCGCTIMER_R |= 1;
    while(SYSCTL_RCGCTIMER_R&1==0);
    TIMER0_CTL_R = 0;
    TIMER0_CFG_R = 0x04;
    TIMER0_TAMR_R = 0x02;
    TIMER0_TAILR_R = 16000 - 1;
    TIMER0_ICR_R = 0x1;
    TIMER0_CTL_R |= 0x01;

    for(i = 0; i < delay; i++) {
        while ((TIMER0_RIS_R & 0x1) == 0) ;
        TIMER0_ICR_R = 0x1;
    }
}

unsigned int ticks_microsseconds(unsigned int microsseconds){
    return ((unsigned int)microsseconds/(1/4));
}

void SysTick_Init(unsigned int reload){
    NVIC_ST_CTRL_R = 0;
    NVIC_ST_RELOAD_R = reload; // Works with 200nS, because of the division by four. 16Mhz/4=4
    NVIC_ST_CURRENT_R = 0;
    NVIC_ST_CTRL_R = NVIC_ST_CTRL_ENABLE | NVIC_ST_CTRL_INTEN;
}


