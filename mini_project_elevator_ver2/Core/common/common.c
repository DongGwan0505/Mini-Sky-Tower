/*
 * common.c
 *
 *  Created on: Dec 18, 2025
 *      Author: rhoblack
 */
#include "common.h"

extern TIM_HandleTypeDef htim3;
extern hpi pi_1F;
extern hpi pi_2F;
extern hpi pi_3F;

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if (htim->Instance == TIM2) { // 1ms call
		TimeWatch_ISR();
		StopWatch_ISR();
		FND_ISR();
	}
	else if (htim->Instance == TIM3) { // 0.1s call
	}
	else if (htim->Instance == TIM4) { // 0.1s call
		StepMotor_ISR();
	}
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if (GPIO_Pin == GPIO_PIN_6)
	{
		if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_6) == GPIO_PIN_SET) {
			__HAL_TIM_SET_COUNTER(&htim3, 0);
			HAL_TIM_Base_Start(&htim3);
		}
		else {
			HAL_TIM_Base_Stop(&htim3);
			uint16_t counter = __HAL_TIM_GET_COUNTER(&htim3);
			SR04_ConvertDistance(counter);
		}
	}

	if (GPIO_Pin == pi_1F.pinNum)
	{
		Photo_Interrupter_EXTI_Callback(&pi_1F);
	}

	else if (GPIO_Pin == pi_2F.pinNum)
	{
		Photo_Interrupter_EXTI_Callback(&pi_2F);
	}

	else if (GPIO_Pin == pi_3F.pinNum)
	{
		Photo_Interrupter_EXTI_Callback(&pi_3F);
	}
}
