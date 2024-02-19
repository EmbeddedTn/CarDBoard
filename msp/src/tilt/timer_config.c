#include "tilt.h"

#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

const Timer_A_UpModeConfig fastUpConfig =
{
        TIMER_A_CLOCKSOURCE_ACLK,               // 32768 Hz
        TIMER_A_CLOCKSOURCE_DIVIDER_1,          // 32768 / 2 = 16384 Hz
        TIMER_PERIOD,                           // every ~= 0.71 s the interrupt is registered
        TIMER_A_TAIE_INTERRUPT_DISABLE,         // Disable Timer interrupt
        TIMER_A_CCIE_CCR0_INTERRUPT_ENABLE ,    // Enable CCR0 interrupt
        TIMER_A_DO_CLEAR                        // Clear value
};
