#ifndef __PAGES_H__
#define __PAGES_H__

#include <ti/grlib/grlib.h>

extern Graphics_Context g_sContext;

/*
 * Function: car_side_init
 * -------------------------
 *  Initialize the car_side image
 */
void car_side_init();

/*
 * Function: car_front_init
 * -------------------------
 *  Initialize the car_front image
 */
void car_front_init();

/*
 * Function: draw_title
 * Parameters: int8_t* title - title to be drawn
 * -------------------------
 *  Draws the provided title of each page on the display
 */
void draw_title(int8_t *);

/*
 * Function: draw_speed_limit
 * -------------------------
 *  Draws the speed limit on the display
 */
void draw_speed_limit();

/*
 * Function: draw_speed
 * -------------------------
 *  Draws the speed on the display
 */
void draw_speed();

/*
 * Function: draw geolocation
 * -------------------------
 *  Draws the geolocation (longitude and latitude) on the display
 */
void draw_geolocation();

/*
 * Function: draw_tilt
 * -------------------------
 *  Draws the tilt on the display
 */
void draw_tilt();

/*
 * Function: draw_page
 * -------------------------
 *  Draws the current page on the display
 */
void draw_page();

/*
 * Function: change_page
 * Parameters: int8_t delta - how to change the page
 * -------------------------
 *  Changes the current page and draws it on the display
 */
void change_page(int8_t delta);

/*
 * Function: in_idle_state
 * Parameters: int x - the current joystick value
 * -------------------------
 *  Check if joystick is in a range to be considered idle
 */
bool in_idle_state(int x);

/*
 * Function: update_speed_limit
 * Parameters: uint8_t* speed_limit - the new speed limit
 * -------------------------
 *  Updates the speed limit on the display
 */
void update_speed_limit(uint8_t *speed_limit);

/*
 * Function: update_speed
 * Parameters: uint8_t* nSpeed - the new speed
 * -------------------------
 *  Updates the speed on the display
 */
void update_speed(uint8_t *nSpeed);

/* Function: update_address
 * Parameters: uint8_t* location_name - the new location name
 * -------------------------
 *  Updates the location name on the display
 */
void update_address(uint8_t *location_name);

/* Function: update_lat
 * Parameters: uint8_t* lat - the new latitude
 * -------------------------
 *  Updates the latitude on the display
 */
void update_lat(uint8_t *lat);

/* Function: update_lon
 * Parameters: uint8_t* lon - the new longitude
 * -------------------------
 *  Updates the longitude on the display
 */
void update_lon(uint8_t *lon);

/* Function: update_tilt
 * -------------------------
 *  Updates the tilt on the display
 */
void update_tilt();

/* Function: update_car_side
 * Parameters: float y_axis - the y axis value
 * -------------------------
 *  Updates the car side image on the display
 */
void update_car_side(float y_axis);

/* Function: update_car_front
 * Parameters: float x_axis - the x axis value
 * -------------------------
 *  Updates the car front image on the display
 */
void update_car_front(float x_axis);

/*
 * Counter used to handle ESP32 requests
 */
extern volatile uint8_t rcount;

#endif /* PAGES_H_ */
