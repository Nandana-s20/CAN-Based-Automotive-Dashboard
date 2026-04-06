/*
 * File:   timer0.c
 * Author: nanda
 *
 * Created on 11 March 2026, 11:41
 */


#include <xc.h>
#include "timer0.h"
#include "message_handler.h"
unsigned char blink = 0;
unsigned int timer =0;


void init_timer0(void) {
    /*
     * Setting instruction cycle clock (Fosc / 4) as the source of
     * timer0
     */

    /*Setting 8 bit timer register*/
    T08BIT = 1;

    /* Selecting internal clock source */
    T0CS = 0;

    /* Enabling timer0*/
    TMR0ON = 1;

    /* disabling prescaler*/
    PSA = 0;

    TMR0 = 6;

    /* Clearing timer0 overflow interrupt flag bit */
    TMR0IF = 0;

    /* Enabling timer0 overflow interrupt */
    TMR0IE = 1;
    T0PS2 = 1;
    T0PS1 = 1;
    T0PS0 = 1;

    GIE = 1;
    PEIE = 1;

}

void __interrupt() isr(void) {
    if (TMR0IF) {
        TMR0IF = 0;
        TMR0 = TMR0 + 6;
        timer++;
        if (timer >= 40) {
            timer = 0;
            blink = !blink;

            if (status == e_ind_left) {
                if (blink) {
                    LEFT_IND_ON();
                } else {
                    LEFT_IND_OFF();
                }
                RIGHT_IND_OFF();


            } else if (status == e_ind_right) {
                if (blink) {
                    RIGHT_IND_ON();
                } else {
                    RIGHT_IND_OFF();
                }


                LEFT_IND_OFF();
            } else if (status == e_ind_hazard) {
                if (blink) {
                    RIGHT_IND_ON();
                    LEFT_IND_ON();

                } else {
                    LEFT_IND_OFF();
                    RIGHT_IND_OFF();
                }
            } else {
                LEFT_IND_OFF();
                RIGHT_IND_OFF();
            }
        }
    }
}
