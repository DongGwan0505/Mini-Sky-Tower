///*
// * fnd.c
// *
// *  Created on: Dec 12, 2025
// *      Author: rhoblack
// */
//#include "fnd.h"
//
//FND_TypeDef fndDigitCom[4] = {
//		{FND_D1_GPIO, FND_D1_PIN},
//		{FND_D2_GPIO, FND_D2_PIN},
//		{FND_D3_GPIO, FND_D3_PIN},
//		{FND_D4_GPIO, FND_D4_PIN}
//};
//
//FND_TypeDef fndPin[8] = {
//		{FND_A_GPIO, FND_A_PIN},
//		{FND_B_GPIO, FND_B_PIN},
//		{FND_C_GPIO, FND_C_PIN},
//		{FND_D_GPIO, FND_D_PIN},
//		{FND_E_GPIO, FND_E_PIN},
//		{FND_F_GPIO, FND_F_PIN},
//		{FND_G_GPIO, FND_G_PIN},
//		{FND_DP_GPIO, FND_DP_PIN}
//};
//
//uint16_t fndNum = 0;
//uint16_t fndDP[4] = {0};
//
//void FND_ISR()
//{
//	FND_DispNum();
//}
//
//void FND_SetNum(uint16_t num)
//{
//	fndNum = num;
//}
//
//void FND_DispDigit(uint16_t digit, int position)
//{
//	const uint8_t segFont[11] = {
//			0x3f, // 0 => 0011 1111
//			0x06, // 1 => 0000 0110
//			0x5b, // 2 => 0101 1011
//			0x4f, // 3 => 0100 1111
//			0x66, // 4 => 0110 0110
//			0x6d, // 5 => 0110 1101
//			0x7d, // 6 => 0111 1101
//			0x07, // 7 => 0000 0111
//			0x7f, // 8 => 0111 1111
//			0x6f, // 9 => 0110 1111
//			0x80  // DP=> 1000 0000
//	};
//
//	uint8_t font = segFont[digit];
//	font = font | fndDP[position];
//
//	for (int i=0; i<8; i++) {
//		if (!(font & (1<<i))) {
//			HAL_GPIO_WritePin(fndPin[i].GPIOx, fndPin[i].GPIO_Pin, RESET);
//		}
//		else {
//			HAL_GPIO_WritePin(fndPin[i].GPIOx, fndPin[i].GPIO_Pin, SET);
//		}
//	}
//}
//
//void FND_AllOff()
//{
//	HAL_GPIO_WritePin(FND_D1_GPIO, FND_D1_PIN, SET);
//	HAL_GPIO_WritePin(FND_D2_GPIO, FND_D2_PIN, SET);
//	HAL_GPIO_WritePin(FND_D3_GPIO, FND_D3_PIN, SET);
//	HAL_GPIO_WritePin(FND_D4_GPIO, FND_D4_PIN, SET);
//}
//
//void FND_DigitOn(int digit)
//{
//	HAL_GPIO_WritePin(FND_D1_GPIO, FND_D1_PIN, SET);
//	HAL_GPIO_WritePin(FND_D2_GPIO, FND_D2_PIN, SET);
//	HAL_GPIO_WritePin(FND_D3_GPIO, FND_D3_PIN, SET);
//	HAL_GPIO_WritePin(FND_D4_GPIO, FND_D4_PIN, SET);
//	switch(digit)
//	{
//	case DIGIT_1000:
//		HAL_GPIO_WritePin(FND_D1_GPIO, FND_D1_PIN, RESET);
//		break;
//	case DIGIT_100:
//		HAL_GPIO_WritePin(FND_D2_GPIO, FND_D2_PIN, RESET);
//		break;
//	case DIGIT_10:
//		HAL_GPIO_WritePin(FND_D3_GPIO, FND_D3_PIN, RESET);
//		break;
//	case DIGIT_1:
//		HAL_GPIO_WritePin(FND_D4_GPIO, FND_D4_PIN, RESET);
//		break;
//	}
//}
//
//
//void FND_DispNum()
//{
//	static int digit = 0;
//	digit = (digit + 1) % 4;
//
//	switch(digit)
//	{
//	case DIGIT_1000:	// digit_1000
//		FND_AllOff();
//		FND_DispDigit(fndNum / 1000 % 10, DIGIT_1000);
//		FND_DigitOn(DIGIT_1000);
//		break;
//	case DIGIT_100:		// digit_100
//		FND_AllOff();
//		FND_DispDigit(fndNum / 100 % 10, DIGIT_100);
//		FND_DigitOn(DIGIT_100);
//		break;
//	case DIGIT_10:		// digit_10
//		FND_AllOff();
//		FND_DispDigit(fndNum / 10 % 10, DIGIT_10);
//		FND_DigitOn(DIGIT_10);
//		break;
//	case DIGIT_1:		// digit_1
//		FND_AllOff();
//		FND_DispDigit(fndNum % 10, DIGIT_1);
//		FND_DigitOn(DIGIT_1);
//		break;
//	}
//}
//
//void FND_SetDP(int position, int state)
//{
//	if (state == FND_DP_ON){
//		fndDP[position] = 0x80;
//	} else {
//		fndDP[position] = 0x00;
//	}
//}

