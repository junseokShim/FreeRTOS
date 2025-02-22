/*
 * protocol_parser_sensor_info.h
 *
 *  Created on: Feb 15, 2025
 *      Author: junseokshim
 */

#include "stm32l475e_iot01_hsensor.h"
#include "stm32l475e_iot01.h"
#include "common.h"

#ifndef MODULE_SENSORS_H_
#define MODULE_SENSORS_H_

#define HTS221_DEVICE_ID		0x5F<<1

extern TSENSOR_InitTypeDef gTemp;
static const int LPS22HB_WHO_AL_I_VAL = 0xB1;

typedef enum {
    REQ_SENSOR_TYPE_INDOOR_TEMP = 0,
    REQ_SENSOR_TYPE_INDOOR_HUMIDITY = 1,
    REQ_SENSOR_TYPE_ATMOSPHERIC_PRESSURE = 2,
    REQ_SENSOR_TYPE_ALL = 255
} SensorType;

void initSensorBSP();
float get_humidity_info();
float get_temp_info();
float get_atmospheric_pressure_info();

void vTaskSensorHandler(void *pvParameters);

#endif /* MODULE_SENSORS_H_ */
