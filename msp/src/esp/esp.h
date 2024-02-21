#ifndef __ESP_H__
#define __ESP_H__

#include "uart.h"
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

#define MAX_SIZE_READ 128
#define MAX_SIZE_COORDINATES 11

/*
 * Function: update_value
 * Parameters: request req -> enum indicating type of request to send to the
 * ESP32
 * -------------------------
 *  updates the value of the specific type returned from the ESP32
 */
void update_value(request req);

/*
 * Function: interrupt_EUSCIA2__esp
 * -------------------------
 *  Interrupt to handle the communication with the ESP32
 */
void interrupt_EUSCIA2__esp();

/*
 * Function: setup__esp
 * -------------------------
 *  Setup the ESP32 communication
 *  Initializes the UART and the GPIO
 */
void setup__esp();

extern uint8_t can_request;

#endif //__ESP_H__
