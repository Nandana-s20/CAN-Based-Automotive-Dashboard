/*
 * File:   ecu2_sensor.c
 * Author: nanda
 *
 * Created on 03 March 2026, 20:07
 */

#include <xc.h>
#include "ecu2_sensor.h"
#include "adc.h"
#include "digital_keypad.h"
#include "can.h"
#include "msg_id.h"
#include "uart.h"

extern volatile IndicatorStatus cur_ind_status = e_ind_off;
unsigned long int get_rpm()
{
    //Implement the rpm function
    //read_adc
    //convert
    //can_trans
    unsigned long int adc_val;
    unsigned long int rpm;
    
    adc_val =read_adc(RPM_ADC_CHANNEL);
    rpm =(adc_val * 6000)/1023;
    
    return rpm;
}

//uint16_t get_engine_temp()
//{
    //Implement the engine temperature function
//}

IndicatorStatus process_indicator()
{
    //Implement the indicator function
    unsigned char key;
     
    key = read_digital_keypad(STATE_CHANGE);
    if(key == SWITCH1) 
    {
        cur_ind_status = e_ind_left;
        
    }
    else if(key ==  SWITCH2)
    {
        cur_ind_status = e_ind_right;
       
    }
    else if(key ==SWITCH3)
    {
        cur_ind_status = e_ind_off;
    }
    else if(key == SWITCH4)
    {
        cur_ind_status = e_ind_hazard;
    }
    return cur_ind_status;
    
}
