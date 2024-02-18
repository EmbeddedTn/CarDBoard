/*
 * uart.h
 *
 *  Created on: 18 Feb 2024
 *      Author: lyreplus
 */

#ifndef INCLUDE_UART_H_
#define INCLUDE_UART_H_

void sendString(char* str);

enum request{
    ADDRESS = 0,
    SPEED = 1,
    LIMIT = 2,
    LAT = 3,
    LON = 4,
    UNSET = -1
};

#endif /* INCLUDE_UART_H_ */
