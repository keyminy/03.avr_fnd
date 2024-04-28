#ifndef LED_H_
#define LED_H_

#include <util/delay.h> 
#include <avr/io.h>
#define LED_PORT PORTA
#define LED_DDR DDRA

void shift_left_ledon();
void shift_right_ledon();
void flower_on();
void flower_off();

#endif /* LED_H_ */

