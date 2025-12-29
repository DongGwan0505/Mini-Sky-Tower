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

hBuzzer elevatorBuzzer;;

void Elevator_Init()
{
    StepMotor_Init();
    Button_Init(&btn_1F, GPIOC, GPIO_PIN_10);
    Button_Init(&btn_2F, GPIOC, GPIO_PIN_11);
    Button_Init(&btn_3F, GPIOC, GPIO_PIN_12);
    Photo_Interrupter_Init(&pi_1F, PI_F1_GPIO, PI_F1_PIN);
    Photo_Interrupter_Init(&pi_2F, PI_F2_GPIO, PI_F2_PIN);
    Photo_Interrupter_Init(&pi_3F, PI_F3_GPIO, PI_F3_PIN);
    Buzzer_Init(&elevatorBuzzer, GPIOB, GPIO_PIN_1);

    LCD_WriteStringXY(0, 0, "Init: Going 1F..");
    LCD_WriteStringXY(1, 0, "Wait please...  ");

    while (HAL_GPIO_ReadPin(PI_F1_GPIO, PI_F1_PIN) == GPIO_PIN_RESET) {
        Elevator_Down();
        HAL_Delay(1);
    }

    Elevator_Stop();
    ElevatorState = FIRST_F;
    Buzzer_Ring_DingDong(&elevatorBuzzer);

    LCD_WriteStringXY(0, 0, "Init Complete!  ");
    LCD_WriteStringXY(1, 0, "Elevator Ready. ");

    HAL_Delay(1000);
}

void Elevator_Up()
{
	StepMotor_SetDir(CW);
	StepMotor_Speed(300);
	StepMotor_Run();
}

void Elevator_Down()
{
	StepMotor_SetDir(CCW);
	StepMotor_Speed(300);
	StepMotor_Run();
}

void Elevator_Stop()
{
	StepMotor_Stop();
}

void Elevator_Move_1_to_3()
{
	Elevator_DispLCD();
	Buzzer_Execute(&elevatorBuzzer);

	static int target_F = 1;

	switch (ElevatorState)
	{
	case FIRST_F:

		if (Button_GetState(&btn_2F) == ACT_PUSHED) {
			pi_2F.event = 0;
			Elevator_Up();
			ElevatorState = MOVING_UP;
			target_F = 2;
		}

		if (Button_GetState(&btn_3F) == ACT_PUSHED) {
			pi_3F.event = 0;
			Elevator_Up();
			ElevatorState = MOVING_UP;
			target_F = 3;
		}

		break;
	case SECOND_F:

		if (Button_GetState(&btn_1F) == ACT_PUSHED) {
			pi_1F.event = 0;
			Elevator_Down();
			ElevatorState = MOVING_DOWN;
			target_F = 1;
		}

		if (Button_GetState(&btn_3F) == ACT_PUSHED) {
			pi_3F.event = 0;
			Elevator_Up();
			ElevatorState = MOVING_UP;
			target_F = 3;
		}

		break;
	case THIRD_F:

		if (Button_GetState(&btn_2F) == ACT_PUSHED) {
			pi_2F.event = 0;
			Elevator_Down();
			ElevatorState = MOVING_DOWN;
			target_F = 2;
		}

		if (Button_GetState(&btn_1F) == ACT_PUSHED) {
			pi_1F.event = 0;
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
			Buzzer_Ring_DingDong(&elevatorBuzzer);
		}
		else if (target_F == 3 && Photo_Interrupter_GetEvent(&pi_3F)) {
			Elevator_Stop();
			ElevatorState = THIRD_F;
			target_F = 5;
			Buzzer_Ring_DingDong(&elevatorBuzzer);
		}
		break;
	case MOVING_DOWN:
		if (target_F == 1 && Photo_Interrupter_GetEvent(&pi_1F)) {
			Elevator_Stop();
			ElevatorState = FIRST_F;
			target_F = 6;
			Buzzer_Ring_DingDong(&elevatorBuzzer);
		}
		else if (target_F == 2 && Photo_Interrupter_GetEvent(&pi_2F)) {
			Elevator_Stop();
			ElevatorState = SECOND_F;
			target_F = 7;
			Buzzer_Ring_DingDong(&elevatorBuzzer);
		}

		break;
	}
}

void Elevator_DispLCD()
{
    char line1[20];
    char line2[20];

    static int prevState = -1;

    if ( prevState != ElevatorState ) {
        prevState = ElevatorState;

        switch(ElevatorState) {
            case FIRST_F:
                // 1층: 로비
                sprintf(line1, "1F: GRAND LOBBY ");
                break;

            case SECOND_F:
                // 2층: 업무 시설
                sprintf(line1, "2F: BIZ SUITE   ");
                break;

            case THIRD_F:
                // 3층: 전망대/라운지
                sprintf(line1, "3F: SKY LOUNGE  ");
                break;

            case MOVING_UP:
                sprintf(line1, "  ^ GOING UP ^  ");
                break;

            case MOVING_DOWN:
                sprintf(line1, "  v GOING DN v  ");
                break;

            default:
                sprintf(line1, "System Error    ");
                break;
        }


        if ((ElevatorState == MOVING_UP) || (ElevatorState == MOVING_DOWN)) {
            sprintf(line2, "[Status]: RUN...");
        } else {
            sprintf(line2, "[Status]: STOP  ");
        }

        LCD_WriteStringXY(0, 0, line1);
        LCD_WriteStringXY(1, 0, line2);
    }
}

void Elevator_Height()
{
    static uint32_t prevTime = 0;

    if (HAL_GetTick() - prevTime > 1000)
    {
        prevTime = HAL_GetTick();

        Ruller_nonstop();
    }
}

