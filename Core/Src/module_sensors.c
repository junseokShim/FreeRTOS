/*
 * protocol_parser_sensor_info.h
 *
 *  Created on: Feb 15, 2025
 *      Author: junseokshim
 */
#include "module_sensors.h"

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

void seperateRxPacket(UartPacket packet)
{
	uint8_t length = packet.data[1];
	uint8_t reqType = packet.data[2];
	uint8_t sensorType = packet.data[3];

	char str[100]; // Allocate memory for the string
	switch (sensorType){
		case REQ_SENSOR_TYPE_INDOOR_TEMP:
			snprintf(str, sizeof(str), "temp : %.2f \r\n", get_temp_info());
			/*
			C 언어에서는 문자열 리터럴("temp : ")과 숫자형(double)을 직접 더하는 연산은 지원하지 않습니다.
			문자열과 숫자를 결합하여 출력하려면 sprintf 또는 snprintf와 같은 함수를 사용해서 포맷팅된 문자열을 만들어야 합니다.
			*/
			break;
		case REQ_SENSOR_TYPE_INDOOR_HUMIDITY:
			snprintf(str, sizeof(str), "humid : %.2f \r\n", get_humidity_info());
			break;
		case REQ_SENSOR_TYPE_ATMOSPHERIC_PRESSURE:
			snprintf(str, sizeof(str), "atmospheric pressure :%.2f \r\n", get_atmospheric_pressure_info());
			break;
		case REQ_SENSOR_TYPE_ALL:
			snprintf(str, sizeof(str), "temp: %.2f \r\n humid : %.2f \r\n atmospheric pressure : %.2f \r\n", get_temp_info(), get_humidity_info(), get_atmospheric_pressure_info());
			break;
		default:
			snprintf(str, sizeof(str), "DATA ERROR");
			break;
	}
	// Print the result after the switch statement
	printf("%s", str);
	// No need to free str as it is allocated on the stack

}

float get_humidity_info()
{
	return HTS221_H_ReadHumidity((uint16_t)HTS221_DEVICE_ID);
}

float get_temp_info()
{
	float temp = HTS221_T_ReadTemp((uint16_t)HTS221_DEVICE_ID);
	if (temp == -1) // Assuming -1 indicates an error
	{
		printf("Error reading temperature\n");
		return 0.0; // Return a default value or handle the error as needed
	}
	return temp;
}

float get_atmospheric_pressure_info()
{
	return LPS22HB_P_ReadPressure(LPS22HB_I2C_ADDRESS);
}
