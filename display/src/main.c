#include <ti/devices/msp432p4xx/inc/msp.h>
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <stdlib.h>

// init functions
#include "../include/init.h"

// UI functions
#include "../include/pages.h"

int main(void)
{
    init_all();
    car_side_init();
    car_front_init();

    srand(time(0));
    while (1){
       PCM_gotoLPM0();
    }
}


// Example timer handler implementation to change the values of speed_limit and speed
// See init.h for timer specs
//
// -- Usage
// A timer can be implemented to query ESP and check if the parameters have changed.
// If so, call update_{parameter}() function to update the screen.
volatile int8_t first = 0;
void TA1_0_IRQHandler(void)
{
    update_speed_limit(rand() % 150);
    update_speed(rand() % 150);
    Timer_A_clearCaptureCompareInterrupt(TIMER_A1_BASE,
            TIMER_A_CAPTURECOMPARE_REGISTER_0);
}

void TA2_0_IRQHandler(void)
{
    update_tilt();
    Timer_A_clearCaptureCompareInterrupt(TIMER_A2_BASE,
            TIMER_A_CAPTURECOMPARE_REGISTER_0);

}
