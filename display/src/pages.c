#include <ti/devices/msp432p4xx/inc/msp.h>
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <ti/grlib/grlib.h>
#include <stdio.h>
#include <stdint.h>

// file initializing the speed limit background image
#include "../include/slb.h"

// Graphic library context
Graphics_Context g_sContext;

#define SPEED_FONT g_sFontCmss30b
#define TITLE_FONT g_sFontCmss12b
#define DEFAULT_FONT g_sFontCmss12
#define PAGES 4

// Global variables
static uint16_t joystickBuffer[2];

uint8_t current_page_number = 0;
int16_t current_speed_limit = 69;
int16_t current_speed = 12;

float lon = 46.06705235237631;
float lat = 11.149869220425288;

int8_t* speed_from_int(int16_t speed) {
    int8_t* str = (int8_t*)malloc(3 * sizeof(int8_t));
    sprintf((char*)str, "%hd", speed);
    return str;
}

void draw_speed_limit() {
    int8_t* speed_limit = speed_from_int(current_speed_limit);
    Graphics_drawImage(&g_sContext, &slb_image, 0, 0);

    Graphics_setFont(&g_sContext, &SPEED_FONT);
    Graphics_drawStringCentered(&g_sContext, speed_limit, AUTO_STRING_LENGTH, 64, 64, OPAQUE_TEXT);
    Graphics_setFont(&g_sContext, &DEFAULT_FONT);
}

void draw_speed() {
    int8_t* speed = speed_from_int(current_speed);
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
    Graphics_drawStringCentered(&g_sContext, speed, AUTO_STRING_LENGTH, 50, 64, OPAQUE_TEXT);

    Graphics_setForegroundColor(&g_sContext, COLOR);
    Graphics_setBackgroundColor(&g_sContext, COLOR);
    Graphics_drawStringCentered(&g_sContext, "        ", AUTO_STRING_LENGTH, 64, 112, OPAQUE_TEXT);
    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_BLACK);
    Graphics_setBackgroundColor(&g_sContext, GRAPHICS_COLOR_WHITE);

    Graphics_setFont(&g_sContext, &DEFAULT_FONT);
    Graphics_drawStringCentered(&g_sContext, "Km/h", AUTO_STRING_LENGTH, 80, 64, OPAQUE_TEXT);
}

void draw_geolocation() {
    int8_t latitude[10];
    int8_t longitude[10];
    sprintf((char*)latitude, "%f", lat);
    sprintf((char*)longitude, "%f", lon);

    Graphics_drawStringCentered(&g_sContext, "Lon: ", AUTO_STRING_LENGTH, 20, 35, OPAQUE_TEXT);
    Graphics_drawStringCentered(&g_sContext, longitude, AUTO_STRING_LENGTH, 60, 35, OPAQUE_TEXT);

    Graphics_drawStringCentered(&g_sContext, "Lat: ", AUTO_STRING_LENGTH, 20, 55, OPAQUE_TEXT);
    Graphics_drawStringCentered(&g_sContext, latitude, AUTO_STRING_LENGTH, 60, 55, OPAQUE_TEXT);
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
        Graphics_clearDisplay(&g_sContext);
        draw_speed_limit();
        //Graphics_drawString(&g_sContext, "Speed Limit", AUTO_STRING_LENGTH, 5, 5, OPAQUE_TEXT);
        draw_title("Speed Limit");

        break;
    case 1:
        Graphics_clearDisplay(&g_sContext);
        draw_title("Vehicle Tilt");

        break;
    case 2:
        Graphics_clearDisplay(&g_sContext);
        draw_title("Speed");
        draw_speed();

        break;
    case 3:
        Graphics_clearDisplay(&g_sContext);
        draw_title("Geolocation");
        draw_geolocation();

        break;
    default:
        Graphics_clearDisplay(&g_sContext);
        draw_title("Err");

        break;
    }

}

// function called when buttons S1 or S2 are pressed
void change_page(int8_t delta) {
    current_page_number = abs(current_page_number + delta) % PAGES;
    draw_page();
}

// Function to call on speed_limit change
void update_speed_limit(int16_t speed_limit) {
    current_speed_limit = speed_limit;
    draw_page();
}

// Function to call on vechicle speed change
void update_speed(int16_t speed) {
    current_speed = speed;
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
            if(joystickBuffer[0] > 14000){
                change_page(1);
            }
            if(joystickBuffer[0] < 2500){
                change_page(-1);
            }
        }
    }
}

// Button S1 interrupt handler
void PORT5_IRQHandler(){
    uint_fast16_t status = GPIO_getEnabledInterruptStatus(GPIO_PORT_P5);
    GPIO_clearInterruptFlag(GPIO_PORT_P5,status);
    if (status & GPIO_PIN1){
        change_page(1);
    }
}

// Button S2 interrupt handler
void PORT3_IRQHandler(){
    uint_fast16_t status = GPIO_getEnabledInterruptStatus(GPIO_PORT_P3);
    GPIO_clearInterruptFlag(GPIO_PORT_P3,status);
    if (status & GPIO_PIN5){
        change_page(-1);
    }
}





