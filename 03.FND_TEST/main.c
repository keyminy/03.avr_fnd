/*
 * 03.FND_TEST.c
 *
 * Created: 2024-04-26 오전 10:40:58
 * Author : HARMAN-27
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

#define FND_DATA_DDR DDRC //PortC
#define FND_DATA_PORT PORTC //data Port

#define FND_DIGIT_DDR DDRB //자리수 선택하는것
#define FND_DIGIT_PORT PORTB 
#define FND_DIGIT_D1 4 //자리수1번 D1설정 4로
#define FND_DIGIT_D2 5 //자리수2번 D2설정 5로
#define FND_DIGIT_D3 6 //자리수3번 D3설정 6로
#define FND_DIGIT_D4 7 //자리수4번 D4설정 7로

void init_fnd(void);
void fnd_display(void);

int main(void)
{
	// initialize state
	init_fnd();
	
    /* Replace with your application code */
    while (1) 
    {
		fnd_display();
		_delay_ms(1); //1ms마다 fnd_display함수 호출
    }
}

void init_fnd(void){
	// PortC를 모두 출력(FND 8pin)으로 하는거니까 모두 write모드로 하기
	FND_DATA_DDR = 0xFF;
	FND_DIGIT_DDR |= 0xF0;// 4,5,6,7만 출력이니까 거기만 write모드
	
	#if 1 //common anode방식으로
		FND_DATA_PORT = ~0x00; // common anode : FND를 all off
	#else	// common cathode
		FND_DATA_PORT = 0x00; // PORTC 설정 : FND를 all off
	#endif
		
}

// display the FND
void fnd_display(void){
	
	#if 1 // common anode
		// 0을 찍을려면 g빼고 1로 16진수값 3F입니다, b는 0011_1111(common anode)
		// common cathode는 1100_0000이고, 16진수로 C0
									//0    1     2     3    4    5    6    7    8    9
		unsigned char fnd_font[] = {0xc0, 0xf9, 0xa4, 0xb0,0x99,0x92,0x82,0xd8,0x80,0x98,0x00};
	#else
		unsigned char fnd_font[] = {~0xc0, ~0xf9, ~0xa4, ~0xb0,~0x99,~0x92,~0x82,~0xd8,~0x80,~0x98,~0x00};
	#endif
		static int digit_position = 0; // 자리수 선택 변수 0~3 : 0,1,2,3
		
	switch(digit_position){
		case 0:
			#if 1
				FND_DIGIT_PORT = 0b10000000; // anode
			#else 
				FND_DIGIT_PORT = ~0b10000000; // cathode
			#endif
				FND_DATA_PORT = fnd_font[8]; // 8번 index write = 9을 사용함
			break;
		case 1:
			#if 1
			FND_DIGIT_PORT = 0b01000000; // anode
			#else
			FND_DIGIT_PORT = ~0b01000000; // cathode
			#endif
			FND_DATA_PORT = fnd_font[8]; // 8번 index write = 9을 사용함
			break;
		case 2:
			#if 1
			FND_DIGIT_PORT = 0b00100000; // anode
			#else
			FND_DIGIT_PORT = ~0b00100000; // cathode
			#endif
			FND_DATA_PORT = fnd_font[8];// 8번 index write = 9을 사용함
			break;
		case 3:
			#if 1
			FND_DIGIT_PORT = 0b00010000; // anode
			#else
			FND_DIGIT_PORT = ~0b00010000; // cathode
			#endif
			FND_DATA_PORT = fnd_font[8]; // 8번 index write = 9을 사용함
			break;
		default:
		break;
	}
	digit_position++;
	digit_position %= 4; // 다음 표시할 자리수를 준비하고 함수 종료
}

