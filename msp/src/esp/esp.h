#ifndef __ESP_H__
#define __ESP_H__

#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

#define MAX_SIZE_READ 128
#define MAX_SIZE_COORDINATES 11

//void update_value(request req);
void interrupt_EUSCIA2__esp();
void setup__esp();

#endif //__ESP_H__