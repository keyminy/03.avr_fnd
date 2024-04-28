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
			// ��ư�� ó�� ������ ����
			_delay_ms(60); // ����� �������⸦ ��ٸ���.
			previous_button_status[button_number] = BUTTON_PRESS; // ó�� ������ ���°� �ƴϴ�
			return 0; //���� ������ ������ ������ ���°� �ƴϴ�.
		} // ��ư�� ������ ������ ���¿����� ����� ������ ����
		else if(previous_button_status[button_number] == BUTTON_PRESS && buttonState == BUTTON_RELEASE){
			previous_button_status[button_number] = BUTTON_RELEASE; // ���� ��ư ���¸� üũ�ϱ� ���� �ʱ�ȭ
			_delay_ms(60); // ����� �������⸦ ��ٸ���.
			return 1; // ������ ������ ������ ����
		}
	// ���� HIGH�� ������ ������
	// ���� ������ ����ġ�� ������ �� ���°� �ƴϰų� ����ġ�� open�� ���� -> return 0;
	return 0;
}
