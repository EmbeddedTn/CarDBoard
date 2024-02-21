#include "uart.h"
#include "esp.h"

#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

void requestPosition() {
  can_request = 0;
  UART_transmitData(EUSCI_A2_BASE, '0');
}

void requestSpeed() {
  can_request = 0;
  UART_transmitData(EUSCI_A2_BASE, '1');
}

void requestLimit() {
  can_request = 0;
  UART_transmitData(EUSCI_A2_BASE, '2');
}

void requestLat() {
  can_request = 0;
  UART_transmitData(EUSCI_A2_BASE, '3');
}

void requestLon() {
  can_request = 0;
  UART_transmitData(EUSCI_A2_BASE, '4');
}
//
// void sendError(){
//    char sendError[4] = "ERR";
//    sendString(sendError);
//}
