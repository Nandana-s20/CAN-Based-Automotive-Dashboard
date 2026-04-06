/*
 * File:   message_handler.c
 * Author: nanda
 *
 * Created on 11 March 2026, 11:40
 */


#include <xc.h>
#include <string.h>
#include "message_handler.h"
#include "msg_id.h"
#include "can.h"
#include "clcd.h"

static uint8_t speed =0;
static uint8_t gear =0;
static uint16_t rpm = 0;


volatile unsigned char status = e_ind_off;
unsigned char arr[8][3] = {"GN", "G1", "G2", "G3", "G4", "G5", "GR", "CO"};


void handle_speed_data(uint8_t *data, uint8_t len)
{
    //Implement the speed function
    {
        speed=data[0];
        clcd_putch((speed/10)+'0',LINE2(0));
        clcd_putch((speed%10)+'0',LINE2(1));
    }
}

void handle_gear_data(uint8_t *data, uint8_t len) 
{
    //Implement the gear function
    gear = data[0];
    clcd_print(arr[gear],LINE2(4));
}

void handle_rpm_data(uint8_t *data, uint8_t len) 
{
    //Implement the rpm function
    rpm = (data[0]<<8)| data[1];
    clcd_putch((rpm/1000)+'0',LINE2(7));
    clcd_putch(((rpm/100)%10)+'0',LINE2(8));
    clcd_putch(((rpm/10)%10)+'0',LINE2(9));
    clcd_putch((rpm%10)+'0',LINE2(10));
}

//void handle_engine_temp_data(uint8_t *data, uint8_t len) 
//{
//    //Implement the temperature function
//}

void handle_indicator_data(uint8_t *data, uint8_t len) 
{
    //Implement the indicator function
    status=data[0];
    if(status == e_ind_off)
    {
        clcd_print("OFF",LINE2(12));
    }
    else if(status == e_ind_left)
    {
        clcd_print("<--",LINE2(12));
    }
    else if(status == e_ind_right)
    {
        clcd_print("-->",LINE2(12));
    }
    else if(status == e_ind_hazard)
    {
        clcd_print("<->",LINE2(12));
    }
}

void process_canbus_data() 
{   
    //process the CAN bus data
    uint8_t can_rx_data[8];
    uint8_t len =0;
    uint16_t msg_id;
    can_receive(&msg_id,can_rx_data,&len);
    if(len>0)
    {
        if(msg_id == SPEED_MSG_ID)
        {
            handle_rpm_data(can_rx_data,len);
        }
        if(msg_id == GEAR_MSG_ID)
        {
            handle_gear_data(can_rx_data,len);
        }
        if(msg_id == RPM_MSG_ID)
        {
            handle_rpm_data(can_rx_data,len);
        }
        if(msg_id == INDICATOR_MSG_ID)
        {
            handle_indicator_data(can_rx_data,len);
        }
    }
}
