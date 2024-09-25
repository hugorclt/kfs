#include "kernel.h"

void kernel_entry()
{
	// first init vga with fore & back colors
	init_vga(WHITE, BLACK);
	printk("42");

	init_idt();

	for(;;)
	{
		asm("hlt");
	}
}
