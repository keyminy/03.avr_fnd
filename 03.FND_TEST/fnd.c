﻿#include "globals.h"
#include "fnd.h"

void init_fnd(void){
	// PortC를 모두 출력(FND 8pin)으로 하는거니까 모두 write모드로 하기
	FND_DATA_DDR = 0xFF;
	FND_DIGIT_DDR |= 0xF0;// 4,5,6,7만 출력이니까 거기만 write모드
	t_stopwatch_state state = STOPPED;
	
	#if 0 //common anode방식으로
	FND_DATA_PORT = ~0x00; // common anode : FND를 all off
	#else	// common cathode
	FND_DATA_PORT = 0x00; // PORTC 설정 : FND를 all off
	#endif
	
}

// display the FND
void fnd_display(void){
	
	#if 0 // common anode
	// 0을 찍을려면 g빼고 1로 16진수값 3F입니다, b는 0011_1111(common anode)
	// common cathode는 1100_0000이고, 16진수로 C0
	//0    1     2     3    4    5    6    7    8    9		dp(10번방)
	unsigned char fnd_font[] = {0xc0, 0xf9, 0xa4, 0xb0,0x99,0x92,0x82,0xd8,0x80,0x98,0x7f};
	#else
	unsigned char fnd_font[] = {~0xc0, ~0xf9, ~0xa4, ~0xb0,~0x99,~0x92,~0x82,~0xd8,~0x80,~0x98,~0x7f};
	#endif
	static int digit_position = 0; // 자리수 선택  변수 0~3 : 0,1,2,3
	
	switch(digit_position){
		case 0: // 1단위
		#if 0
		FND_DIGIT_PORT = 0b10000000; // anode
		FND_DATA_PORT = fnd_font[(ms_count%10)]& fnd_font[10];
		#else
		FND_DIGIT_PORT = ~0b10000000; // cathode
		// sec_count % 10 = 0~9까지 빙글빙글
		FND_DATA_PORT = fnd_font[(ms_count%10)] | fnd_font[10];
		#endif
		FND_DATA_PORT = fnd_font[(ms_count%10)];
		
		break;
		case 1: // 10단위
		#if 0
		FND_DIGIT_PORT = 0b01000000; // anode
		FND_DATA_PORT = fnd_font[(ms_count/100) % 100]& fnd_font[10]; //초의 10의자리수가 나옴
		#else
		FND_DIGIT_PORT = ~0b01000000; // cathode
		FND_DATA_PORT = fnd_font[(ms_count/100) % 100]| fnd_font[10]; //초의 10의자리수가 나옴
		#endif
		FND_DATA_PORT = fnd_font[(ms_count/100) % 100]; //초의 10의자리수가 나옴
		break;
		case 2: // 100단위
		#if 0
		FND_DIGIT_PORT = 0b00100000; // anode
		FND_DATA_PORT = fnd_font[(sec_count/60)%10] & fnd_font[10];// 분의 1의자리수가 나옴.
		#else
		FND_DIGIT_PORT = ~0b00100000; // cathode
		FND_DATA_PORT = fnd_font[(sec_count/60)%10] | fnd_font[10];// 분의 1의자리수가 나옴.
		#endif
		FND_DATA_PORT = fnd_font[(sec_count/60)%10];// 분의 1의자리수가 나옴.
		break;
		case 3: // 1000단위
		#if 0
		FND_DIGIT_PORT = 0b00010000; // anode
		FND_DATA_PORT = fnd_font[(sec_count/600)%6]& fnd_font[10];
		#else
		FND_DIGIT_PORT = ~0b00010000; // cathode
		FND_DATA_PORT = fnd_font[(sec_count/600)%6]| fnd_font[10];
		#endif
		FND_DATA_PORT = fnd_font[(sec_count/600)%6];
		break;
		default:
		break;
	}
	digit_position++;
	digit_position %= 4; // 다음 표시할 자리수를 준비하고 함수 종료
}

