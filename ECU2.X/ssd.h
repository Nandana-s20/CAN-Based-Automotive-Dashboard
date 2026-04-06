/* 
 * File:   ssd.h
 * Author: nanda
 *
 * Created on 03 March 2026, 21:25
 */

#ifndef SSD_H
#define	SSD_H
#define DATA_PORT          PORTD
#define CONTROL_PORT       PORTA
#define DATA_PORT_DDR      TRISD
#define CONTROL_PORT_DDR   TRISA

void init_ssd(void);
void display(uint8_t *ssd);

#endif	/* SSD_H */

