#ifndef BUTTON_H_
#define BUTTON_H_

#include <avr/io.h> // PORTA DDRA ���� symbom�� ���� �Ǿ� �ִ�.
#include <util/delay.h> // _delay_ms ���� �Լ��� ����ִ�.
#define BUTTON_DDR DDRC
#define BUTTON_PIN PINC // PORTD�� read�ϴ� register, ����5v�� ������ 1, 0v�� ������ 0

/* ��ư ��ȣ */
#define BUTTON1 0
#define BUTTON2 1
#define BUTTON3 2
#define BUTTON4 3

#define BUTTON1_PIN 0 // PORTC.0
#define BUTTON2_PIN 1 // PORTC.1
#define BUTTON3_PIN 2 // PORTC.2
#define BUTTON4_PIN 3 // PORTC.3

#define BUTTON_PRESS 1 //��ư�� ������ high active-high
#define BUTTON_RELEASE 0 //��ư�� ���� LOW
#define BUTTON_NUMBER 4 // ��ư ������ 4����

// declare function
void init_button(void);
uint8_t get_button(int button_pin, int button_number);

#endif