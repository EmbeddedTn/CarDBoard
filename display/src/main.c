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
    int i = 0;
    srand(time(0));
    while (1){
       //PCM_gotoLPM0();
       i++;
       if(i == 1000000) {
           i = 0;
           update_speed_limit(rand() % 150);
       } else if (i % 500000 == 0) {
           update_speed(rand() % 150);
       }
    }
}
