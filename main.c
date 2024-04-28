/*  PORTD - FND 연결
	PORTD[0..3]-7448디코더 BCD입력[ABCD]
	PORTD[4..7]-7448 COM단자의 입력[1000..1자리 DIGIT선택하는 비트]
*/
// 0~9999까지 Up Cnt,Start Button은 PC0를 이용함.

#include <inttypes.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include "led.h"
#include "button.h"
#include "fnd.h"
#include "globals.h"

extern uint8_t get_button(int button_pin, int button_number);
extern void init_button();
extern void fnd_display(void);
extern void init_fnd(void);

uint32_t ms_count = 0;
uint32_t sec_count = 0;

int main()
{
	unsigned int pinc0;
	
	init_fnd();

	DDRC = 0x00; // PORTC를 입력으로 설정

   while (1){
		pinc0 = PINC & 0x01;
		if(pinc0 == 0){
			// pinc0 == 0x00과 같은 표현
			//스위치가 눌린  상태
			ms_count++;
			if(ms_count == 100){
				//1000ms = 1s
				ms_count = 0;
				sec_count++; // sec count를 증가시킴
			}
		}
	
		fnd_display();
		_delay_ms(5); //5ms마다 fnd_display함수 호출
	
		// sec count가 60초될때 초기화)
		if(sec_count >= 61) sec_count = 0;
	}
	return 0;
}
 
