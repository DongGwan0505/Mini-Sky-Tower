#include "buzzer.h"

void Buzzer_Init(hBuzzer *buzzer, GPIO_TypeDef * GPIOx, uint16_t pinNum)
{
    buzzer->GPIOx = GPIOx;
    buzzer->pinNum = pinNum;
    buzzer->step = 0; // 초기 상태: 0 (꺼짐)
    HAL_GPIO_WritePin(buzzer->GPIOx, buzzer->pinNum, GPIO_PIN_RESET);
}

// 이 함수를 호출하면 "띠-딩~" 시퀀스를 시작합니다.
void Buzzer_Ring_DingDong(hBuzzer *buzzer)
{
    // 이미 울리고 있으면 무시하거나, 강제로 처음부터 다시 시작
    buzzer->step = 1; // 1단계 시작
    buzzer->prevTime = HAL_GetTick();
    HAL_GPIO_WritePin(buzzer->GPIOx, buzzer->pinNum, GPIO_PIN_SET); // 소리 ON
}

// 메인 루프에서 계속 돌아가며 시간을 체크하고 다음 소리를 냅니다.
void Buzzer_Execute(hBuzzer *buzzer)
{
    uint32_t curTime = HAL_GetTick();

    switch (buzzer->step)
    {
    case 0:
        // 아무것도 안 함 (대기 상태)
        break;

    case 1: // [1단계] "띠" (짧은 소리)
        // 100ms 동안 소리 냄
        if (curTime - buzzer->prevTime > 100)
        {
            HAL_GPIO_WritePin(buzzer->GPIOx, buzzer->pinNum, GPIO_PIN_RESET); // 소리 OFF
            buzzer->prevTime = curTime;
            buzzer->step = 2; // 다음 단계(쉬는 시간)로 이동
        }
        break;

    case 2: // [2단계] "..." (잠깐 쉼 - 끊어주는 느낌)
        // 50ms 동안 침묵
        if (curTime - buzzer->prevTime > 50)
        {
            HAL_GPIO_WritePin(buzzer->GPIOx, buzzer->pinNum, GPIO_PIN_SET); // 소리 ON
            buzzer->prevTime = curTime;
            buzzer->step = 3; // 다음 단계(긴 소리)로 이동
        }
        break;

    case 3: // [3단계] "딩~" (긴 소리)
        // 300ms 동안 소리 냄
        if (curTime - buzzer->prevTime > 300)
        {
            HAL_GPIO_WritePin(buzzer->GPIOx, buzzer->pinNum, GPIO_PIN_RESET); // 소리 OFF
            buzzer->step = 0; // 모든 단계 종료 -> 대기 상태로 복귀
        }
        break;
    }
}
