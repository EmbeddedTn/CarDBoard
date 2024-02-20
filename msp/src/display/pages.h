#ifndef __PAGES_H__
#define __PAGES_H__

#include <ti/grlib/grlib.h>

extern Graphics_Context g_sContext;

void car_side_init();
void car_front_init();
void draw_title(int8_t*);
void draw_speed();
void draw_geolocation();
void draw_tilt();
void draw_title(int8_t* title);
void draw_page();
void change_page(int8_t delta);
bool in_idle_state(int x);

void update_speed_limit(uint8_t* speed_limit);
void update_speed(uint8_t* nSpeed);
void update_address(uint8_t* location_name);
void update_lat(uint8_t* lat);
void update_lon(uint8_t* lon);
void update_tilt();
void update_car_side(float y_axis);
void update_car_front(float x_axis);
extern volatile uint8_t rcount;

#endif /* PAGES_H_ */
