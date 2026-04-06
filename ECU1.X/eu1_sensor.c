/*
 * File:   eu1_sensor.c
 * Author: nanda
 *
 * Created on 24 February 2026, 12:51
 */


#include "eu1_sensor.h"
#include "adc.h"
#include "can.h"
#include "msg_id.h"
#include "uart.h"
#include"digital_keypad.h"


uint16_t get_speed(void)
{
    // Implement the speed function
    //read adc
    //convert --->0 to 99
    //can_transmit(SPEED_MSG_ID,str,len)
    
    uint16_t adc_val;
    uint16_t speed;
    
    adc_val = read_adc(SPEED_ADC_CHANNEL);
    
    speed = ((unsigned long int)adc_val/10.25);
    
    return speed;
}

unsigned char get_gear_pos()
{
    // Implement the gear function
    //read switch
    //update index
    //can_transmit(GEAR_MSG_ID,len)
    
    static unsigned char index = 0;
    unsigned char key;
    
    key =read_digital_keypad(STATE_CHANGE);
    if(key == GEAR_UP)
    {
        if(index < MAX_GEAR)
        {
            index++;
        }
         
    }
    else if(key == GEAR_DOWN)
    {
        if(index > 0)
        {
            index--;
        }
        else
        {
            index=0;
        }
    }
    else if(key == COLLISION)
    {
          index=7;
    }
     
    return index;
}
