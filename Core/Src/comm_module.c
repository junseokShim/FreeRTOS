/*
 * comm_module.c
 *
 *  Created on: Feb 2, 2025
 *      Author: junseokshim
 */
#include "comm_module.h"

void vTaskSendTXData(char *pvParameters)
{
	while(1){
		printf("%s \r\n", pvParameters);
		vTaskDelay(pdMS_TO_TICKS(1000));
	}
}

void vTask1(void *pvParameters)
{
	char* str = pcTaskGetName(xTask2Handle);

	while(1) {
		printf("Operation in Task1 \r\n");

		if (eSuspended == eTaskGetState(xTask2Handle)){
			printf("Resume %s \r\n", str);
			vTaskResume(xTask2Handle);
		}

		else if (eSuspended != eTaskGetState(xTask2Handle)){
			printf("Suspend %s \r\n", str);
			vTaskSuspend(xTask2Handle);
		}
		vTaskDelay(pdMS_TO_TICKS(1000));
	}
}

void vTask2(void *pvParameters)
{
	while(1)
	{
		printf("Operation in Task2 \r\n");
		vTaskDelay(pdMS_TO_TICKS(1000));
	}
}
