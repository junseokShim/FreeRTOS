#include "packet_receiver.h"
#include "cmsis_os.h"
#include "module_sensors.h"
#include "controller.h"
#include "common.h"

uint8_t uartBuff[RX_BUFFER_SIZE] = {0x00, };
QueueHandle_t uartQueue;

void target_function(void)
{
	printf("Target packet received! Executing function... \r\n");
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	BaseType_t xHigherPriorityTaskWoken = pdFALSE;
	if (huart->Instance == USART1)
	{
		// 수신된 데이터의 크기를 확인
		size_t dataLength = huart->RxXferSize - huart->RxXferCount;

		// 수신된 데이터를 큐에 넣음
		UartPacket packet;
		memset(packet.data, 0, RX_BUFFER_SIZE); // Initialize packet data buffer
		memcpy(packet.data, uartBuff, dataLength);
		packet.length = dataLength;

		// 수신된 데이터가 버퍼 크기를 초과하는지 확인
		if (dataLength > RX_BUFFER_SIZE)
		{
			// 버퍼 초기화
			memset(uartBuff, 0, RX_BUFFER_SIZE);
		}
		else
		{
			// 수신된 데이터를 큐에 넣음
			xQueueSendFromISR(uartQueue, &packet, &xHigherPriorityTaskWoken);
		}

		// 다시 수신 대기
		HAL_UART_Receive_IT(&huart1, uartBuff, RX_BUFFER_SIZE);
	}
	portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

void vTaskUARTReceiver(void *pvParameters)
{
	uartQueue = xQueueCreate(10, sizeof(UartPacket));
	if (uartQueue == NULL)	{
		printf("Queue Generation Fail \r\n");
		return;		// 큐 생성 실패
	}

	// 센서 초기화
	initSensorBSP();

	// 첫 번째 수신 시작
	if (HAL_UART_Receive_IT(&huart1, uartBuff, RX_BUFFER_SIZE) != HAL_OK)	return;

	while (1)
	{
		printf("Waiting for data... \r\n");

		// 큐에서 수신된 데이터를 가져옴
		UartPacket packet;
		if (xQueueReceive(uartQueue, &packet, portMAX_DELAY) == pdPASS)
		{
			// 패킷을 문자열 형식으로 변환하여 출력
			char strPacket[RX_BUFFER_SIZE * 2 + 1];
			for (size_t i = 0; i < packet.length; i++)
			{
				sprintf(&strPacket[i * 2], "%02X ", packet.data[i]);
			}
			strPacket[packet.length * 2] = '\0'; // Null-terminate the string
			printf("Data Receiving Success: %s \r\n", strPacket);

			// 받은 데이터가 버퍼 크기를 초과하는지 확인
			size_t dataLength = packet.length;

			int reqType = packet.data[2];

			if (dataLength < RX_BUFFER_SIZE){
				xQueueReset(uartQueue);    //reset queue
				continue;
			}

			// 받은 데이터를 다시 TX로 전송
			if (HAL_UART_Transmit(&huart1, packet.data, dataLength, HAL_MAX_DELAY) != HAL_OK)
			{
				printf("Failed to transmit data.\r\n");
			}
			else {
				switch (reqType){
					case REQ_TYPE_SENSOR:
						printf("Here is sensor data \r\n");
						if(sensorQueue != NULL)
						{
							xQueueSend(sensorQueue, &packet, portMAX_DELAY);
						}
						break;
					case REQ_TYPE_CONTROL:
						printf("Here is control data \r\n");
						if(controlQueue != NULL)
						{
							xQueueSend(controlQueue, &packet, portMAX_DELAY);
						}
						break;
					default:
						target_function();
						break;
				}
			}
		}
		else{
			printf("Data Receiving Fail \r\n");
		}
		
		printf("Reset Queue \r\n");
		xQueueReset(uartQueue);    //reset queue
	}
}
