#ifndef __UART_H__
#define __UART_H__

void sendString(char* str);

void requestPosition();
void requestSpeed();
void requestLimit();
void requestLat();
void requestLon();
void sendError();

typedef enum request{
    ADDRESS = '0',
    SPEED = '1',
    LIMIT = '2',
    LAT = '3',
    LON = '4',
    UNSET = -1
} request;

#endif // __UART_H__
