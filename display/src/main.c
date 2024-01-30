#include <ti/devices/msp432p4xx/inc/msp.h>
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <stdio.h>
#include <stdint.h>

// init functions
#include "../include/init.h"

// file with pages functions
#include "../include/pages.h"

// Useful defines
#define SCREEN_MAXWIDTH 128


int main(void)
{
    init_all();

    draw_page(0);
    while (1){
       PCM_gotoLPM0();
    }
}
