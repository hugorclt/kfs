#pragma once

#include <stdint.h> 

extern uint8_t inb(uint16_t port);
extern void outb(uint16_t port, uint8_t value);
extern void outw(uint16_t port, uint16_t value);
extern void iowait();
