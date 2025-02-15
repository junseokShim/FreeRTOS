/*
 * common.h
 *
 *  Created on: Feb 15, 2025
 *      Author: junseokshim
 */

#ifndef INC_COMMON_H_
#define INC_COMMON_H_

#define RX_BUFFER_SIZE 8

#include <stdint.h>
#include <stddef.h>

typedef struct {
    uint8_t data[RX_BUFFER_SIZE];
    size_t length;
} UartPacket;

#endif /* INC_COMMON_H_ */
