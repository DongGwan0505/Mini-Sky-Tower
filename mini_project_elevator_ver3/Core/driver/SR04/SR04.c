/*
 * SR04.c
 *
 *  Created on: Dec 19, 2025
 *      Author: kccistc
 */

#include "SR04.h"

hBtn btnTrigger;

SR04_t sr04Data;

uint32_t SR04_GetDistance()
{
	return sr04Data.distance;
}

uint32_t SR04_GetState()
{
	uint32_t flag = sr04Data.cmpltflag;
	sr04Data.cmpltflag = SR04_CLEAR;

	return flag;
}

void Ruller_Init()
{
	Button_Init(&btnTrigger, GPIOC, GPIO_PIN_12);
}

void SR04_ConvertDistance(uint16_t microSec) //microSec에는 타이머 값이 들어간다.
{
	sr04Data.distance = (uint32_t)(microSec * 0.017);
	sr04Data.cmpltflag = SR04_SET;
}

void SR04_Trigger()
{
	HAL_GPIO_WritePin(SR04_GPIO, SR04_PIN, GPIO_PIN_SET);
	HAL_Delay(1);
	HAL_GPIO_WritePin(SR04_GPIO, SR04_PIN, GPIO_PIN_RESET);
}

void Ruller_Execute()
{
	Ruller();
}

void Ruller()
{
	SR04_Trigger();
	if (Button_GetState(&btnTrigger) == ACT_RELEASED) {
		FND_SetNum(SR04_GetDistance());
		Ruller_DispLCD();
	}
}

void Ruller_nonstop()
{
	SR04_Trigger();
	//FND_SetNum(SR04_GetDistance());
	FND_SetDistance(SR04_GetDistance()-4);
}


void Ruller_DispLCD()
{
	char str[80];
	sprintf(str,"DIST: %03lu cm    ",sr04Data.distance);
	LCD_WriteStringXY(1, 0, str);
}
