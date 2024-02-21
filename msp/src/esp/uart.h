#ifndef __UART_H__
#define __UART_H__

/*
 * Function: sendString
 *  Parameters: char* str -> string to send
 * -------------------------
 *  Sends a string through the UART
 */
void sendString(char *str);

/*
 * Function: requestPosition
 * -------------------------
 *  Sends a request to the ESP32 to get the position
 *  of the car
 */
void requestPosition();

/*
 * Function: requestSpeed
 * -------------------------
 *  Sends a request to the ESP32 to get the speed
 */
void requestSpeed();

/*
 * Function: requestLimit
 * -------------------------
 *  Sends a request to the ESP32 to get the speed limit
 */
void requestLimit();

/*
 * Function: requestLat
 * -------------------------
 *  Sends a request to the ESP32 to get the latitude
 */
void requestLat();

/*
 * Function: requestLon
 * -------------------------
 *  Sends a request to the ESP32 to get the longitude
 */
void requestLon();

/*
 * Function: sendError
 * -------------------------
 *  Sends an error message to the ESP32
 */
void sendError();

/*
 * Struct: request
 * -------------------------
 *  Enum to indicate the type of request to send to the ESP32
 */
typedef enum request {
  ADDRESS = '0',
  SPEED = '1',
  LIMIT = '2',
  LAT = '3',
  LON = '4',
  UNSET = -1
} request;

#endif // __UART_H__
