#ifndef __MODS_H__
#define __MODS_H__

#include "display/display.h"
#include "tilt/tilt.h"
#include "esp/esp.h"

#include "utils.h"

#define N_SETUPS 4
void (*SETUPS[N_SETUPS])(void) = {
    setup__hw,
    setup__display,
    setup__tilt,
    setup__esp,
};

#define N_INTERRUPTS_TA1_0 1
void (*INTERRUPTS_TA1_0[N_INTERRUPTS_TA1_0])(void) = {
    interrupt_TA1_0__display,
};

#define N_INTERRUPTS_TA2_0 1
void (*INTERRUPTS_TA2_0[N_INTERRUPTS_TA2_0])(void) = {
    interrupt_TA2_0__tilt,
};

#define N_INTERRUPTS_EUSCIA2 1
void (*INTERRUPTS_EUSCIA2[N_INTERRUPTS_EUSCIA2])(void) = {
    interrupt_EUSCIA2__esp,
};



#endif
