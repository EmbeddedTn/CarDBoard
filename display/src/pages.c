#include <ti/devices/msp432p4xx/inc/msp.h>
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <ti/grlib/grlib.h>
#include <stdio.h>
#include <stdint.h>

// file initializing the speed limit background image
#include "../include/slb.h"

/* Graphic library context */
Graphics_Context g_sContext;

#define SPEED_FONT g_sFontCmss30b
#define DEFAULT_FONT g_sFontCmss12
#define PAGES 4

// Global variables
static uint16_t joystickBuffer[2];

uint8_t current_page_number = 0;
int16_t current_speed_limit = 69;
int16_t current_speed = 4.20;

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

    Graphics_setFont(&g_sContext, &SPEED_FONT);
    Graphics_drawStringCentered(&g_sContext, speed, AUTO_STRING_LENGTH, 64, 64, OPAQUE_TEXT);
    Graphics_setFont(&g_sContext, &DEFAULT_FONT);
}

// Select the page to draw to the screen
void draw_page() {
    switch (current_page_number) {
    case 0:
        Graphics_clearDisplay(&g_sContext);
        draw_speed_limit();
        Graphics_drawString(&g_sContext, "Speed Limit", AUTO_STRING_LENGTH, 5, 5, OPAQUE_TEXT);

        break;
    case 1:
        Graphics_clearDisplay(&g_sContext);
        Graphics_drawString(&g_sContext, "Vehicle Tilt", AUTO_STRING_LENGTH, 5, 5, OPAQUE_TEXT);

        break;
    case 2:
        Graphics_clearDisplay(&g_sContext);
        Graphics_drawString(&g_sContext, "Speed", AUTO_STRING_LENGTH, 5, 5, OPAQUE_TEXT);
        draw_speed();

        break;
    case 3:
        Graphics_clearDisplay(&g_sContext);
        Graphics_drawString(&g_sContext, "Geolocation", AUTO_STRING_LENGTH, 5, 5, OPAQUE_TEXT);

        break;
    default:
        Graphics_clearDisplay(&g_sContext);
        Graphics_drawString(&g_sContext, "Err", AUTO_STRING_LENGTH, 5, 5, OPAQUE_TEXT);

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

// Joystick interrupt
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

// Button S1 interrupt
void PORT5_IRQHandler(){
    uint_fast16_t status = GPIO_getEnabledInterruptStatus(GPIO_PORT_P5);
    GPIO_clearInterruptFlag(GPIO_PORT_P5,status);
    if (status & GPIO_PIN1){
        change_page(1);
    }
}

void PORT3_IRQHandler(){
    uint_fast16_t status = GPIO_getEnabledInterruptStatus(GPIO_PORT_P3);
    GPIO_clearInterruptFlag(GPIO_PORT_P3,status);
    if (status & GPIO_PIN5){
        change_page(-1);
    }
}





