#include <ti/devices/msp432p4xx/inc/msp.h>
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <stdio.h>
#include <stdint.h>

// init functions
#include "../include/init.h"

// UI functions
#include "../include/pages.h"

int main(void)
{
    init_all();

    draw_page(0);
    srand(time(0));
    while (1){
       PCM_gotoLPM0();
    }
}

void TA1_0_IRQHandler(void)
{
    update_speed_limit(rand() % 150);
    update_speed(rand() % 150);
    Timer_A_clearCaptureCompareInterrupt(TIMER_A1_BASE,
            TIMER_A_CAPTURECOMPARE_REGISTER_0);
}
