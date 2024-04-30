/*
 * 03.FND_TEST.c
 *
 * Created: 2024-04-26 오전 10:40:58
 * Author : HARMAN-27
 */ 

#include <stdbool.h>
//#include "extern.h"
#include "fnd.h"
#include "button.h"

extern void fnd_display(int d4,int d3,int d2,int d1);
extern void init_fnd(void);

uint32_t ms_count = 0; 
uint32_t sec_count = 0;

int main(void)
{
	bool state = false;
	// initialize state
	init_fnd();

		
    /* Replace with your application code */
    while (1) 
    {
		if(!state){

		}else{
			ms_count++;
			if(ms_count >= 1000){
				//1000ms = 1s
				ms_count = 0;
				sec_count++; // sec count를 증가시킴
			}
			fnd_display(
				sec_count/10%10, //d4
				sec_count%10, //d3
				ms_count/100%100, //d2
				ms_count/10%10 //d1
			);
			_delay_ms(4);
		}
				
		if(get_button(BUTTON1_PIN,BUTTON1)){
			state = !state;
		}

	}
}