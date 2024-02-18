#ifndef __TILT_H__
#define __TILT_H__

#include "../utils.h"
#include <stdint.h>
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

float changeG(uint16_t resultsBuffer);
void _fastTimerA2Init();

extern const Timer_A_UpModeConfig fastUpConfig;

void setup__tilt();
void interrupt_TA2_0__tilt();



#endif // __TILT_H__
