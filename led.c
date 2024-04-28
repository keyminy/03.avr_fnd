#include "led.h"

void shift_left_ledon(){
	for(int i=0; i<8; i++){
		LED_PORT = 0x01 << i; 
		_delay_ms(200);
	}
}

void shift_right_ledon(){
	for(int i=0; i<8; i++){
		LED_PORT = 0x80 >> i; 
		_delay_ms(100);
	}
}

void flower_on(){
	LED_PORT = 0x00;
	_delay_ms(1000);
	for(int i=0;i<4;i++){
		LED_PORT |= (0b00001000 >> i) | (0b00010000 << i);
		_delay_ms(200);
	}
	_delay_ms(200);
}
void flower_off(){
	LED_PORT = 0xff;
	_delay_ms(1000);
	for(int i=0;i<4;i++){
		LED_PORT &= (0b01111111 >> i) & (0b11111110 << i);
		_delay_ms(200);
	}
	_delay_ms(200);
}