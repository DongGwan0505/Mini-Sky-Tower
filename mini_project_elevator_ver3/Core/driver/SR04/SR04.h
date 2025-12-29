/*
 * SR04.h
 *
 *  Created on: Dec 19, 2025
 *      Author: kccistc
 */

#ifndef DRIVER_SR04_SR04_H_
#define DRIVER_SR04_SR04_H_

#include <stdint.h>
#include <stdio.h>
#include "stm32f4xx_hal.h"
#include "../button/button.h"
#include "../fnd/fnd.h"
#include "../lcd/lcd.h"

#define SR04_GPIO GPIOC
#define SR04_PIN  GPIO_PIN_8

typedef struct {
	uint32_t distance;
	uint32_t cmpltflag;
} SR04_t;

enum {SR04_CLEAR, SR04_SET};

uint32_t SR04_GetDistance();
uint32_t SR04_GetState();
void Ruller_Init();
void SR04_ConvertDistance(uint16_t microSec);
void SR04_Trigger();
void Ruller_Execute();
void Ruller();
void Ruller_nonstop();
void Ruller_DispLCD();
void Ruller_DispFND();


#endif /* DRIVER_SR04_SR04_H_ */
