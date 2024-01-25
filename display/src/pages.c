#include <ti/devices/msp432p4xx/inc/msp.h>
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <ti/grlib/grlib.h>
#include <stdio.h>
#include <stdint.h>

// file containing global variable with slb_image
#include "../include/slb.h"

/* Graphic library context */
Graphics_Context g_sContext;


uint8_t current_speed = 0;

#define PAGES 3
int current_page_number = 0;

int8_t* speed_from_int(int speed) {
    switch (speed) {
    case 30:
        return "30";
    case 40:
        return "40";
    case 50:
        return "50";
    case 60:
        return "60";
    case 70:
        return "70";
    case 90:
        return "90";
    case 110:
        return "110";
    case 130:
        return "130";
    default:
        return "No Limit";
    }
}

void draw_speed_limit(int speed_int) {
    int8_t* speed = speed_from_int(speed_int);
    Graphics_drawImage(&g_sContext, &slb_image, 0, 0);
    Graphics_drawStringCentered(&g_sContext, speed, 3, 64, 64, OPAQUE_TEXT);
}

// Select the page to draw to the screen
void draw_page(uint8_t page_number) {
    //GrContextForegroundSet(&g_sContext, ClrBlack);
    switch (page_number) {
    case 0:
        draw_speed_limit(current_speed);
        break;
    default:
        Graphics_drawImage(&g_sContext, &slb_image, 0, 0);
        break;
    }

}

void change_page(int delta) {
    current_page_number = (current_page_number + delta) % PAGES;
    draw_page(current_page_number);
}
