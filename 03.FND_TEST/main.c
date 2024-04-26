/*
 * 03.FND_TEST.c
 *
 * Created: 2024-04-26 오전 10:40:58
 * Author : HARMAN-27
 */ 
#include "globals.h"
#include "fnd.h"
#include "button.h"

extern void fnd_display(void);
extern void init_fnd(void);

//unsigned int ms_count = 0; // unsigned int 길어요
uint32_t ms_count = 0; // ms를 재는 변수이다
uint32_t sec_count = 0;

int main(void)
{
	// initialize state
	init_fnd();
	
    /* Replace with your application code */
    while (1) 
    {
		fnd_display();
		_delay_ms(100); //1ms마다 fnd_display함수 호출
		ms_count++;
		if(ms_count == 1000){
			//1000ms = 1s
			ms_count = 0;
			sec_count++; // sec count를 증가시킴
		}
		if(get_button(BUTTON1_PIN,BUTTON1)){
			while(1){
				if(get_button(BUTTON1_PIN,BUTTON1)){
					break;
				}
			}
		}
	}
}
