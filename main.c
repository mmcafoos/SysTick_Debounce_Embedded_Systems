/* Lab1 for Embedded Systems
 * Author: Alex Fay, Mark McAfoose
 * id# 801336907, 801149826
 * date: 04/05/2023
 * main.c
 */

#include "main.h"

int main(void)
{

    struct nvic_st_s *sysTick = (void*)SYSTICK_BASE; // construct SysTick at peripheral base

    sysTickInit(sysTick);

    gpioPortfInit();

    int sw, i; // sw to track button press, i to iterate pattern

    while(1){

        for(i = 0; i < 8; i++){

            do{

                sw = *GPIO_DATA_READ_R; // poll for button press

            } while(sw & (1 << SW_BIT_POS));

            *GPIO_DATA_WRITE_R &= 0x000;
            *GPIO_DATA_WRITE_R |= pattern[i];

            sysTickDelayMs(sysTick, 100); // delay between responses to debounce

            do{
                sw = *GPIO_DATA_READ_R; // poll for button release
            } while(!(sw & (1 << SW_BIT_POS)));

            sysTickDelayMs(sysTick, 100); // delay between responses to debounce

        }
    }
}

void sysTickInit(struct nvic_st_s* sysTick){

    sysTick->ctrl = 0x0; // make sure systick is off first
    sysTick->reload = F_CPU / 1000; // set reload value to the number of cycles in 1mS
    sysTick->current = 0; // start the counter at a known value (zero)
    sysTick->ctrl =
            (1 << ST_EN_POS) | // enable systick
            (1 << ST_CLKSRC_POS); // set clock source to system clock
    return;

}

void sysTickDelayMs(struct nvic_st_s* sysTick, unsigned long num){

    int i;
    /* Systick hits 0 every mS
     * however, we may get here in between
     * cycles, so mS to be delayed is
     * incrememnted by 1 so that
     * the delay is always AT LEAST
     * 1 mS */
    for(i = 0; i < num + 1; i++){
        while(sysTick->current > 50){
            ;
        }
    }
    return;

}

void gpioPortfInit(void){

    *RCGC_GPIO_R |= (1 << RCGCGPIO_PORTF_EN_POS); // enable the clock to the GPIO port

    while(!(*PRGPIO_R & (1 << PRGPIO_PORTF_RDY_POS))){}; // wait until peripheral is ready

    *GPIO_DEN_R =
            (1 << RED_BIT_POS) |
            (1 << GREEN_BIT_POS) |
            (1 << BLUE_BIT_POS) |
            (1 << SW_BIT_POS); // enable all digital functions for pins

    *GPIO_DIR_R =
            (1 << RED_BIT_POS) |
            (1 << GREEN_BIT_POS) |
            (1 << BLUE_BIT_POS); // configure pins 1, 2, 3 as outputs
    *GPIO_PEN_R = (1 << SW_BIT_POS); // pull up pin 4(SW1)
    return;

}
