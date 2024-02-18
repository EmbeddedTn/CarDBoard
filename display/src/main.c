#include <ti/devices/msp432p4xx/inc/msp.h>
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>

// init functions
#include "../include/init.h"

// UI functions
#include "../include/pages.h"

//uart
#include "../include/uart.h"

#define MAX_SIZE_READ 128
#define MAX_SIZE_COORDINATES 11

uint8_t TXData = 1;
uint8_t RXData = 0;
//the geographical address in which the gps is located
uint8_t location_address[MAX_SIZE_READ];
int8_t stato_comm = -1;
bool first = true;

uint8_t lat[MAX_SIZE_COORDINATES];
uint8_t lon[MAX_SIZE_COORDINATES];

uint8_t speed[4];
uint8_t speed_limit[4];

void update_value(request req);




request req = UNSET;

uint8_t counter = 0;

int main(void)
{
    init_all();
    car_side_init();
    car_front_init();

    srand(time(0));
    while (1){
       UART_transmitData(EUSCI_A2_BASE, TXData);

       PCM_gotoLPM0();
    }
}


// Example timer handler implementation to change the values of speed_limit and speed
// See init.h for timer specs
//
// -- Usage
// A timer can be implemented to query ESP and check if the parameters have changed.
// If so, call update_{parameter}() function to update the screen.
volatile int8_t first = 0;
void TA1_0_IRQHandler(void)
{
    update_speed_limit(rand() % 150);
    update_speed(rand() % 150);
    Timer_A_clearCaptureCompareInterrupt(TIMER_A1_BASE,
            TIMER_A_CAPTURECOMPARE_REGISTER_0);
}

void TA2_0_IRQHandler(void)
{
    update_tilt();
    Timer_A_clearCaptureCompareInterrupt(TIMER_A2_BASE,
            TIMER_A_CAPTURECOMPARE_REGISTER_0);

}

/* EUSCI A0 UART ISR */
void EUSCIA2_IRQHandler(void)
{
    uint32_t status = UART_getEnabledInterruptStatus(EUSCI_A2_BASE);

    if(status & EUSCI_A_UART_RECEIVE_INTERRUPT_FLAG)
    {
        //led for displaying we're receiving datas from esp32
        GPIO_setOutputHighOnPin(GPIO_PORT_P1, GPIO_PIN0);
        RXData = UART_receiveData(EUSCI_A2_BASE);

        //0 Indirizzo, 1 Velocità, 2 Limite Velocità, 3 Lat, 4 Lon
        if(RXData != '\n'){
            if(first){
               req = RXData;
               first = false;
            }else{
                switch(req) {
                    case ADDRESS:
                        location_address[counter] = RXData;
                        break;
                    case SPEED:
                        speed[counter] = RXData;
                        break;
                    case LIMIT:
                        speed_limit[counter] = RXData;
                       break;
                    case LAT:
                        lat[counter] = RXData;
                        break;
                    case LON:
                        lon[counter] = RXData;
                        break;
                    default:
                        first = true;
                        req = UNSET;
                        //todo send error
                        break;
                }
                counter++;
            }
        }else{
            GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0);
            first = true;
            update_value();
            counter = 0;
        }


        fflush(stdout);
        Interrupt_disableSleepOnIsrExit();
    }

}

void update_value(request req){
    switch(req) {
        case ADDRESS:
            location_address[counter] = '\0';
            //TODO
            update_address(location_address);
            break;
        case SPEED:
            speed[counter] = '\0';
            update_speed(speed);
            break;
        case LIMIT:
           speed_limit[counter] = '\0';
           update_speed_limit(speed_limit);
           break;
        case LAT:
            lat[counter] = '\0';
            update_lat(lat);
            break;
        case LON:
            lon[counter] = '\0';
            update_lon(lon);
            break;
        default:
            first = true;
            req = UNSET;
            //todo send error
            break;
    }
}

