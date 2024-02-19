#ifndef __UTILS_H__
#define __UTILS_H__

#include <stdint.h>

#define TIMER_PERIOD 0x2DC6 // 11718
void setup__hw();
void irq_dispatcher(void (*handlers[])(), uint8_t handler_len);

#endif
