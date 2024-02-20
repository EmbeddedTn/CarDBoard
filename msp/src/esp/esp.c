#include "esp.h"

#include "uart.h"
#include "../display/pages.h"
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <stdbool.h>

uint8_t TXData = 1;
uint8_t RXData = 0;
//the geographical address in which the gps is located
uint8_t location_address[MAX_SIZE_READ];
int8_t stato_comm = -1;
volatile bool first = true;

uint8_t lat[MAX_SIZE_COORDINATES];
uint8_t lon[MAX_SIZE_COORDINATES];

uint8_t speed[4];
uint8_t speed_limit[4];

uint8_t can_request = 1;

volatile request req = UNSET;

volatile uint8_t counter = 0;

const eUSCI_UART_ConfigV1 uartConfig = {
        EUSCI_A_UART_CLOCKSOURCE_SMCLK,          // SMCLK Clock Source
        13,                                      // divider
        0,                                       // UCxBRF = 0
        37,                                      // UCxBRS
        EUSCI_A_UART_NO_PARITY,                  // No Parity
        EUSCI_A_UART_LSB_FIRST,                  // LSB First
        EUSCI_A_UART_ONE_STOP_BIT,               // One stop bit
        EUSCI_A_UART_MODE,                       // UART mode
        EUSCI_A_UART_OVERSAMPLING_BAUDRATE_GENERATION,  // Oversampling
};

void update_value(request req){
    can_request = 1;
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

void interrupt_EUSCIA2__esp(){
    uint32_t status = UART_getEnabledInterruptStatus(EUSCI_A2_BASE);

    if(status & EUSCI_A_UART_RECEIVE_INTERRUPT_FLAG){
        // led for displaying we're receiving datas from esp32
        GPIO_setOutputHighOnPin(GPIO_PORT_P1, GPIO_PIN0);
        RXData = UART_receiveData(EUSCI_A2_BASE);

        // 0 Address, 1 Speed, 2 Speed Limit, 3 Lat, 4 Lon
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
        } else {
            GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0);
            first = true;
            update_value(req);
            counter = 0;
        }
    }
}

void setup__esp() {
    /* Selecting P3.2 and P3.3 in UART mode and P1.0 as output (LED) */
    GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P3,
             GPIO_PIN2 | GPIO_PIN3, GPIO_PRIMARY_MODULE_FUNCTION);
    GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN0);
    GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0);

    FlashCtl_setWaitState(FLASH_BANK0, 1);
    FlashCtl_setWaitState(FLASH_BANK1, 1);
    PCM_setCoreVoltageLevel(PCM_VCORE1);
    CS_setDCOCenteredFrequency(CS_DCO_FREQUENCY_24);

    /* Configuring UART Module */
    UART_initModule(EUSCI_A2_BASE, &uartConfig);

    /* Enable UART module */
    UART_enableModule(EUSCI_A2_BASE);

    /* Enabling interrupts */
    UART_enableInterrupt(EUSCI_A2_BASE, EUSCI_A_UART_RECEIVE_INTERRUPT);
    Interrupt_enableInterrupt(INT_EUSCIA2);

//    UART_transmitData(EUSCI_A2_BASE, TXData);
}
