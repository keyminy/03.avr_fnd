#ifndef FND_H_

#define FND_H_

#include <avr/io.h> // PORTA DDRA ���� symbom�� ���� �Ǿ� �ִ�.
#include <util/delay.h> // _delay_ms ���� �Լ��� ����ִ�.

typedef enum stopwatch_state {
	STOPPED, RUNNING, RESET
} t_stopwatch_state;

#define FND_DDR DDRD //������� + �ڸ��� �����ϴ°�
#define FND_PORT PORTD

void init_fnd(void);
void fnd_display(void);

#endif 