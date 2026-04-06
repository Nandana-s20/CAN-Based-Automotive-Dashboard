/*
 * File:   main.c
 * Author: nanda
 *
 * Created on 03 March 2026, 20:07
 */

#define _XTAL_FREQ 20000000

#include <xc.h>
#include "ecu2_sensor.h"
#include "adc.h"
#include "can.h"
#include "msg_id.h"
#include "uart.h"
//#include "ssd.h"
#include "timer0.h"
#include "digital_keypad.h"


void init_config(void)
{
    init_timer0();
    init_uart();
    init_adc();
    init_digital_keypad();
    //init_ssd();
    init_can();
    
    TRISB=0X00;
    PORTB=0X00;
}
//unsigned char digits[] ={0xE7,0X21,0XCB,0X6B,0X2D,0X6E,0XEE,0X23,0XEF,0X6F};
//unsigned char ssd[4];
 
int main()
{
    //call the functions
    unsigned long int rpm;
    uint8_t can_tx_data[2];
    uint8_t can_rx_data[8];
    uint8_t len =0;
    uint16_t msg_id;
    uint8_t rpm_rx;
    
    init_config();
    while(1)
    {
        rpm =get_rpm();
//        ssd[0]= digits[rpm/1000];
//        ssd[1]=digits[(rpm/100)%10];
//        ssd[2]=digits[(rpm/10)%10];
//        ssd[3]=digits[rpm%10];
//        
//        display(ssd);
        
        
        can_tx_data[0]=(uint8_t)(rpm>>8);
        can_tx_data[1]=(uint8_t)(rpm & 0xFF);
        can_transmit(RPM_MSG_ID,can_tx_data,2);
        __delay_ms(80);
        process_indicator();
        can_tx_data[0]=cur_ind_status;
        can_transmit(INDICATOR_MSG_ID,can_tx_data,1);
        
        __delay_ms(80);
    }
}   
        
//        if(cur_ind_status == e_ind_left)
//        {
//            if(blink)
//            {
//            LEFT_IND_ON();
//            }
//            else
//            {
//                LEFT_IND_OFF();
//            }
//            RIGHT_IND_OFF();
//         
//           
//        }
//        else if(cur_ind_status == e_ind_right)
//        {
//            if(blink)
//            {
//                RIGHT_IND_ON();
//            }
//            else
//            {
//                RIGHT_IND_OFF();
//            }
//        
//            
//            LEFT_IND_OFF();
//        }
//        else if(cur_ind_status == e_ind_hazard)
//        {
//            if(blink)
//            {
//            RIGHT_IND_ON();
//            LEFT_IND_ON();
//            
//            }
//            else
//            {
//            LEFT_IND_ON();
//            RIGHT_IND_ON();
//            }
//        }
//        else
//        {
//            LEFT_IND_OFF();
//            RIGHT_IND_OFF();
//        }
//        can_tx_data[0] = (uint8_t)(rpm>>8);
//        can_tx_data[0] =(uint8_t)(rpm&0xFF);
//        can_transmit(RPM_MSG_ID, can_tx_data,2);
//        
//        can_receive(&msg_id,can_rx_data,&len);
//        
//        rpm_rx=(can_rx_data[0]<<8)|can_rx_data[1];
//        puts("RPM");
//        putch((can_rx_data[0]%10)+'0');
//        putch((can_rx_data[0]/10)+'0');
//        
//        can_transmit(GEAR_MSG_ID,can_tx_gear,1);
//        __delay_ms(100);
//        can_receive(&msg_id,can_rx_data,&len);
//        
//        puts("GEAR:");
//        puts(arr[can_rx_data[0]]);
//        puts("\r\n");
//        
//        __delay_ms(100);
//        
         
