#include "utils.h"

#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <ti/devices/msp432p4xx/inc/msp.h>

void setup__hw() {
  /* Halting WDT and disabling master interrupts */
  WDT_A_holdTimer();
  Interrupt_disableMaster();

  /* Set the core voltage level to VCORE1 */
  PCM_setCoreVoltageLevel(PCM_VCORE1);

  /* Set 2 flash wait states for Flash bank 0 and 1*/
  FlashCtl_setWaitState(FLASH_BANK0, 2);
  FlashCtl_setWaitState(FLASH_BANK1, 2);

  /* Initializes Clock System */
  CS_setDCOCenteredFrequency(CS_DCO_FREQUENCY_48);
  CS_initClockSignal(CS_MCLK, CS_DCOCLK_SELECT, CS_CLOCK_DIVIDER_1);
  CS_initClockSignal(CS_HSMCLK, CS_DCOCLK_SELECT, CS_CLOCK_DIVIDER_1);
  CS_initClockSignal(CS_SMCLK, CS_DCOCLK_SELECT, CS_CLOCK_DIVIDER_1);
  CS_initClockSignal(CS_ACLK, CS_REFOCLK_SELECT, CS_CLOCK_DIVIDER_1);
}

void irq_dispatcher(void (*handlers[])(), uint8_t handler_len) {
  int i = 0;
  for (; i < handler_len; i++) {
    handlers[i]();
  }
}
