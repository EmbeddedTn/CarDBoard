#include <stdlib.h>

#ifndef __DISPLAY_H__
#define __DISPLAY_H__

/*
 * Function: setup__display
 * -------------------------
 *  Setup the display, initializing the car images for the tilt section
 *  and all the necesary pins for the display
 *
 *  Returns: void
 */
void setup__display();

/*
 * Function: interrupt_TA1_0__display
 * -------------------------
 *  Interrupt to update the display, it is called every ~0.7 seconds.
 *  It updates the display with the contents of the current page,
 *  also sending requests to the sensors / ESP32
 */
void interrupt_TA1_0__display();

#endif
