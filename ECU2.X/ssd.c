 /*
 * File:   ssd.c
 * Author: nanda
 *
 * Created on 03 March 2026, 21:25
 */

#include <xc.h>
#include "ssd.h"

void init_ssd(void)
{
    //setting the control pins as output 
    CONTROL_PORT_DDR = CONTROL_PORT_DDR & 0xF0;          //TRISA = TRISA & 0xF0
    //setting the data pins as input
    DATA_PORT_DDR = 0x00;                                //TRISD = 0x00
    //initializing the control pins
    CONTROL_PORT = CONTROL_PORT & 0xF0;                  // PORTA = PORTA & 0xF0
}

void display(uint8_t *ssd)
{
    for(int i=0; i<4; i++)
    {
        DATA_PORT = ssd[i];
        CONTROL_PORT = (CONTROL_PORT & 0xF0) | (1<<i);
        for(int wait = 1000;wait--;);
    }
}
