#include "tilt.h"
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

const Timer_A_UpModeConfig fastUpConfig = {
    TIMER_A_CLOCKSOURCE_ACLK,      // 32768 Hz
    TIMER_A_CLOCKSOURCE_DIVIDER_1, // 32768 / 2 = 16384 Hz
    TIMER_PERIOD, // every ~= 0.71 s the interrupt is registered
    TIMER_A_TAIE_INTERRUPT_DISABLE,     // Disable Timer interrupt
    TIMER_A_CCIE_CCR0_INTERRUPT_ENABLE, // Enable CCR0 interrupt
    TIMER_A_DO_CLEAR                    // Clear value
};

// faster timer for updating tilting
void _fastTimerA2Init() {
  Timer_A_configureUpMode(TIMER_A2_BASE, &fastUpConfig);

  Interrupt_enableInterrupt(INT_TA2_0);
  Timer_A_startCounter(TIMER_A2_BASE, TIMER_A_UP_MODE);
}

void setup__tilt() { _fastTimerA2Init(); }

// volatile int8_t first = 0;

void interrupt_TA2_0__tilt() {
  update_tilt();
  Timer_A_clearCaptureCompareInterrupt(TIMER_A2_BASE,
                                       TIMER_A_CAPTURECOMPARE_REGISTER_0);
}
