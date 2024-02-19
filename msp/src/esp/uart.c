#include "uart.h"
#include "esp.h"

#include <ti/devices/msp432p4xx/driverlib/driverlib.h>


void requestPosition(){
    if(!can_request[0]) return;
    can_request[0] = 0;
    UART_transmitData(EUSCI_A2_BASE, '0');
}

void requestSpeed(){
    if(!can_request[1]) return;
    can_request[1] = 0;
    UART_transmitData(EUSCI_A2_BASE, '1');
}

void requestLimit(){
    if(!can_request[2]) return;
    can_request[2] = 0;
    UART_transmitData(EUSCI_A2_BASE, '2');
}

void requestLat(){
    if(!can_request[3]) return;
    can_request[3] = 0;
    UART_transmitData(EUSCI_A2_BASE, '3');
}

void requestLon(){
    if(!can_request[4]) return;
    can_request[4] = 0;
    UART_transmitData(EUSCI_A2_BASE, '4');
}
//
//void sendError(){
//    char sendError[4] = "ERR";
//    sendString(sendError);
//}
