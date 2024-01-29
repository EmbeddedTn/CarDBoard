#include <ti/devices/msp432p4xx/inc/msp.h>
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <ti/grlib/grlib.h>
#include <stdio.h>
#include <stdint.h>

// file containing global variable with slb_image
#include "../include/slb.h"

/* Graphic library context */
Graphics_Context g_sContext;

// this should be received from the OSM api
uint8_t current_speed = 130;

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
        return "NaN";
    }
}

void draw_speed_limit(int speed_int) {
    int8_t* speed = speed_from_int(speed_int);
    Graphics_drawImage(&g_sContext, &slb_image, 0, 0);
    Graphics_drawStringCentered(&g_sContext, speed, 3, 64, 64, OPAQUE_TEXT);
}

// Select the page to draw to the screen
void draw_page(int8_t page_number) {
    switch (page_number) {
    case 0:
        draw_speed_limit(current_speed);
        Graphics_drawString(&g_sContext, "Speed Limit", AUTO_STRING_LENGTH, 5, 5, OPAQUE_TEXT);

        break;
    case 1:
        Graphics_clearDisplay(&g_sContext);
        Graphics_drawString(&g_sContext, "Vehicle Tilt", AUTO_STRING_LENGTH, 5, 5, OPAQUE_TEXT);

        break;
    case 2:
        Graphics_clearDisplay(&g_sContext);
        Graphics_drawString(&g_sContext, "Geolocation", AUTO_STRING_LENGTH, 5, 5, OPAQUE_TEXT);

        break;
    default:
        Graphics_clearDisplay(&g_sContext);
        Graphics_drawString(&g_sContext, "Err", AUTO_STRING_LENGTH, 11, 5, OPAQUE_TEXT);

        break;
    }

}

void change_page(int delta) {
    current_page_number = abs(current_page_number + delta) % PAGES;
    draw_page(current_page_number);
}
