/*
 * photo_interrupter.c
 *
 *  Created on: Dec 23, 2025
 *      Author: kccistc
 */

#include "photo_interrupter.h"

hpi photo;

void Photo_Interrupter_Init(hpi *pi, GPIO_TypeDef *GPIOx, uint16_t pinNum)
{
    pi->GPIOx = GPIOx;
    pi->pinNum = pinNum;
    pi->event = 0;
    pi->count = 0;
}

void Photo_Interrupter_EXTI_Callback(hpi *pi)
{
    pi->event = 1;
    pi->count++;
}

uint8_t Photo_Interrupter_GetEvent(hpi *pi)
{
    if (pi->event) {
        pi->event = 0;
        return 1;
    }
    return 0;
}
