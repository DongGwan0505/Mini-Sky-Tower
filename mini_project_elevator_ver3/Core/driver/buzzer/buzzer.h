/*
 * buzzer.h
 *
 *  Created on: Dec 25, 2025
 *      Author: kccistc
 */

#ifndef DRIVER_BUZZER_BUZZER_H_
#define DRIVER_BUZZER_BUZZER_H_

#include "stm32f4xx_hal.h" // MCU에 맞는 헤더 포함

typedef struct {
    GPIO_TypeDef * GPIOx;
    uint16_t pinNum;
    uint32_t prevTime;    // 시간 측정용
    uint8_t step;         // 현재 소리 단계 (0:꺼짐, 1:첫소리, 2:쉼, 3:뒷소리)
} hBuzzer;

void Buzzer_Init(hBuzzer *buzzer, GPIO_TypeDef * GPIOx, uint16_t pinNum);
void Buzzer_Ring_DingDong(hBuzzer *buzzer); // 백화점 소리 함수
void Buzzer_Execute(hBuzzer *buzzer);

#endif /* DRIVER_BUZZER_BUZZER_H_ */
