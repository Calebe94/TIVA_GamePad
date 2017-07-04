#include"tm4c123gh6pm.h"

// SysTick function must be replaced on line 86 in the "tm4c123gh6pm_startup_css.c"

#define ANALOG_Y 0<<1 //PE2
#define ANALOG_X 0<<2 //PE3

#define Y_AIN 1
#define X_AIN 2

#define ANALOG_X_INITIAL 2026
#define ANALOG_Y_INITIAL 2092

#define UP      0<<4 //PortC
#define RIGHT   0<<7 //PortC
#define LEFT    0<<5 //PortC
#define DOWN    0<<6 //PortC

#define Y       0<<1 //PortD
#define X       0<<3 //PortD
#define A       0<<2 //PortD
#define B       0<<0 //PortD

#define ACL     0<<2 //PortB
#define ACR     0<<4 //PortB

#define START   0<<3 //PortB (Will need a interrupt function) line 87.

#define BT_TX 1<<0  // PortB(Rx)
#define BT_RX 1<<1  // PortB(Tx)

#define D_UP !(GPIO_PORTC_DATA_R&(!UP))
#define D_DOWN !(GPIO_PORTC_DATA_R&(!DOWN))
#define D_RIGHT !(GPIO_PORTC_DATA_R&(!RIGHT))
#define D_LEFT !(GPIO_PORTC_DATA_R&(!LEFT))

#define ACT_A !(GPIO_PORTD_DATA_R&(!A))
#define ACT_B !(GPIO_PORTD_DATA_R&(!B))
#define ACT_X !(GPIO_PORTD_DATA_R&(!X))
#define ACT_Y !(GPIO_PORTD_DATA_R&(!Y))
#define ACT_R !(GPIO_PORTB_DATA_R&(!ACR))
#define ACT_L !(GPIO_PORTB_DATA_R&(!ACL))

#define PAUSE !(GPIO_PORTB_DATA_R&(!START))
