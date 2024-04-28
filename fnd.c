#include "globals.h"
#include "fnd.h"


void init_fnd(void){
	FND_DDR = 0xFF;
	FND_PORT = 0x00;
}

// display the FND
void fnd_display(void){
	static int digit_position = 0; // �ڸ��� ����  ���� 0~3 : 0,1,2,3
	switch(digit_position){
		case 0: // 1����
			FND_PORT = 0x70 | (ms_count % 10) / 1; // 1���ڸ� digit����
			break;
		case 1: // 10����
			FND_PORT = 0xB0 | (ms_count % 100) / 10; // 10���ڸ� digit����
			break;
		case 2: // 100����
			FND_PORT = 0xD0 | (sec_count%10); // 100�ڸ� digit����
			break;
		case 3: // 1000����
			FND_PORT = 0xE0 | (sec_count % 100) / 10; // 1000�ڸ� digit ����
			break;
	}
	digit_position++;
	digit_position %= 4; // ���� ǥ���� �ڸ����� �غ��ϰ� �Լ� ����
}