#include"ADC.h"

void ADC_Init(){
    SYSCTL_RCGCADC_R |= 0b01;
    while(SYSCTL_RCGCADC_R&0b01==0);

    SYSCTL_RCGCGPIO_R|=SYSCTL_RCGC2_GPIOE;
    while(SYSCTL_RCGCGPIO_R&SYSCTL_RCGC2_GPIOE==0);
    GPIO_PORTE_DIR_R  |= (ANALOG_X |ANALOG_Y );
    GPIO_PORTE_AFSEL_R|= (~ANALOG_X|~ANALOG_Y);
    GPIO_PORTE_DEN_R  &= (ANALOG_X |ANALOG_Y );
    GPIO_PORTE_AMSEL_R|= (~ANALOG_X|~ANALOG_Y);

    ADC0_ACTSS_R&=0b0000;
    ADC0_EMUX_R&=~0x0F00;
    ADC0_SSCTL2_R=0b01100110;
    ADC0_ACTSS_R|=0b0100;
}

unsigned long ADC_Read(unsigned int AINx){
    unsigned long result=0;
    ADC0_SSMUX2_R = AINx;
    ADC0_PSSI_R=0b0100;
    while(ADC0_RIS_R&0b0100==0);
    result = ADC0_SSFIFO2_R&0b111111111111;
    ADC0_ISC_R = 0b0100;
    return result;
}

int32_t Joystick_Map(int32_t value, int32_t known_min,  int32_t known_max, int32_t min, int32_t max){
    //Interpolação Linear é definida por: p(x) = f(x0)+(f(x1)-f(x0)/x1-x2)*(x-x0)
    return (int32_t)(value-known_min)*(max-min)/(known_max-known_min)+min;
}
