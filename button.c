#include "button.h"

unsigned char previous_button_status[BUTTON_NUMBER] = 
{BUTTON_RELEASE, BUTTON_RELEASE, BUTTON_RELEASE,BUTTON_RELEASE};

// declare function
void init_button(){
	BUTTON_DDR &= ~((1<<BUTTON1_PIN) | (1<<BUTTON2_PIN) | (1<<BUTTON3_PIN) | (1<<BUTTON4_PIN));
	//BUTTON_DDR = XXXX0000
}
uint8_t get_button(int button_pin, int button_number){
	uint8_t buttonState;
	
	buttonState = BUTTON_PIN & (1<< button_pin);
	if(buttonState && previous_button_status[button_number]== BUTTON_RELEASE){
			// 버튼이 처음 눌러진 상태
			_delay_ms(60); // 노이즈가 지나가기를 기다린다.
			previous_button_status[button_number] = BUTTON_PRESS; // 처음 눌러진 상태가 아니다
			return 0; //아직 완전히 눌렀다 떼어진 상태가 아니다.
		} // 버튼이 이전에 눌러진 상태였으면 현재는 떼어진 상태
		else if(previous_button_status[button_number] == BUTTON_PRESS && buttonState == BUTTON_RELEASE){
			previous_button_status[button_number] = BUTTON_RELEASE; // 다음 버튼 상태를 체크하기 위해 초기화
			_delay_ms(60); // 노이즈가 지나가기를 기다린다.
			return 1; // 완전히 눌렀다 떼어진 상태
		}
	// 아직 HIGH인 상태인 것이지
	// 아직 완전히 스위치를 눌렀다 뗀 상태가 아니거나 스위치가 open된 상태 -> return 0;
	return 0;
}
