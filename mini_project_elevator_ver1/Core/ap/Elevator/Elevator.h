/*
 * Elavator.h
 *
 *  Created on: Dec 23, 2025
 *      Author: kccistc
 */

#ifndef AP_ELEVATOR_ELEVATOR_H_
#define AP_ELEVATOR_ELEVATOR_H_

#include <stdio.h>
#include "stm32f4xx_hal.h"
#include "../driver/StepMotor/StepMotor.h"
#include "../driver/photo_interrupter/photo_interrupter.h"
#include "../../driver/button/button.h"
#include "../../driver/lcd/lcd.h"

#define PI_F1_GPIO GPIOB
#define PI_F1_PIN  GPIO_PIN_13
#define PI_F2_GPIO GPIOB
#define PI_F2_PIN  GPIO_PIN_14
#define PI_F3_GPIO GPIOB
#define PI_F3_PIN  GPIO_PIN_15

enum {FIRST_F, SECOND_F, THIRD_F, MOVING_UP, MOVING_DOWN};

extern hBtn btn_1F;
extern hBtn btn_2F;
extern hBtn btn_3F;

extern hpi pi_1F;
extern hpi pi_2F;
extern hpi pi_3F;

void Elevator_Init();
void Elevator_Up();
void Elevator_Down();
void Elevator_Stop();
void Elevator_Move_1_to_3();
void Elevator_DispLCD();

#endif /* AP_ELEVATOR_ELEVATOR_H_ */
