/*  PORTD - FND ����
	PORTD[0..3]-7448���ڴ� BCD�Է�[ABCD]
	PORTD[4..7]-7448 COM������ �Է�[1000..1�ڸ� DIGIT�����ϴ� ��Ʈ]
*/
// 0~9999���� Up Cnt,Start Button�� PC0�� �̿���.

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

	DDRC = 0x00; // PORTC�� �Է����� ����

   while (1){
		pinc0 = PINC & 0x01;
		if(pinc0 == 0){
			// pinc0 == 0x00�� ���� ǥ��
			//����ġ�� ����  ����
			ms_count++;
			if(ms_count == 100){
				//1000ms = 1s
				ms_count = 0;
				sec_count++; // sec count�� ������Ŵ
			}
		}
	
		fnd_display();
		_delay_ms(5); //5ms���� fnd_display�Լ� ȣ��
	
		// sec count�� 60�ʵɶ� �ʱ�ȭ)
		if(sec_count >= 61) sec_count = 0;
	}
	return 0;
}
 
