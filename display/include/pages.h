#include <ti/grlib/grlib.h>

#ifndef PAGES_H_
#define PAGES_H_

extern Graphics_Context g_sContext;

void update_speed_limit(int speed_limit);
void update_speed(int speed);
void update_geolocation(float lon, float lat, int8_t* location_name);


#endif /* PAGES_H_ */
