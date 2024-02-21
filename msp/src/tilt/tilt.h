#ifndef __TILT_H__
#define __TILT_H__

#include "../utils.h"
#include <stdint.h>
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

/*
 * Function: changeG
 * -------------------------
 * Calculates corresponding g value from the ADC result
 */
float changeG(uint16_t resultsBuffer);

/*
 * Function: _fastTimerA2Init
 * -------------------------
 * Initializes the timer A2, used for the tilt sensor
 */
void _fastTimerA2Init();

extern const Timer_A_UpModeConfig fastUpConfig;

/*
 * Function: setup__tilt
 * -------------------------
 * Setup the tilt sensor
 */
void setup__tilt();

/*
 * Function: interrupt_TA2_0__tilt
 * -------------------------
 * Interrupt to handle the tilt sensor
 */
void interrupt_TA2_0__tilt();

#endif // __TILT_H__
