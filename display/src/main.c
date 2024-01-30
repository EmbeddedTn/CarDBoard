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
    while (1){
       PCM_gotoLPM0();
    }
}
