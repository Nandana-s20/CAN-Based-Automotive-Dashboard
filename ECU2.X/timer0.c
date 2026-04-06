/*
 * File:   timer0.c
 * Author: nanda
 *
 * Created on 05 March 2026, 13:07
 */


#include <xc.h>
#include "timer0.h"

volatile unsigned char blink = 0;
volatile unsigned int timer = 0;

void init_timer0(void)
{
    TMR0ON = 1;
    T0CS = 0;
    PSA = 0;
    //pre-scaler 1:256
    T0PS2 = 1;
    T0PS1 = 1;
    T0PS0 = 1;
    TMR0 = 6;//START FROM 6TH TO 256 TICK
    GIE = 1;
    PEIE = 1;
    TMR0IE = 1; //TIMER INTERRUPT
    TMR0IF = 0;//TIMER0 FLAG
}

/*
 1:256 pre-scaler
 * time for 1 tick = 0.2us * 256 =51.2us
 * for 1 overflow = 256 ticks
 * pre-loading with 6-->250 ticks
 * 0.2us*250*256 = 12800us--> 12.8ms           ....ie time for 1 overflow
 */

void __interrupt() isr(void)
{
    if(TMR0IF)
    {
        TMR0IF = 0;
        TMR0 = TMR0 + 6;
        timer++;
        if(timer>= 40)  //40*12.8ms =512ms
        {
            timer = 0;
            blink = !blink;
        }
                
    }
}

