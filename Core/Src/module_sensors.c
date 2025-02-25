/*
 * protocol_parser_sensor_info.h
 *
 *  Created on: Feb 15, 2025
 *      Author: junseokshim
 */
#include "module_sensors.h"
#include "common.h"

TSENSOR_InitTypeDef gTemp = {};

void initSensorBSP()
{
	if(BSP_HSENSOR_Init() != 0)
	{
		printf("Error initializing HSENSOR\n");
		return;
	}
	if(0xBC == HTS221_H_ReadID(HTS221_DEVICE_ID))
	{
		HTS221_H_Init((uint16_t)HTS221_DEVICE_ID);
		HTS221_T_Init((uint16_t)HTS221_DEVICE_ID, &gTemp);
	}

	if (LPS22HB_WHO_AL_I_VAL == LPS22HB_P_ReadID(LPS22HB_I2C_ADDRESS))
	{
		LPS22HB_P_Init(LPS22HB_I2C_ADDRESS);
	}
}

/**
 * @brief Task to handle sensor data.
	while (1)
	{
		UartPacket receivedPacket;
 * @param pvParameters Pointer to the parameters passed to the task (not used).
 */
void vTaskSensorHandler(void *pvParameters)
{
	UartPacket receivedPacket;

	while (1)
	{
		// 센서 큐에서 패킷 수신 (무한 대기)
		if(xQueueReceive(sensorQueue, &receivedPacket, portMAX_DELAY) == pdPASS)
		{
			uint8_t sensorType = receivedPacket.data[3];

			char str[100]; // Allocate memory for the string
			
			switch (sensorType){
				case REQ_SENSOR_TYPE_INDOOR_TEMP:
					snprintf(str, sizeof(str), "temp : %.2f", get_temp_info());
					//snprintf(str, sizeof(str), "TEMP");
					break;
				case REQ_SENSOR_TYPE_INDOOR_HUMIDITY:
					snprintf(str, sizeof(str), "humid : %.2f", get_humidity_info());
					break;
				case REQ_SENSOR_TYPE_ATMOSPHERIC_PRESSURE:
					snprintf(str, sizeof(str), "atmospheric pressure :%.2f", get_atmospheric_pressure_info());
					break;
				case REQ_SENSOR_TYPE_ALL:
					snprintf(str, sizeof(str), "temp: %.2f, humid : %.2f, atmospheric pressure : %.2f ", get_temp_info(), get_humidity_info(), get_atmospheric_pressure_info());
					break;
				default:
					vTaskDelay(pdMS_TO_TICKS(2000));
					snprintf(str, sizeof(str), "DATA ERROR");
					break;
			}
			// Print the result after the switch statement
			printf("%s \r\n", str);
			vTaskDelay(pdMS_TO_TICKS(100));
		}

		// Clear the sensor queue
		xQueueReset(sensorQueue);
	}
}

float get_humidity_info()
{
    float humidity = HTS221_H_ReadHumidity((uint16_t)HTS221_DEVICE_ID);
    return humidity;
}

float get_temp_info()
{
	float temp = HTS221_T_ReadTemp((uint16_t)HTS221_DEVICE_ID);
	return temp;
}

float get_atmospheric_pressure_info()
{
	return LPS22HB_P_ReadPressure(LPS22HB_I2C_ADDRESS);
}
