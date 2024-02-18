#include <ti/devices/msp432p4xx/inc/msp.h>
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

#include "display/display.h"

#include "utils.h"
#include "mods.h"

int main(void) {
    int i = 0;
    for(; i < N_SETUPS; i++) {
        SETUPS[i]();
    }

    while(1) {
        PCM_gotoLPM0();
    }
}

void TA1_0_IRQHandler(void) {
    irq_dispatcher(INTERRUPTS_TA1_0, N_INTERRUPTS_TA1_0);
}

void TA2_0_IRQHandler(void) {
    irq_dispatcher(INTERRUPTS_TA2_0, N_INTERRUPTS_TA2_0);
}


// Example timer handler implementation to change the values of speed_limit and speed
// See init.h for timer specs
//
// -- Usage
// A timer can be implemented to query ESP and check if the parameters have changed.
// If so, call update_{parameter}() function to update the screen.





