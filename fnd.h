#ifndef FND_H_

#define FND_H_

#include <avr/io.h> // PORTA DDRA 등의 symbom이 정의 되어 있다.
#include <util/delay.h> // _delay_ms 등의 함수가 들어있다.

typedef enum stopwatch_state {
	STOPPED, RUNNING, RESET
} t_stopwatch_state;

#define FND_DDR DDRD //숫자출력 + 자리수 선택하는것
#define FND_PORT PORTD

void init_fnd(void);
void fnd_display(void);

#endif 