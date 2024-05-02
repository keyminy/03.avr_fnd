#include <stdbool.h>
#include "fnd.h"
#include "extern.h"


void init_fnd(void){
	// PortC를 모두 출력(FND 8pin)으로 하는거니까 모두 write모드로 하기
	FND_DATA_DDR = 0xFF;
	FND_DIGIT_DDR |= 0xF0;// 4,5,6,7만 출력이니까 거기만 write모드
	
	FND_DATA_PORT = 0x00; // PORTC 설정 : FND를 all off

}

// display the FND
void fnd_display(bool dot1_state){
	
	// 0을 찍을려면 g빼고 1로 16진수값 3F입니다, b는 0011_1111(common anode)
	// common cathode는 1100_0000이고, 16진수로 C0
	//0    1     2     3    4    5    6    7    8    9		dp(10번방)
	unsigned char fnd_font[] = {~0xc0, ~0xf9, ~0xa4, ~0xb0,~0x99,~0x92,~0x82,~0xd8,~0x80,~0x98,~0x7f};

	static int digit_position = 0; // 자리수 선택  변수 0~3 : 0,1,2,3
	static int dp1 = 0x00;
	
	if(dot1_state){
		dp1 = fnd_font[10];
	}else {
		dp1 = 0x00;
	}
	
	switch(digit_position){
		case 0: // 1단위 : 100ms마다

		FND_DIGIT_PORT = ~0b10000000; // cathode
		FND_DATA_PORT = fnd_font[ms_count/10%10];
		break;
		
		case 1: // 10단위 : 10ms마다
		FND_DIGIT_PORT = ~0b01000000; // cathode
		FND_DATA_PORT =fnd_font[ms_count/100%100] | dp1;
		break;
		
		case 2: // 100단위 : 초의 1의자리수
		FND_DIGIT_PORT = ~0b00100000; // cathode
		FND_DATA_PORT = fnd_font[sec_count%10];
		break;
		
		case 3: // 1000단위 : 초의 10의자리수
		FND_DIGIT_PORT = ~0b00010000; // cathode
		FND_DATA_PORT = fnd_font[sec_count/10%6];
		break;
	}
	digit_position++;
	digit_position %= 4; // 다음 표시할 자리수를 준비하고 함수 종료
}

void fnd_stop_display(bool btn1_state,bool dot1_state){
	static int digit_position = 0; // 자리수 선택  변수 0~3 : 0,1,2,3
	static int dp1 = 0x00;
	
	unsigned char fnd_font[] = {~0xc0, ~0xf9, ~0xa4, ~0xb0,~0x99,~0x92,~0x82,~0xd8,~0x80,~0x98,~0x7f};
		
	if(dot1_state){
		dp1 = fnd_font[10];
	}else {
		dp1= 0x00;
	}
		
	switch(digit_position){
		case 0:
		FND_DIGIT_PORT = ~0b10000000; // cathode
		if(!btn1_state)
			FND_DATA_PORT = stop_logic(digit_position);
		else
			FND_DATA_PORT = fnd_font[ms_count/10%10];
		break;
		case 1:
		FND_DIGIT_PORT = ~0b01000000; // cathode
		if(!btn1_state)
			FND_DATA_PORT = stop_logic(digit_position);
		else
			FND_DATA_PORT =fnd_font[ms_count/100%100] | dp1;
		break;
		case 2:
		FND_DIGIT_PORT = ~0b00100000; // cathode
		if(!btn1_state)
			FND_DATA_PORT = stop_logic(digit_position);
		else
			FND_DATA_PORT = fnd_font[sec_count%10];
		break;
		case 3:
		FND_DIGIT_PORT = ~0b00010000; // cathode
		if(!btn1_state)
			FND_DATA_PORT = stop_logic(digit_position);
		else
			FND_DATA_PORT = fnd_font[sec_count/10%6];
		break;
	}
	digit_position++;
	digit_position %= 4; // 다음 표시할 자리수를 준비하고 함수 종료
}

int stop_logic(int digit_position){
	static  int  ms;
	static int turn; // Determine how many cycles it is.
	static int circle;
	//Specifies the characters to cycle through.
	unsigned char fnd_font[10]={~0xfe,~0xfe,~0xfe,~0xfe,~0xcf,~0xf7,~0xf7,~0xf7,~0xf7,~0xf9};
	// Note : Currently, If you look at fnd_font value, it will rotate counterclockwise!.
	unsigned char fnd_index[10]={0,1,2,3,3,3,2,1,0,0};
	
	if(ms == 100){
		ms %= 100;
		turn++;
	}
	if(turn == 10){
		circle++;
		turn %= 10;
	}
	
	switch(circle){
		case 0:
		ms++;
		//fnd counterclockwise
		if(digit_position == fnd_index[turn]){
			return fnd_font[turn];
		}
		break;
		case 1:
		//fnd all off
		ms++;
		return 0x00;
		break;
		case 2:
		//fnd clockwise
		if(digit_position == fnd_index[9-turn]){
			return fnd_font[9-turn];
		}
		ms++;
		break;
		case 3:
		//fnd all off
		ms++;
		return 0x00;
		break;
		default:
		ms++;
		circle = 0;
		break;
	}
	return 0x00;
}