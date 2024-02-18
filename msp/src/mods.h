#ifndef __MODS_H__
#define __MODS_H__

#include "display/display.h"
#include "utils.h"

#define N_SETUPS 2
void (*SETUPS[N_SETUPS])(void) = {setup__hw, setup__display};

#define N_INTERRUPTS_TA1_0 1
void (*INTERRUPTS_TA1_0[N_INTERRUPTS_TA1_0])(void) = {interrupt_TA1_0__display};

#endif
