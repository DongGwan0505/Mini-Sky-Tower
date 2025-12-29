/*
 * photo_interrupter.h
 *
 *  Created on: Dec 23, 2025
 *      Author: kccistc
 */

#ifndef DRIVER_PHOTO_INTERRUPTER_PHOTO_INTERRUPTER_H_
#define DRIVER_PHOTO_INTERRUPTER_PHOTO_INTERRUPTER_H_

#include "stm32f4xx_hal.h"
#include <stdint.h>

typedef struct {
    GPIO_TypeDef *GPIOx;
    uint16_t pinNum;
    volatile uint8_t event;
    volatile uint32_t count;
} hpi;

void Photo_Interrupter_Init(hpi *pi,GPIO_TypeDef *GPIOx,uint16_t pinNum);
void Photo_Interrupter_EXTI_Callback(hpi *pi);
uint8_t Photo_Interrupter_GetEvent(hpi *pi);

#endif
