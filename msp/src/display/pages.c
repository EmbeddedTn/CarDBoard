#include "pages.h"
#include "../esp/esp.h"

#include <ti/devices/msp432p4xx/inc/msp.h>
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <ti/grlib/grlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h> //for atoi

#include "images.h"
#include "car_front.h"
#include "car_side.h"
#include "../tilt/tilt.h"


#define SPEED_FONT g_sFontCmss30b
#define TITLE_FONT g_sFontCmss12b
#define DEFAULT_FONT g_sFontCmss12
#define PAGES 4

// Global variables
static uint16_t joystickBuffer[2];
Graphics_Context g_sContext;

Graphics_Image car_side_array[19];
Graphics_Image car_front_array[19];

void car_side_init(){
        car_side_array[0] = car_side_output__45;
        car_side_array[1] = car_side_output__40;
        car_side_array[2] = car_side_output__35;
        car_side_array[3] = car_side_output__30;
        car_side_array[4] = car_side_output__25;
        car_side_array[5] = car_side_output__20;
        car_side_array[6] = car_side_output__15;
        car_side_array[7] = car_side_output__10;
        car_side_array[8] = car_side_output__5;
        car_side_array[9] = car_side;
        car_side_array[10] = car_side_output_5;
        car_side_array[11] = car_side_output_10;
        car_side_array[12] = car_side_output_15;
        car_side_array[13] = car_side_output_20;
        car_side_array[14] = car_side_output_25;
        car_side_array[15] = car_side_output_30;
        car_side_array[16] = car_side_output_35;
        car_side_array[17] = car_side_output_40;
        car_side_array[18] = car_side_output_45;
}

void car_front_init(){
        car_front_array[0] = car_front_output__45;
        car_front_array[1] = car_front_output__40;
        car_front_array[2] = car_front_output__35;
        car_front_array[3] = car_front_output__30;
        car_front_array[4] = car_front_output__25;
        car_front_array[5] = car_front_output__20;
        car_front_array[6] = car_front_output__15;
        car_front_array[7] = car_front_output__10;
        car_front_array[8] = car_front_output__5;
        car_front_array[9] = car_front;
        car_front_array[10] = car_front_output_5;
        car_front_array[11] = car_front_output_10;
        car_front_array[12] = car_front_output_15;
        car_front_array[13] = car_front_output_20;
        car_front_array[14] = car_front_output_25;
        car_front_array[15] = car_front_output_30;
        car_front_array[16] = car_front_output_35;
        car_front_array[17] = car_front_output_40;
        car_front_array[18] = car_front_output_45;
}

volatile uint8_t current_page_number = 0;
uint8_t* current_speed = "012";
uint8_t* current_speed_limit = "69";

int numeric_current_speed = 0;
int numeric_current_speed_limit = 0;

static uint16_t resultsBuffer[2];

uint8_t* current_lon = "?"; //length: 8
uint8_t* current_lat = "?"; //length: 8

const uint8_t default_location_name[128] = "Finding Location";
uint8_t* current_location_name = "";

// Moving snprintf to RAM to improve performance
#pragma CODE_SECTION(snprintf, ".ram_functions")
int snprintf(char* str, size_t size, const char* format, ...){
    int r;
    va_list args;
    va_start(args, format);
    r = vsnprintf(str, size, format, args);
    va_end(args);
    return r;
}


void draw_speed_limit() {
    Graphics_clearDisplay(&g_sContext);

    Graphics_drawImage(&g_sContext, &slb_image, 0, 0);
    Graphics_setFont(&g_sContext, &SPEED_FONT);
    Graphics_drawStringCentered(&g_sContext, current_speed_limit, AUTO_STRING_LENGTH, 64, 64, OPAQUE_TEXT);
    Graphics_setFont(&g_sContext, &DEFAULT_FONT);
    draw_title("Speed Limit");
}

void draw_speed() {
    int COLOR;

    // Checking if over speed limit
    if (numeric_current_speed > numeric_current_speed_limit) {
        COLOR = GRAPHICS_COLOR_RED;
    } else if (abs(numeric_current_speed - numeric_current_speed_limit) < 5) {
        COLOR = GRAPHICS_COLOR_ORANGE;
    } else {
        COLOR = GRAPHICS_COLOR_GREEN;
    }

    Graphics_clearDisplay(&g_sContext);
    draw_title("Speed");

    Graphics_setFont(&g_sContext, &SPEED_FONT);
    Graphics_drawStringCentered(&g_sContext, (int8_t*)current_speed, AUTO_STRING_LENGTH, 50, 64, OPAQUE_TEXT);

    Graphics_setForegroundColor(&g_sContext, COLOR);
    Graphics_setBackgroundColor(&g_sContext, COLOR);
    Graphics_drawStringCentered(&g_sContext, "          ", AUTO_STRING_LENGTH, 64, 112, OPAQUE_TEXT);
    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_BLACK);
    Graphics_setBackgroundColor(&g_sContext, GRAPHICS_COLOR_WHITE);

    Graphics_setFont(&g_sContext, &DEFAULT_FONT);
    Graphics_drawString(&g_sContext, "Km/h", AUTO_STRING_LENGTH, 80, 64, OPAQUE_TEXT);
}

