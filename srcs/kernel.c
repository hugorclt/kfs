#include "kernel.h"

void kernel_entry()
{
	// first init vga with fore & back colors
	init_vga(WHITE, BLACK);
	// init_idt();

	printk("42");
}
