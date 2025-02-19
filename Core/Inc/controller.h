/*
 * controller.h
 *
 *  Created on: Feb 2, 2025
 *      Author: junseokshim
 */
#include "main.h"
#include <stdint.h>

#ifndef INC_CONTROLLER_H_
#define INC_CONTROLLER_H_

// uint16_t pwm_value = 0;
extern TIM_HandleTypeDef htim2;

void vTaskLEDOnOff(void *pvParameters);
void vTaskDCMotorControl(void *pvParameters);

#endif /* INC_CONTROLLER_H_ */
