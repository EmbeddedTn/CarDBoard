#include "display.h"

#include <ti/devices/msp432p4xx/inc/msp.h>
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <time.h>
#include <stdlib.h>
#include "pages.h"
#include "init.h"

void setup__display(){
    srand(time(0));
    init_all();

//    draw_page(0);

    car_side_init();
    car_front_init();
}

void interrupt_TA1_0__display(void){
    update_speed_limit(rand() % 150);
    update_speed(rand() % 150);
    Timer_A_clearCaptureCompareInterrupt(TIMER_A1_BASE,
            TIMER_A_CAPTURECOMPARE_REGISTER_0);
}
