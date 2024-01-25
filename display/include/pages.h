#include <ti/grlib/grlib.h>

#ifndef PAGES_H_
#define PAGES_H_

extern Graphics_Context g_sContext;

int8_t* speed_from_int(int speed);
void draw_speed_limit(int speed_int);
void draw_page(uint8_t page_number);
void change_page(int delta);


#endif /* PAGES_H_ */
