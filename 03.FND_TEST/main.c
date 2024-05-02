#include <stdbool.h>
#include "extern.h"
#include "fnd.h"
#include "button.h"

extern void fnd_display(bool dot1_state);
extern void fnd_stop_display(bool btn1_state,bool dot1_state);
extern void fnd_idle(void);
extern void init_fnd(void);

int ms_count = 0;
int sec_count = 0;
int ms_flash = 0;
int ms1000_flash = 0;

int main(void)
{
	bool state = false;
	bool btn1_state = false;
	bool dot1_state = false;
	// initialize state
	init_fnd();

    while (1) 
    {
		if(!state){
			fnd_stop_display(btn1_state,dot1_state);
			_delay_ms(1);
		}else{
			if(btn1_state){
				// stopwatch 모드
				ms_count++;
				ms_flash++;
				if(ms_count >= 1000){
					//1000ms = 1s
					ms_count = 0;
					sec_count++; // sec count를 증가시킴
					ms1000_flash++;
					dot1_state = !dot1_state;
				}
				fnd_display(dot1_state);
				_delay_ms(1);
			}
		}
				
		if(get_button(BUTTON1_PIN,BUTTON1)){
			state = !state;
			btn1_state = true;
		}else if(get_button(BUTTON2_PIN,BUTTON2)){
			ms_count = 0;
			ms_flash = 0;
			sec_count = 0;
			dot1_state = false;
			btn1_state = false;
		}

	}
}