void draw_geolocation() {
    Graphics_clearDisplay(&g_sContext);
    draw_title("Geolocation");

    Graphics_drawString(&g_sContext, "Lon: ", AUTO_STRING_LENGTH, 10, 35, OPAQUE_TEXT);
    Graphics_drawString(&g_sContext, (int8_t*)current_lon, AUTO_STRING_LENGTH, 40, 35, OPAQUE_TEXT);

    Graphics_drawString(&g_sContext, "Lat: ", AUTO_STRING_LENGTH, 10, 55, OPAQUE_TEXT);
    Graphics_drawString(&g_sContext, (int8_t*)current_lat, AUTO_STRING_LENGTH, 40, 55, OPAQUE_TEXT);

    Graphics_drawString(&g_sContext, "Location name:", AUTO_STRING_LENGTH, 10, 85, OPAQUE_TEXT);
    Graphics_drawString(&g_sContext, (int8_t *) current_location_name, AUTO_STRING_LENGTH, 20, 105, OPAQUE_TEXT);
}

void draw_tilt() {
    Graphics_clearDisplay(&g_sContext);
    draw_title("Vehicle Tilt");
    Graphics_drawImage(&g_sContext, &car_side, 80, 35);
    Graphics_drawImage(&g_sContext, &car_front, 10, 35);
    int8_t x_accelerometer[8];
    int8_t y_accelerometer[8];

    sprintf((char*) x_accelerometer, " %1.2f ", changeG(resultsBuffer[0]));
    sprintf((char*) y_accelerometer, " %1.2f ", changeG(resultsBuffer[1]));
    Graphics_drawString(&g_sContext, x_accelerometer, AUTO_STRING_LENGTH, 80, 70, OPAQUE_TEXT);
    Graphics_drawString(&g_sContext, y_accelerometer, AUTO_STRING_LENGTH, 10, 70, OPAQUE_TEXT);
    Graphics_drawLineV(&g_sContext, 64, 25, 128);
    Graphics_drawLineH(&g_sContext, 0, 128, 25);
}

void draw_title(int8_t* title) {
    Graphics_setFont(&g_sContext, &TITLE_FONT);
    //Graphics_drawImage(&g_sContext, &front_car_image, 80, 35);
    Graphics_drawString(&g_sContext, title, AUTO_STRING_LENGTH, 5, 5, OPAQUE_TEXT);
    Graphics_setFont(&g_sContext, &DEFAULT_FONT);
}

// page to draw on the screen
void draw_page() {
    switch (current_page_number) {
    case 0:
        draw_speed_limit();
        break;
    case 1:
        draw_speed();
        break;
    case 2:
        draw_tilt();
        break;
    case 3:
        draw_geolocation();
        break;
    default:
        draw_speed_limit();
        current_page_number = 0;
        break;
    }
}

// function called when buttons S1 or S2 are pressed
void change_page(int8_t delta) {
    current_page_number = (current_page_number + delta + PAGES) % PAGES;
    rcount = 0;
    draw_page();
}

// Function to call on speed_limit change
void update_speed_limit(uint8_t* speed_limit) {
    current_speed_limit = speed_limit;
    numeric_current_speed_limit = atoi(current_speed_limit);
    if (current_page_number == 0) {

        Graphics_setFont(&g_sContext, &SPEED_FONT);
        Graphics_drawStringCentered(&g_sContext, "    ", AUTO_STRING_LENGTH, 64, 64, OPAQUE_TEXT);
        Graphics_drawStringCentered(&g_sContext, (int8_t*)current_speed_limit, AUTO_STRING_LENGTH, 64, 64, OPAQUE_TEXT);
        Graphics_setFont(&g_sContext, &DEFAULT_FONT);
    }
}

// Function to call on vechicle speed change
void update_speed(uint8_t* nSpeed) {
    current_speed = nSpeed;
    numeric_current_speed = atoi(nSpeed);

    if (current_page_number == 1) {
        int COLOR;

        // Checking if over speed limit
        if (numeric_current_speed > numeric_current_speed_limit) {
            COLOR = GRAPHICS_COLOR_RED;
        } else if (abs(numeric_current_speed - numeric_current_speed_limit) < 5) {
            COLOR = GRAPHICS_COLOR_ORANGE;
        } else {
            COLOR = GRAPHICS_COLOR_GREEN;
        }

        Graphics_setFont(&g_sContext, &SPEED_FONT);
        Graphics_drawStringCentered(&g_sContext, "    ", AUTO_STRING_LENGTH, 50, 64, OPAQUE_TEXT);
        Graphics_drawStringCentered(&g_sContext, (int8_t*) current_speed, AUTO_STRING_LENGTH, 50, 64, OPAQUE_TEXT);

        Graphics_setForegroundColor(&g_sContext, COLOR);
        Graphics_setBackgroundColor(&g_sContext, COLOR);
        Graphics_drawStringCentered(&g_sContext, "          ", AUTO_STRING_LENGTH, 64, 112, OPAQUE_TEXT);
        Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_BLACK);
        Graphics_setBackgroundColor(&g_sContext, GRAPHICS_COLOR_WHITE);

        Graphics_setFont(&g_sContext, &DEFAULT_FONT);
    }
}

