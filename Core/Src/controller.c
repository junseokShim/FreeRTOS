/*
 * controller.c
 *
 *  Created on: Feb 2, 2025
 *      Author: junseokshim
 */
#include "controller.h"
#include "stm32l4xx_hal.h" // Include the HAL header file for GPIO definitions
#include "stm32l4xx_hal_gpio.h" // Include the HAL header file for GPIO functions
#include "stm32l4xx_hal_rcc.h" // Include the HAL header file for RCC functions


void vTaskDCMotorControl(void *pvParameters)
{
	for(;;){
		// Configure the TIM2 peripheral
		TIM_HandleTypeDef htim2;
		TIM_OC_InitTypeDef sConfigOC = {0};

		__HAL_RCC_TIM2_CLK_ENABLE();

		htim2.Instance = TIM2;
		htim2.Init.Prescaler = 79;
		htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
		htim2.Init.Period = 999;
		htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
		htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
		if (HAL_TIM_PWM_Init(&htim2) != HAL_OK)
		{
			// Initialization Error
			Error_Handler();
		}

		sConfigOC.OCMode = TIM_OCMODE_PWM1;
		sConfigOC.Pulse = 500; // Set the pulse width
		sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
		sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
		if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_4) != HAL_OK)
		{
			// Configuration Error
			Error_Handler();
		}

		// Start PWM signal generation
		if (HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_4) != HAL_OK)
		{
			// PWM Generation Error
			Error_Handler();
		}

		// Control the duty cycle of the PWM signal
		uint16_t dutyCycle = (uint16_t)pvParameters;
		__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_4, dutyCycle); // Set duty cycle
		vTaskDelay(1000);

	}
}

void vTaskLEDOnOff(void *pvParameters)
{
	for(;;){
		HAL_GPIO_TogglePin(LED2_GPIO_Port, LED2_Pin);
		vTaskDelay(1000);
	}
}
