#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include "tilt.h"

//faster timer for updating tilting
void _fastTimerA2Init(){
    Timer_A_configureUpMode(TIMER_A2_BASE, &fastUpConfig);

    Interrupt_enableInterrupt(INT_TA2_0);
    Timer_A_startCounter(TIMER_A2_BASE, TIMER_A_UP_MODE);
}

void setup__tilt() {
    _fastTimerA2Init();
}

//volatile int8_t first = 0;

void interrupt_TA2_0__tilt()
{
    update_tilt();
    Timer_A_clearCaptureCompareInterrupt(TIMER_A2_BASE,
            TIMER_A_CAPTURECOMPARE_REGISTER_0);

}

