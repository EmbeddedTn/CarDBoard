#include <src/mods.h>
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
