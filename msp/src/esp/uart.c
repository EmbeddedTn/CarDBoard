#include "uart.h"

#include <ti/devices/msp432p4xx/driverlib/driverlib.h>


void sendString(char* str) {
    while(*str != '\0') {
        UART_transmitData(EUSCI_A2_BASE, *str);
        str++;
    }
}

void requestPosition(){
    char sendPosition[2] = "0";
    sendString(sendPosition);
}

void requestSpeed(){
    char sendSpeed[2] = "1";
    sendString(sendSpeed);
}

void requestLimit(){
    char sendLimit[2] = "2";
    sendString(sendLimit);
}

void requestLat(){
    char sendLat[2] = "3";
    sendString(sendLat);
}

void requestLon(){
    char sendLon[2] = "4";
    sendString(sendLon);
}

void sendError(){
    char sendError[4] = "ERR";
    sendString(sendError);
}
