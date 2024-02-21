#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <ti/devices/msp432p4xx/inc/msp.h>

#include "display/display.h"

#include "mods.h"
#include "utils.h"

int main(void) {
  int i = 0;
  for (; i < N_SETUPS; i++) {
    SETUPS[i]();
  }

  while (1) {
    PCM_gotoLPM0();
  }
}

void TA1_0_IRQHandler(void) {
  irq_dispatcher(INTERRUPTS_TA1_0, N_INTERRUPTS_TA1_0);
}

void TA2_0_IRQHandler(void) {
  irq_dispatcher(INTERRUPTS_TA2_0, N_INTERRUPTS_TA2_0);
}

void EUSCIA2_IRQHandler(void) {
  irq_dispatcher(INTERRUPTS_EUSCIA2, N_INTERRUPTS_TA2_0);
}
