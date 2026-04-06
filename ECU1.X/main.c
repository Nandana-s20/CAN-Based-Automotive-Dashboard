/*
 * File:   main.c
 * Author: nanda
 *
 * Created on 24 February 2026, 12:22
 */

#define _XTAL_FREQ 20000000

#include "adc.h"
#include "can.h"
#include "eu1_sensor.h"
#include "digital_keypad.h"
#include "msg_id.h"
#include "uart.h"
unsigned char arr[8][3] = {"GN", "G1", "G2", "G3", "G4", "G5", "GR", "CO"};

int main() {
    //Call the functions
    //init_config-adc,(mkp,clcd)or(dkp and uart))



    uint16_t speed; //2bytes we are taking
    unsigned char gear;

    uint8_t can_tx_data[1];
    uint8_t can_rx_data[8];
    uint8_t len = 0;
    uint16_t msg_id;


    init_adc();
    init_digital_keypad();
    init_uart();
    init_can();

    while (1) {
        //speed from adc

        speed = get_speed();
        __delay_ms(50);
        can_tx_data[0] = (uint8_t) speed;
        can_transmit(SPEED_MSG_ID, can_tx_data, 1);

        //gear
        gear = get_gear_pos();
        __delay_ms(50);
        can_tx_data[0] = gear;
        can_transmit(GEAR_MSG_ID, can_tx_data, 1);
    }

}

//display in tera
//        if (speed != prev_speed || gear != prev_gear) {
//            puts("SPEED;");
//            putch((speed / 10) + '0');
//            putch((speed % 10) + '0');
//
//            puts("GEAR:");
//
//            puts(arr[gear]);
//
//            puts("\r\n");
//            __delay_ms(200);
//            prev_speed =speed;
//            prev_gear = gear;
//        }


