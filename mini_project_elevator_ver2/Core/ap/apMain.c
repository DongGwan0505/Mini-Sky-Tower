/*
 * apMain.c
 *
 *  Created on: Dec 18, 2025
 *      Author: rhoblack
 */

#include "apMain.h"

extern I2C_HandleTypeDef hi2c1;
extern TIM_HandleTypeDef htim2; // 1ms timer interrupt
extern TIM_HandleTypeDef htim3;
extern UART_HandleTypeDef huart2;

enum {TIME_WATCH, STOP_WATCH, TIME_MODIFY, RULLER};
hBtn btnMode;





void apMain_Init()
{
	LCD_Init(&hi2c1);
	Ruller_Init();
	StepMotor_Init();
	Button_Init(&btnMode, GPIOC, GPIO_PIN_10);
	HAL_TIM_Base_Start_IT(&htim2);
	Elevator_Init();
}

void SeoulWatch_DispMode(int state)
{
	if (state == TIME_WATCH) {
		LCD_WriteStringXY(0, 0, "TIME  ");
	}
	else if (state == STOP_WATCH) {
		LCD_WriteStringXY(0, 0, "SWTC  ");
	}
	else if (state == TIME_MODIFY){
		LCD_WriteStringXY(0, 0, "MODI");
	} else {
		LCD_WriteStringXY(0, 0, "DIST   ");
	}
}

void apMain()
{
	//int watchState = TIME_WATCH;

	while(1)
	{
		Elevator_Move_1_to_3();
		/*
		SeoulWatch_DispMode(watchState);
		//TimeWatch_Excute();
		switch (watchState)
		{
		case TIME_WATCH:
			TimeWatch_Excute();
			if (Button_GetState(&btnMode) == ACT_RELEASED) {
				watchState = STOP_WATCH;
			}
			break;
		case STOP_WATCH:
			TimeWatch_Excute();
			StopWatch_Excute();
			if (Button_GetState(&btnMode) == ACT_RELEASED) {
				watchState = TIME_MODIFY;
			}
			break;
		case TIME_MODIFY:
			TimeWatch_Excute();
			TimeWatch_Modify();
			if (Button_GetState(&btnMode) == ACT_RELEASED) {
				watchState = RULLER;
			}
			break;
		case RULLER:
			TimeWatch_DispLCD();
			Ruller_Execute();
			if (Button_GetState(&btnMode) == ACT_RELEASED) {
				watchState = TIME_WATCH;
			}
			break;
		}
		 */
	}
}






