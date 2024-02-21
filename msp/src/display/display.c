#include "display.h"

#include "../esp/esp.h"
#include "../esp/uart.h"
#include "init.h"
#include "pages.h"
#include <stdlib.h>
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <ti/devices/msp432p4xx/inc/msp.h>
#include <time.h>

extern volatile uint8_t current_page_number;

void setup__display() {
  srand(time(0));
  init_all();

  car_side_init();
  car_front_init();
}

volatile uint8_t rcount = 0;
uint8_t abort_count = 20;

void interrupt_TA1_0__display(void) { // slow interrupt
  if (!can_request) {
    if (--abort_count == 0) {
      can_request = 1;
      abort_count = 20;
    }
  } else {
    switch (current_page_number) {
    case 0:
      if (rcount % 6 == 0)
        requestLimit();
      break;
    case 1:
      if (rcount % 6 == 0)
        requestLimit();
      else
        requestSpeed();
      break;
    case 3:
      if (rcount % 40 == 0)
        requestPosition();
      else if (rcount % 2 == 0)
        requestLon();
      else
        requestLat();
    }
    rcount++;
    if (rcount >= 120)
      rcount = 0;
  }

  Timer_A_clearCaptureCompareInterrupt(TIMER_A1_BASE,
                                       TIMER_A_CAPTURECOMPARE_REGISTER_0);
}
