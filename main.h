/* Lab1 for Embedded Systems
 * Author: Alex Fay, Mark McAfoose
 * id# 801336907, 801149826
 * date: 04/05/2023
 * main.h
 */

#ifndef MAIN_H_
#define MAIN_H_

// timebase defines
#define F_CPU 16000000
#define SYSTICK_BASE 0xE000E010

// sysctl defines
#define RCGCGPIO_PORTF_EN_POS (5)
#define PRGPIO_PORTF_RDY_POS (5)

// sysTick defines
#define ST_EN_POS (0)
#define ST_CLKSRC_POS (2)

// GPIO defines
#define RED_BIT_POS (1)
#define GREEN_BIT_POS (2)
#define BLUE_BIT_POS (3)
#define SW_BIT_POS (4)
#define RED 0x02
#define GREEN 0x08
#define BLUE 0x04
#define PURPLE 0x06
#define CYAN 0x0C
#define YELLOW 0x0A
#define WHITE 0x0E
#define BLACK 0x00

// SysCtl pointers
volatile unsigned long *RCGC_GPIO_R = (volatile unsigned long *)0x400FE608;
volatile unsigned long *PRGPIO_R = (volatile unsigned long *)0x400FEA08;

// GPIO pointers
volatile unsigned long *GPIO_DEN_R = (volatile unsigned long *)0x4002551C;
volatile unsigned long *GPIO_DIR_R = (volatile unsigned long *)0x40025400;
volatile unsigned long *GPIO_PEN_R = (volatile unsigned long *)0x40025510;
volatile unsigned long *GPIO_DATA_WRITE_R = (volatile unsigned long *)0x40025038;
volatile unsigned long *GPIO_DATA_READ_R = (volatile unsigned long *)0x40025040;

/* define color pattern to step
 * through according to the spec */
static unsigned long pattern[] = {
                                  RED,
                                  PURPLE,
                                  GREEN,
                                  CYAN,
                                  BLUE,
                                  YELLOW,
                                  WHITE,
                                  BLACK
};

// define a struct for the SysTick peripheral
struct nvic_st_s {
    volatile unsigned long ctrl;
    volatile unsigned long reload;
    volatile unsigned long current;
};

// SysTick function prototypes
void sysTickInit(struct nvic_st_s* sysTick);
void sysTickDelayMs(struct nvic_st_s* sysTick, unsigned long num);

// GPIO function prototypes
void gpioPortfInit(void);

#endif /* MAIN_H_ */
