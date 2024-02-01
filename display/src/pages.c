#include <ti/devices/msp432p4xx/inc/msp.h>
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <ti/grlib/grlib.h>
#include <stdio.h>
#include <stdint.h>

// file initializing the speed limit background image
#include "../include/slb.h"

// #include "../include/song.h"

#define SPEED_FONT g_sFontCmss30b
#define TITLE_FONT g_sFontCmss12b
#define DEFAULT_FONT g_sFontCmss12
#define PAGES 4

// Global variables
static uint16_t joystickBuffer[2];
Graphics_Context g_sContext;

uint8_t current_page_number = 0;
int16_t current_speed_limit = 69;
int16_t current_speed = 12;

float current_lon = 46.06705235237631;
float current_lat = 11.149869220425288;

int8_t* current_location_name = "Povo, Trento";

// function signatures
void draw_title(int8_t*);


void draw_speed_limit() {
    int8_t speed_limit[3];
    sprintf((char*)speed_limit, "%hd", current_speed_limit);

    Graphics_clearDisplay(&g_sContext);

    Graphics_drawImage(&g_sContext, &slb_image, 0, 0);
    Graphics_setFont(&g_sContext, &SPEED_FONT);
    Graphics_drawStringCentered(&g_sContext, speed_limit, AUTO_STRING_LENGTH, 64, 64, OPAQUE_TEXT);
    Graphics_setFont(&g_sContext, &DEFAULT_FONT);
    draw_title("Speed Limit");
}

void draw_speed() {
    int8_t speed[3];
    sprintf((char*)speed, "%hd", current_speed);
    int COLOR;

    // Checking if over speed limit
    if (current_speed > current_speed_limit) {
        COLOR = GRAPHICS_COLOR_RED;
    } else if (abs(current_speed - current_speed_limit) < 5) {
        COLOR = GRAPHICS_COLOR_ORANGE;
    } else {
        COLOR = GRAPHICS_COLOR_GREEN;
    }

    Graphics_clearDisplay(&g_sContext);
    draw_title("Speed");

    Graphics_setFont(&g_sContext, &SPEED_FONT);
    Graphics_drawStringCentered(&g_sContext, speed, AUTO_STRING_LENGTH, 50, 64, OPAQUE_TEXT);

    Graphics_setForegroundColor(&g_sContext, COLOR);
    Graphics_setBackgroundColor(&g_sContext, COLOR);
    Graphics_drawStringCentered(&g_sContext, "          ", AUTO_STRING_LENGTH, 64, 112, OPAQUE_TEXT);
    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_BLACK);
    Graphics_setBackgroundColor(&g_sContext, GRAPHICS_COLOR_WHITE);

    Graphics_setFont(&g_sContext, &DEFAULT_FONT);
    Graphics_drawString(&g_sContext, "Km/h", AUTO_STRING_LENGTH, 80, 64, OPAQUE_TEXT);
}

void draw_geolocation() {
    int8_t latitude[10];
    int8_t longitude[10];
    sprintf((char*)latitude, "%f", current_lat);
    sprintf((char*)longitude, "%f", current_lon);

    Graphics_clearDisplay(&g_sContext);
    draw_title("Geolocation");

    Graphics_drawString(&g_sContext, "Lon: ", AUTO_STRING_LENGTH, 10, 35, OPAQUE_TEXT);
    Graphics_drawString(&g_sContext, longitude, AUTO_STRING_LENGTH, 40, 35, OPAQUE_TEXT);

    Graphics_drawString(&g_sContext, "Lat: ", AUTO_STRING_LENGTH, 10, 55, OPAQUE_TEXT);
    Graphics_drawString(&g_sContext, latitude, AUTO_STRING_LENGTH, 40, 55, OPAQUE_TEXT);

    Graphics_drawString(&g_sContext, "Location name:", AUTO_STRING_LENGTH, 10, 85, OPAQUE_TEXT);
    Graphics_drawString(&g_sContext, current_location_name, AUTO_STRING_LENGTH, 20, 105, OPAQUE_TEXT);
}

void draw_tilt() {
    Graphics_clearDisplay(&g_sContext);
    draw_title("Vehicle Tilt");
}

void draw_title(int8_t* title) {
    Graphics_setFont(&g_sContext, &TITLE_FONT);
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
        break;
    }
}

// function called when buttons S1 or S2 are pressed
void change_page(int8_t delta) {
    current_page_number = (current_page_number + delta + PAGES) % PAGES;
    draw_page();
}

// Function to call on speed_limit change
void update_speed_limit(int16_t speed_limit) {
    current_speed_limit = speed_limit;
    if (current_page_number == 0) {
        int8_t speed_limit[3];
        sprintf((char*)speed_limit, "%hd", current_speed_limit);

        Graphics_setFont(&g_sContext, &SPEED_FONT);
        Graphics_drawStringCentered(&g_sContext, "    ", AUTO_STRING_LENGTH, 64, 64, OPAQUE_TEXT);
        Graphics_drawStringCentered(&g_sContext, speed_limit, AUTO_STRING_LENGTH, 64, 64, OPAQUE_TEXT);
        Graphics_setFont(&g_sContext, &DEFAULT_FONT);
    }
}

// Function to call on vechicle speed change
void update_speed(int16_t nSpeed) {
    current_speed = nSpeed;

    if (current_page_number == 1) {
        int8_t speed[3];
        sprintf((char*)speed, "%hd", current_speed);
        int COLOR;

        // Checking if over speed limit
        if (current_speed > current_speed_limit) {
            COLOR = GRAPHICS_COLOR_RED;
        } else if (abs(current_speed - current_speed_limit) < 5) {
            COLOR = GRAPHICS_COLOR_ORANGE;
        } else {
            COLOR = GRAPHICS_COLOR_GREEN;
        }

        Graphics_setFont(&g_sContext, &SPEED_FONT);
        Graphics_drawStringCentered(&g_sContext, "    ", AUTO_STRING_LENGTH, 50, 64, OPAQUE_TEXT);
        Graphics_drawStringCentered(&g_sContext, speed, AUTO_STRING_LENGTH, 50, 64, OPAQUE_TEXT);

        Graphics_setForegroundColor(&g_sContext, COLOR);
        Graphics_setBackgroundColor(&g_sContext, COLOR);
        Graphics_drawStringCentered(&g_sContext, "          ", AUTO_STRING_LENGTH, 64, 112, OPAQUE_TEXT);
        Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_BLACK);
        Graphics_setBackgroundColor(&g_sContext, GRAPHICS_COLOR_WHITE);

        Graphics_setFont(&g_sContext, &DEFAULT_FONT);
    }
}

// Function to call on geolocation change
void update_geolocation(float lon, float lat, int8_t* location_name) {
    current_lon = lon;
    current_lat = lat;
    current_location_name = location_name;
    draw_page();
}

bool isInIdleState(int x){
    return ((x>7000) && (x<9000));
}

// Joystick interrupt handler
void ADC14_IRQHandler(void){
    uint64_t status;
    status = ADC14_getEnabledInterruptStatus();
    ADC14_clearInterruptFlag(status);

    //Joystick reading finished
    if(status & ADC_INT1){ //Conversion is over
        joystickBuffer[0] = ADC14_getResult(ADC_MEM0);
        joystickBuffer[1] = ADC14_getResult(ADC_MEM1);

        // change page by checking x axis joystick value
        if(!isInIdleState(joystickBuffer[0])){
            if(joystickBuffer[0] > 15000){
                change_page(1);
            } else if(joystickBuffer[0] < 1000){
                change_page(-1);
            }
        }
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





