/*
 * controller.c
 *
 *  Created on: Feb 2, 2025
 *      Author: junseokshim
 */
#include "controller.h"

void vTaskLEDOnOff(void *pvParameters)
{
	for(;;){
		HAL_GPIO_TogglePin(LED2_GPIO_Port, LED2_Pin);
		vTaskDelay(500);
	}
}
