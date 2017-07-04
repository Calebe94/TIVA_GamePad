#include"gamepad.h"


void printf_Dir(SERIAL *uart, unsigned int up, unsigned int down, unsigned int left, unsigned int right){
    // For some reasan the sprintf() doesn't work in microcontrollers
    // Problably because these kind of function take a lot of stack
    // See: https://e2e.ti.com/support/microcontrollers/tiva_arm/f/908/t/242208
    char aux[] = "U: ;D: ;L: ;R: ;";
    aux[2] = (char)48|up;
    aux[6] = (char)48|down;
    aux[10]= (char)48|left;
    aux[14]= (char)48|right;
    // Print aux to UART
    print(uart, aux);
}

void printf_Act(SERIAL *uart, uint32_t a, uint32_t b, uint32_t x, uint32_t y, uint32_t al, uint32_t ar){
    // For some reasan the sprintf() doesn't work in microcontrollers
    // Problably because these kind of function take a lot of stack
    // See: https://e2e.ti.com/support/microcontrollers/tiva_arm/f/908/t/242208
    char aux[] = "A: ;B: ;X: ;Y: ;AL: ;AR: ;";
    aux[2] = (char)48|a;
    aux[6] = (char)48|b;
    aux[10]= (char)48|x;
    aux[14]= (char)48|y;
    aux[19]= (char)48|al;
    aux[24]= (char)48|ar;
    //Print aux to UART
    print(uart,aux);
}

void printf_Analog(SERIAL *uart, int32_t x_value, int32_t y_value){
    // For some reasan the sprintf() doesn't work in microcontrollers
    // Problably because these kind of function take a lot of stack
    // See: https://e2e.ti.com/support/microcontrollers/tiva_arm/f/908/t/242208
    /*
     * Foi Necessário uma conversão dos valores analógicos(decimais), para uma String;
     * A Primeira forma que eu pensei foi em converter os valores de Milhar, cententa, dezena e unidade
     * individualmente e atribuir cada valor em sua respectiva posição do vetor de caracteres.
     *
     * */

    char values[] = "AX:    ;AY:    ;";
    uint8_t milhar,centena,dezena,unidade;

    // X axis value conversion
    milhar =(uint8_t)(x_value/1000);
    centena=(uint8_t)(x_value-(milhar*1000))/100;
    dezena =(uint8_t)(x_value-(milhar*1000)-(centena*100))/10;
    unidade=(uint8_t)(x_value-(milhar*1000)-(centena*100)-(dezena*10));

    values[3] = (char)48|milhar;
    values[4] = (char)48|centena;
    values[5] = (char)48|dezena;
    values[6] = (char)48|unidade;

    // Y axis value conversion
    milhar =(uint8_t)(y_value/1000);
    centena=(uint8_t)(y_value-(milhar*1000))/100;
    dezena =(uint8_t)(y_value-(milhar*1000)-(centena*100))/10;
    unidade=(uint8_t)(y_value-(milhar*1000)-(centena*100)-(dezena*10));

    values[11] = (char)48|milhar;
    values[12] = (char)48|centena;
    values[13] = (char)48|dezena;
    values[14] = (char)48|unidade;

    print(uart,values);
    print(uart,"\n");
}


