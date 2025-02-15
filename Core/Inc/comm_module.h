/*
 * comm_module.h
 *
 *  Created on: Feb 2, 2025
 *      Author: junseokshim
 */
#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>
#include <string.h>

#ifndef INC_COMM_MODULE_H_
#define INC_COMM_MODULE_H_

#define RX_BUFFER_SIZE 1000

extern TaskHandle_t xTask1Handle;
extern TaskHandle_t xTask2Handle;

void vTask1(void *pvParameters);
void vTask2(void *pvParameters);
void vTaskSendTXData(char *pvParameters);

#endif /* INC_COMM_MODULE_H_ */