// Function to call on location change
void update_address(uint8_t* location_name){
    current_location_name = location_name;
    Graphics_drawString(&g_sContext, (int8_t*)current_location_name, AUTO_STRING_LENGTH, 20, 105, OPAQUE_TEXT);
}

void update_lat(uint8_t* lat){
    current_lat = lat;
    Graphics_drawString(&g_sContext, (int8_t*)current_lat, AUTO_STRING_LENGTH, 40, 55, OPAQUE_TEXT);
}

void update_lon(uint8_t* lon){
    current_lon = lon;
    Graphics_drawString(&g_sContext, (int8_t*)current_lon, AUTO_STRING_LENGTH, 40, 35, OPAQUE_TEXT);
}

void update_car_side(float y_axis){
    int interval_index;
    if(y_axis>=-0.15 && y_axis <= 0.15){
        interval_index = 9;
    }else{
        interval_index = (y_axis + 0.85) / 0.094;
    }
    Graphics_drawImage(&g_sContext, &car_side_array[interval_index], 80, 35);
}

void update_car_front(float x_axis){
    int interval_index;
        if(x_axis>=-0.15 && x_axis <= 0.15){
            interval_index = 9;
        }else{
            interval_index = (x_axis + 0.85) / 0.094;
        }
        Graphics_drawImage(&g_sContext, &car_front_array[interval_index], 10, 35);
}

void update_tilt(){
    if (current_page_number == 2){
        int8_t x_accelerometer[8];
        int8_t y_accelerometer[8];
        float x_res = changeG(resultsBuffer[0]);
        float y_res = changeG(resultsBuffer[1]);

        sprintf((char*) x_accelerometer, " %1.2f ", x_res);
        sprintf((char*) y_accelerometer, " %1.2f ", y_res);
        Graphics_drawString(&g_sContext, x_accelerometer, AUTO_STRING_LENGTH, 10, 70, OPAQUE_TEXT);
        Graphics_drawString(&g_sContext, y_accelerometer, AUTO_STRING_LENGTH, 80, 70, OPAQUE_TEXT);

        update_car_side(y_res);
        update_car_front(x_res);

    }
}



bool in_idle_state(int x) {
    return ((x>7000) && (x<9000));
}

// Joystick and accelerometer interrupt handler
void ADC14_IRQHandler(void) {
    uint64_t status;
    status = ADC14_getEnabledInterruptStatus();
    ADC14_clearInterruptFlag(status);

    //Joystick reading finished
    if(status & ADC_INT1){ //Conversion is over
        joystickBuffer[0] = ADC14_getResult(ADC_MEM0);
        joystickBuffer[1] = ADC14_getResult(ADC_MEM1);

        // change page by checking x axis joystick value
        if(!in_idle_state(joystickBuffer[0])){
            if(joystickBuffer[0] > 15000){
                change_page(1);
            } else if(joystickBuffer[0] < 1000){
                change_page(-1);
            }
        }
    }

    //Accelerometer
    /* This interrupt is fired whenever a conversion is completed and placed in
     * ADC_MEM2. This signals the end of conversion and the results array is
     * grabbed and placed in resultsBuffer */

    /* Accelerometer reading finished (ADC_MEM2-3-4 conversion completed) */
    if (status & ADC_INT2)
    {
        /* Store ADC14 conversion results */
        resultsBuffer[0] = ADC14_getResult(ADC_MEM2);
        resultsBuffer[1] = ADC14_getResult(ADC_MEM3);
        //printf("X-%d, Y-%d, Z-%d\n", resultsBuffer[0],resultsBuffer[1],resultsBuffer[2]);
    }
}

// Button S1 interrupt handler
void PORT5_IRQHandler(){
//    uint_fast16_t status = GPIO_getEnabledInterruptStatus(GPIO_PORT_P5);
//    GPIO_clearInterruptFlag(GPIO_PORT_P5,status);
//    if (status & GPIO_PIN1){
//        reproduce_song();
//    }
}

// Button S2 interrupt handler
void PORT3_IRQHandler(){
//    uint_fast16_t status = GPIO_getEnabledInterruptStatus(GPIO_PORT_P3);
//    GPIO_clearInterruptFlag(GPIO_PORT_P3,status);
//    if (status & GPIO_PIN5){
//        play_pause();
//    }
}





