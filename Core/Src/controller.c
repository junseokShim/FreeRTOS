/*
 * controller.c
 *
 *  Created on: Feb 2, 2025
 *      Author: junseokshim
 */
#include "controller.h"
#include "common.h"
#include "stm32l4xx_hal.h" // Include the HAL header file for GPIO definitions
#include "stm32l4xx_hal_gpio.h" // Include the HAL header file for GPIO functions
#include "stm32l4xx_hal_rcc.h" // Include the HAL header file for RCC functions


void vTaskControlHandler(void *pvParameters)
{
	    UartPacket receivedPacket;
    TIM_HandleTypeDef htim2;
    TIM_OC_InitTypeDef sConfigOC = {0};

    // TIM2 초기화
    __HAL_RCC_TIM2_CLK_ENABLE();

    htim2.Instance = TIM2;
    htim2.Init.Prescaler = 79;
    htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim2.Init.Period = 999;
    htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    if (HAL_TIM_PWM_Init(&htim2) != HAL_OK)
    {
        // 초기화 오류
        Error_Handler();
    }

    sConfigOC.OCMode = TIM_OCMODE_PWM1;
    sConfigOC.Pulse = 500; // 초기 펄스 폭 설정
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
    if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_4) != HAL_OK)
    {
        // 구성 오류
        Error_Handler();
    }

    // PWM 신호 생성 시작
    if (HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_4) != HAL_OK)
    {
        // PWM 생성 오류
        Error_Handler();
    }

    while (1)
    {
        printf("Waiting for control data... \r\n");

        // 제어 큐에서 패킷 수신 (무한 대기)
        if (xQueueReceive(controlQueue, &receivedPacket, portMAX_DELAY) == pdPASS)
        {
            printf("Received control data... \r\n");

            // receivedPacket.data[3] 값을 사용하여 PWM 듀티 사이클 조정
            uint16_t dutyCycle = (uint16_t)receivedPacket.data[3];
            printf("Duty Cycle: %d \r\n", dutyCycle);
			if (dutyCycle == 0)
            {
                // 듀티 사이클이 0이면 PWM 신호 중지
                if (HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_4) != HAL_OK)
                {
                    printf("Failed to stop PWM.\r\n");
                }
                else
                {
                    printf("PWM stopped.\r\n");
                }
            }
            else
            {
                // 듀티 사이클이 0이 아니면 PWM 신호 시작 및 듀티 사이클 설정
                if (HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_4) != HAL_OK)
                {
                    printf("Failed to start PWM.\r\n");
                }
                else
                {
                    __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_4, dutyCycle); // 듀티 사이클 설정
                    printf("PWM started with duty cycle: %d\r\n", dutyCycle);
                }
            }
        }
    }	
}

void vTaskLEDOnOff(void *pvParameters)
{
	for(;;){
		HAL_GPIO_TogglePin(LED2_GPIO_Port, LED2_Pin);
		vTaskDelay(1000);
	}
}