/*
 * fnd.c
 * Modified for custom characters (cn)
 */
#include "fnd.h"

// 1. 폰트 배열을 전역으로 뺍니다 (다른 함수에서도 쓰기 위해)
const uint8_t fndFont[11] = {
		0x3f, // 0
		0x06, // 1
		0x5b, // 2
		0x4f, // 3
		0x66, // 4
		0x6d, // 5
		0x7d, // 6
		0x07, // 7
		0x7f, // 8
		0x6f, // 9
		0x80  // DP
};

// 2. 특수문자 정의
#define FND_CHAR_c  0x58  // 소문자 c (g+e+d)
#define FND_CHAR_n  0x54  // 소문자 n (g+e+c) -> m 대용
#define FND_CHAR_BLANK 0x00 // 꺼짐

// 3. 각 4자리 FND에 들어갈 실제 비트 패턴을 저장하는 배열
uint8_t fndData[4] = {0,};

FND_TypeDef fndDigitCom[4] = {
		{FND_D1_GPIO, FND_D1_PIN},
		{FND_D2_GPIO, FND_D2_PIN},
		{FND_D3_GPIO, FND_D3_PIN},
		{FND_D4_GPIO, FND_D4_PIN}
};

FND_TypeDef fndPin[8] = {
		{FND_A_GPIO, FND_A_PIN},
		{FND_B_GPIO, FND_B_PIN},
		{FND_C_GPIO, FND_C_PIN},
		{FND_D_GPIO, FND_D_PIN},
		{FND_E_GPIO, FND_E_PIN},
		{FND_F_GPIO, FND_F_PIN},
		{FND_G_GPIO, FND_G_PIN},
		{FND_DP_GPIO, FND_DP_PIN}
};

void FND_ISR()
{
	FND_DispNum();
}

// [중요] 기존 FND_SetNum 대신 이 함수를 사용하여 데이터를 채웁니다.
// 거리(cm)를 받아서 "숫자+cn" 형태로 버퍼에 넣는 함수
void FND_SetDistance(uint32_t dist)
{
	if (dist < 100) {
		// 100cm 미만일 때: [10자리][1자리][c][n]

		// 10의 자리 (0이면 끔)
		if (dist / 10 == 0) fndData[0] = FND_CHAR_BLANK;
		else                fndData[0] = fndFont[dist / 10];

		// 1의 자리
		fndData[1] = fndFont[dist % 10];

		// 문자 'c'
		fndData[2] = FND_CHAR_n;

		// 문자 'n'
		fndData[3] = FND_CHAR_n;
	}
	else {
		// 100cm 이상일 때: [100][10][1][c] 형태로 하거나, 그냥 숫자만 표시
		// 여기서는 숫자 4자리 표기 방식으로 처리
		fndData[0] = fndFont[(dist / 1000) % 10]; // 천의 자리 (없으면 0나옴)
		if (fndData[0] == fndFont[0]) fndData[0] = FND_CHAR_BLANK; // 앞자리 0 제거

		fndData[1] = fndFont[(dist / 100) % 10];
		fndData[2] = fndFont[(dist / 10) % 10];
		fndData[3] = fndFont[dist % 10];
	}
}

