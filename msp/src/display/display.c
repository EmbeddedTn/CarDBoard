#include "display.h"

#include <ti/devices/msp432p4xx/inc/msp.h>
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <time.h>
#include <stdlib.h>
#include "pages.h"
#include "init.h"
#include "../esp/uart.h"

extern volatile uint8_t current_page_number;

void setup__display(){
    srand(time(0));
    init_all();

//    draw_page(0);

    car_side_init();
    car_front_init();
}

void interrupt_TA1_0__display(void){ //slow interrupt
    if(current_page_number == 0 || current_page_number == 1) {
        requestSpeed();
        requestLimit();
    }
    if(current_page_number == 3){
        requestPosition();
        requestLat();
        requestLon();
    }
    Timer_A_clearCaptureCompareInterrupt(TIMER_A1_BASE,
            TIMER_A_CAPTURECOMPARE_REGISTER_0);
}
