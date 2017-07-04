#include"UART.h"
#include<string.h>

SERIAL USB_begin(uint32_t baudrate){
    SERIAL aux;

    uint32_t integer = (16000000/(16*baudrate/100));
    uint32_t fraction = (integer)-((16000000/(16*baudrate))*100);

    SYSCTL_RCGCUART_R |= (1<<0);
    while(SYSCTL_RCGCUART_R&(1<<0) == 0);
    SYSCTL_RCGCGPIO_R |= (1<<0);
    while(SYSCTL_RCGCGPIO_R&(1<<0) == 0);
    GPIO_PORTA_AFSEL_R = (1<<0)|(1<<1);
    GPIO_PORTA_PCTL_R  = (1<<0)|(1<<4);
    //GPIO_PORTA_PCTL_R  = (1<<0)|(1<<1);
    GPIO_PORTA_DEN_R   = (1<<0)|(1<<1);

    UART0_CTL_R &=~(1<<0);//Check pg 918
    UART0_IBRD_R = (uint32_t)integer/100;//Check pg 914
    UART0_FBRD_R = (uint32_t)fraction;//Check pg 915
    UART0_LCRH_R = 0x3<<5;//Check pg 916
    UART0_CC_R = 0x0;//Check pg 939
    UART0_CTL_R = (1<<0)|(1<<8)|(1<<9);//Check pg 918
    aux.FR =&UART0_FR_R;  //Check pg 911
    aux.DR =&UART0_DR_R;  //Check pg 906
    /*Just a little delay. I don't know why. But without it the UART crashes*/
    uint32_t delay=0;
    for(delay=0;delay<3000;delay++);

    return aux;
}

SERIAL Bluetooth_begin(uint32_t baudrate){
    SERIAL aux;

    uint32_t integer = (16000000/(16*baudrate/100));
    uint32_t fraction = (integer)-((16000000/(16*baudrate))*100);

    SYSCTL_RCGCUART_R |= (1<<1);
    while(SYSCTL_RCGCUART_R&(1<<1) == 0);
    SYSCTL_RCGCGPIO_R |= (1<<1);
    while(SYSCTL_RCGCGPIO_R&(1<<1) == 0);
    GPIO_PORTB_AFSEL_R |= (1<<0)|(1<<1);
    GPIO_PORTB_PCTL_R  |= (1<<0)|(1<<4);
    GPIO_PORTB_DEN_R   |= (1<<0)|(1<<1);

    UART1_CTL_R &=~(1<<0);//Check pg 918
    UART1_IBRD_R = (uint32_t)integer/100;//Check pg 914
    UART1_FBRD_R = (uint32_t)fraction;//Check pg 915
    UART1_LCRH_R = 0x3<<5;//Check pg 916
    UART1_CC_R = 0x0;//Check pg 939
    UART1_CTL_R = (1<<0)|(1<<8)|(1<<9);//Check pg 918
    aux.FR =&UART1_FR_R;  //Check pg 911
    aux.DR =&UART1_DR_R;  //Check pg 906
    /*Just a little delay. I don't know why. But without it the UART crashes*/
    uint32_t delay=0;
    for(delay=0;delay<3000;delay++);

    //print(&aux,"AT");
    //while(read(&aux)!='O');
    //print(&aux, "AT+BAUD5");

    return aux;
}

SERIAL begin(char port, uint32_t RX,uint32_t TX){
    SERIAL aux;
    if(port == 'A'){
        SYSCTL_RCGCUART_R |= (1<<0);
        while(SYSCTL_RCGCUART_R&(1<<0) == 0);
        SYSCTL_RCGCGPIO_R |= (1<<0);
        while(SYSCTL_RCGCGPIO_R&(1<<0) == 0);
        GPIO_PORTA_AFSEL_R = (1<<RX)|(1<<TX);
        GPIO_PORTA_PCTL_R  = (1<<0)|(1<<4);
        GPIO_PORTA_DEN_R   = (1<<RX)|(1<<TX);

        UART0_CTL_R &=~(1<<0);//Check pg 918
        UART0_IBRD_R = 104;//Check pg 914
        UART0_FBRD_R = 16;//Check pg 915
        UART0_LCRH_R = 0x3<<5;//Check pg 916
        UART0_CC_R = 0x0;//Check pg 939
        UART0_CTL_R = (1<<0)|(1<<8)|(1<<9);//Check pg 918
        aux.FR =&UART0_FR_R;  //Check pg 911
        aux.DR =&UART0_DR_R;  //Check pg 906
    }else if(port == 'B'){
        SYSCTL_RCGCUART_R |= (1<<1);
        while(SYSCTL_RCGCUART_R&(1<<1) == 0);
        SYSCTL_RCGCGPIO_R |= (1<<1);
        while(SYSCTL_RCGCGPIO_R&(1<<1) == 0);
        GPIO_PORTB_AFSEL_R = (1<<RX)|(1<<TX);
        GPIO_PORTB_PCTL_R  = (1<<0)|(1<<4);
        GPIO_PORTB_DEN_R   = (1<<RX)|(1<<TX);

        UART1_CTL_R &=~(1<<0);//Check pg 918
        UART1_IBRD_R = 104;//Check pg 914
        UART1_FBRD_R = 11;//Check pg 915
        UART1_LCRH_R = 0x3<<5;//Check pg 916
        UART1_CC_R = 0x0;//Check pg 939
        UART1_CTL_R = (1<<0)|(1<<8)|(1<<9);//Check pg 918
        aux.FR =&UART1_FR_R;  //Check pg 911
        aux.DR =&UART1_DR_R;  //Check pg 906
    }
    /*Just a little delay. I don't know why. But without it the UART crashes*/
    uint32_t delay=0;
    for(delay=0;delay<30;delay++);

    return aux;
}
void print(SERIAL *serial, char *string){
    while(*string){
        write(serial,*(string++));
    }
}
void write(SERIAL *serial, char character){
    while((*serial->FR&(1<<5))!=0){}
    *serial->DR = character;
}

char read(SERIAL *serial){
    char cRead;
    while(*serial->FR&(1<<4)!=0);
    cRead = *serial->DR;
    return cRead;
}
