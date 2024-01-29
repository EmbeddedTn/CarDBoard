#include <ti/devices/msp432p4xx/inc/msp.h>
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <ti/grlib/grlib.h>
#include "LcdDriver/Crystalfontz128x128_ST7735.h"
#include "../LcdDriver/HAL_MSP_EXP432P401R_Crystalfontz128x128_ST7735.h"
#include "../include/HAL_I2C.h"
#include "../include/HAL_TMP006.h"
#include <stdio.h>
#include <stdint.h>

// init functions
#include "../include/init.h"

// file including the font WIP
#include "../include/font.h"

// file with pages functions
#include "../include/pages.h"

// Useful defines
#define SCREEN_MAXWIDTH 128


/*
 * Main function
 */
int main(void)
{
    _hwInit();
    _graphicsInit();

    // WIP
    // initFont();

    draw_page(0);
    while (1){
       if(!(P3IN & GPIO_PIN5)) {
           change_page(-1);
       } else if (!(P5IN & GPIO_PIN1)) {
           change_page(1);
       }

    }
}