// 기존 FND_SetNum 호환성 유지 (필요하다면 수정해서 사용)
void FND_SetNum(uint16_t num)
{
	fndData[0] = fndFont[num / 1000 % 10];
	fndData[1] = fndFont[num / 100 % 10];
	fndData[2] = fndFont[num / 10 % 10];
	fndData[3] = fndFont[num % 10];
}

// [수정됨] 이제 숫자가 아니라 '패턴(font)'을 직접 받아서 찍습니다.
void FND_DispPattern(uint8_t font)
{
	for (int i=0; i<8; i++) {
		if (!(font & (1<<i))) {
			HAL_GPIO_WritePin(fndPin[i].GPIOx, fndPin[i].GPIO_Pin, RESET);
		}
		else {
			HAL_GPIO_WritePin(fndPin[i].GPIOx, fndPin[i].GPIO_Pin, SET);
		}
	}
}

void FND_AllOff()
{
	HAL_GPIO_WritePin(FND_D1_GPIO, FND_D1_PIN, SET);
	HAL_GPIO_WritePin(FND_D2_GPIO, FND_D2_PIN, SET);
	HAL_GPIO_WritePin(FND_D3_GPIO, FND_D3_PIN, SET);
	HAL_GPIO_WritePin(FND_D4_GPIO, FND_D4_PIN, SET);
}

void FND_DigitOn(int digit)
{
	HAL_GPIO_WritePin(FND_D1_GPIO, FND_D1_PIN, SET);
	HAL_GPIO_WritePin(FND_D2_GPIO, FND_D2_PIN, SET);
	HAL_GPIO_WritePin(FND_D3_GPIO, FND_D3_PIN, SET);
	HAL_GPIO_WritePin(FND_D4_GPIO, FND_D4_PIN, SET);

	// switch 대신 배열 인덱스로 처리 가능하지만 기존 로직 유지
	switch(digit)
	{
	case 0: HAL_GPIO_WritePin(FND_D1_GPIO, FND_D1_PIN, RESET); break;
	case 1: HAL_GPIO_WritePin(FND_D2_GPIO, FND_D2_PIN, RESET); break;
	case 2: HAL_GPIO_WritePin(FND_D3_GPIO, FND_D3_PIN, RESET); break;
	case 3: HAL_GPIO_WritePin(FND_D4_GPIO, FND_D4_PIN, RESET); break;
	}
}

// [수정됨] ISR에서 호출되는 함수
// 계산을 하지 않고, 미리 만들어진 fndData 배열을 뿌려주기만 합니다.
void FND_DispNum()
{
	static int digit = 0;

	// 1. 끕니다
	FND_AllOff();

	// 2. 현재 자리에 맞는 패턴을 세팅합니다. (fndData 배열 사용)
	// 기존 코드는 DIGIT_1000이 enum이었을 텐데, 여기선 인덱스(0~3)로 가정합니다.
	// fndData[0]: 천의자리(왼쪽), fndData[3]: 일의자리(오른쪽) 기준
	FND_DispPattern(fndData[digit]);

	// 3. 자리를 켭니다.
	FND_DigitOn(digit);

	// 4. 다음 자리 준비
	digit = (digit + 1) % 4;
}

