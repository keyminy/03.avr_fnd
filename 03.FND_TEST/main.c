/*
 * 03.FND_TEST.c
 *
 * Created: 2024-04-26 오전 10:40:58
 * Author : HARMAN-27
 */ 
#include <stdbool.h>
#include "extern.h"
#include "fnd.h"
#include "button.h"

extern void fnd_display();
extern void init_fnd(void);

int ms_count = 0;
int sec_count = 0;

int main(void)
{
	bool state = false;
	// initialize state
	init_fnd();

		
    /* Replace with your application code */
    while (1) 
    {
		if(!state){
			fnd_stop_display();
		}else{
			ms_count++;
			if(ms_count >= 1000){
				//1000ms = 1s
				ms_count = 0;
				sec_count++; // sec count를 증가시킴
			}
			fnd_display();
			_delay_ms(4);
		}
				
		if(get_button(BUTTON1_PIN,BUTTON1)){
			state = !state;
		}

	}
}