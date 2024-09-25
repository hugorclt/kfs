#include "pic.h"

void init_keyboard() { outb(PIC1_DATA_PORT, 0xFD); }

void enable_interrupt() { asm("sti"); }

void PIC_remap(int offset1, int offset2)
{
	// Init two pic
	outb(PIC1_COMMAND_PORT, 0x11);
	outb(PIC2_COMMAND_PORT, 0x11);

	// set vector position
	outb(PIC1_DATA_PORT, offset1);
	outb(PIC2_DATA_PORT, offset2);

	// link two pic
	outb(PIC1_DATA_PORT, 0x0);
	outb(PIC2_DATA_PORT, 0x0);

	// Additionnal info
	outb(PIC1_DATA_PORT, 0x1);
	outb(PIC2_DATA_PORT, 0x1);

	// Mask
	outb(PIC1_DATA_PORT, 0xff);
	outb(PIC2_DATA_PORT, 0xff);

	init_keyboard();
	enable_interrupt();
}
