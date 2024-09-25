#pragma once

#include <stdint.h>

#define PIC1_COMMAND_PORT 0x20
#define PIC1_DATA_PORT 0x21
#define PIC2_COMMAND_PORT 0xA0
#define PIC2_DATA_PORT 0xA1

extern void outb(unsigned short port, unsigned char data);
extern char inb(unsigned short port);

void PIC_remap(int offset, int offset2);
void acknowledge_interrupt(unsigned int interrupt);
void init_keyboard();
void enable_interrupt();
