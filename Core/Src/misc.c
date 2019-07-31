/*
 * misc.c
 *
 *  Created on: 30 de jul de 2019
 *      Author: rinaldo
 */

#include "misc.h"

extern SPI_HandleTypeDef hspi1;

uint8_t xpt2046(uint8_t data)
{
	uint8_t	ret;
	HAL_SPI_TransmitReceive(&hspi1, &data, &ret, 1, 10);
	return ret;
}
