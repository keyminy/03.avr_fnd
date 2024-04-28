#ifndef BUTTON_H_
#define BUTTON_H_

#include <avr/io.h> // PORTA DDRA 등의 symbom이 정의 되어 있다.
#include <util/delay.h> // _delay_ms 등의 함수가 들어있다.
#define BUTTON_DDR DDRC
#define BUTTON_PIN PINC // PORTD를 read하는 register, 전압5v를 읽으면 1, 0v를 읽으면 0

/* 버튼 번호 */
#define BUTTON1 0
#define BUTTON2 1
#define BUTTON3 2
#define BUTTON4 3

#define BUTTON1_PIN 0 // PORTC.0
#define BUTTON2_PIN 1 // PORTC.1
#define BUTTON3_PIN 2 // PORTC.2
#define BUTTON4_PIN 3 // PORTC.3

#define BUTTON_PRESS 1 //버튼을 누르면 high active-high
#define BUTTON_RELEASE 0 //버튼을 떼면 LOW
#define BUTTON_NUMBER 4 // 버튼 갯수는 4개다

// declare function
void init_button(void);
uint8_t get_button(int button_pin, int button_number);

#endif