/*
 * recieve_packet_module.h
 *
 *  Created on: Feb 8, 2025
 *      Author: junseokshim
 */

#ifndef INC_PACKET_RECEIVER_H_
#define INC_PACKET_RECEIVER_H_

#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include <string.h>
#include <stdio.h>
#include "common.h"

#define RX_BUFFER_SIZE 8

extern UART_HandleTypeDef huart1;

extern uint8_t uartBuff[RX_BUFFER_SIZE];
extern uint16_t uartCnt;

typedef enum {
    REQ_TYPE_SENSOR = 0,
    REQ_TYPE_CONTROL = 1
} RequestType;

void target_function(void); // 특정 패킷 수신 시 호출할 함수
void vTaskUARTReceiver(void *pvParameters); // FreeRTOS 태스크: UART 데이터를 받아서 특정 패킷을 검사함.
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);

#endif /* INC_PACKET_RECEIVER_H_ */
