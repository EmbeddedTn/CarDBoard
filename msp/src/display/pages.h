#ifndef __PAGES_H__
#define __PAGES_H__

#include <ti/grlib/grlib.h>


extern Graphics_Context g_sContext;


void draw_title(int8_t*);
void draw_speed();
void draw_geolocation();
void draw_tilt();
void draw_title(int8_t* title);
void draw_page();
void change_page(int8_t delta);
bool in_idle_state(int x);

void update_speed_limit(uint16_t speed_limit);
extern void update_speed(uint16_t speed);
void update_geolocation(float lon, float lat, int8_t* location_name);
void update_tilt();
void update_car_side(float y_axis);
void car_side_init();
void car_front_init();


#endif /* PAGES_H_ */
