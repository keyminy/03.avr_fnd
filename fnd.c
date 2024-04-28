#include "globals.h"
#include "fnd.h"


void init_fnd(void){
	FND_DDR = 0xFF;
	FND_PORT = 0x00;
}

// display the FND
void fnd_display(void){
	static int digit_position = 0; // 자리수 선택  변수 0~3 : 0,1,2,3
	switch(digit_position){
		case 0: // 1단위
			FND_PORT = 0x70 | (ms_count % 10) / 1; // 1의자리 digit추출
			break;
		case 1: // 10단위
			FND_PORT = 0xB0 | (ms_count % 100) / 10; // 10의자리 digit추출
			break;
		case 2: // 100단위
			FND_PORT = 0xD0 | (sec_count%10); // 100자리 digit추출
			break;
		case 3: // 1000단위
			FND_PORT = 0xE0 | (sec_count % 100) / 10; // 1000자리 digit 추출
			break;
	}
	digit_position++;
	digit_position %= 4; // 다음 표시할 자리수를 준비하고 함수 종료
}