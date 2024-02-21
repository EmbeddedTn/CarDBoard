#ifndef __DISPLAY_INIT_H__
#define __DISPLAY_INIT_H__

#include "../utils.h"

/*
 * Function: _graphicsInit
 * -------------------------
 *  Initialize the graphics context
 */
void _graphicsInit();

/*
 * Function: _displayButtonsInit
 * --> Deprecated
 * -------------------------
 *  Initialize the buttons
 */
void _displayButtonsInit();

/*
 * Function _adcInit
 * -------------------------
 *  Initialize the ADC
 */
void _adcInit();

/*
 * Function: _timerA1Init
 * -------------------------
 *  Initialize the timer A1, used for the display update
 *  and the sensor / ESP32 requests
 */
void _timerA1Init();

/*
 * Function: init_all
 * -------------------------
 *  Wrapper function that calls all the initialization functions
 */
void init_all();

#endif /* INCLUDE_INIT_H_ */
