/*
 * Elevator.c
 *
 *  Created on: Dec 23, 2025
 *      Author: kccistc
 */

#include "Elevator.h"

int ElevatorState = FIRST_F;

hBtn btn_1F;
hBtn btn_2F;
hBtn btn_3F;

hpi pi_1F;
hpi pi_2F;
hpi pi_3F;

void Elevator_Init()
{
	StepMotor_Init();
	Button_Init(&btn_1F, GPIOC, GPIO_PIN_10);
	Button_Init(&btn_2F, GPIOC, GPIO_PIN_11);
	Button_Init(&btn_3F, GPIOC, GPIO_PIN_12);
	Photo_Interrupter_Init(&pi_1F, PI_F1_GPIO, PI_F1_PIN);
	Photo_Interrupter_Init(&pi_2F, PI_F2_GPIO, PI_F2_PIN);
	Photo_Interrupter_Init(&pi_3F, PI_F3_GPIO, PI_F3_PIN);

	while (!Photo_Interrupter_GetEvent(&pi_1F)) {
		Elevator_Down();
	}
	Elevator_Stop();
}

void Elevator_Up()
{
	StepMotor_SetDir(CW);
	StepMotor_Speed(500);
	StepMotor_Run();
}

void Elevator_Down()
{
	StepMotor_SetDir(CCW);
	StepMotor_Speed(500);
	StepMotor_Run();
}

void Elevator_Stop()
{
	StepMotor_Stop();
}

void Elevator_Move_1_to_3()
{
	Elevator_DispLCD();
	static int target_F = 1;

	switch (ElevatorState)
	{
	case FIRST_F:

		if (Button_GetState(&btn_2F) == ACT_PUSHED) {
			Elevator_Up();
			ElevatorState = MOVING_UP;
			target_F = 2;
		}

		if (Button_GetState(&btn_3F) == ACT_PUSHED) {
			Elevator_Up();
			ElevatorState = MOVING_UP;
			target_F = 3;
		}

		break;
	case SECOND_F:

		if (Button_GetState(&btn_1F) == ACT_PUSHED) {
			Elevator_Down();
			ElevatorState = MOVING_DOWN;
			target_F = 1;
		}

		if (Button_GetState(&btn_3F) == ACT_PUSHED) {
			Elevator_Up();
			ElevatorState = MOVING_UP;
			target_F = 3;
		}

		break;
	case THIRD_F:

		if (Button_GetState(&btn_2F) == ACT_PUSHED) {
			Elevator_Down();
			ElevatorState = MOVING_DOWN;
			target_F = 2;
		}

		if (Button_GetState(&btn_1F) == ACT_PUSHED) {
			Elevator_Down();
			ElevatorState = MOVING_DOWN;
			target_F = 1;
		}

		break;
	case MOVING_UP:
		if (target_F == 2 && Photo_Interrupter_GetEvent(&pi_2F)) {
			Elevator_Stop();
			ElevatorState = SECOND_F;
			target_F = 4;
		}
		else if (target_F == 3 && Photo_Interrupter_GetEvent(&pi_3F)) {
			Elevator_Stop();
			ElevatorState = THIRD_F;
			target_F = 5;
		}
		break;
	case MOVING_DOWN:
		if (target_F == 1 && Photo_Interrupter_GetEvent(&pi_1F)) {
			Elevator_Stop();
			ElevatorState = FIRST_F;
			target_F = 6;
		}
		else if (target_F == 2 && Photo_Interrupter_GetEvent(&pi_2F)) {
			Elevator_Stop();
			ElevatorState = SECOND_F;
			target_F = 7;
		}

		break;
	}
}

void Elevator_DispLCD()
{
	char str[80];
	static int prevState = FIRST_F;

	if ( prevState != ElevatorState ) {
		prevState = ElevatorState;

		if ((ElevatorState == MOVING_UP) || (ElevatorState == MOVING_UP) ) {
			sprintf(str," [RUN]:");
		}
		else {
			sprintf(str,"[STOP]:");
		}
		LCD_WriteStringXY(1, 0, str);
	}

}
