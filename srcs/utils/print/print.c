#include "print.h"
#include "printk.h"
#include "vga.h"
#include <stdint.h>

void	printkhex(uint32_t nb)
{
	printk("0x");	
	vga_putnbr_hex(nb);
}

void 	printmemk(void *start, size_t byte)
{
	for (size_t i = 0; i < byte; i++) {
		uint32_t *address = start + i * 4;
		printkhex((uint32_t)address);
		printk(" : ");
		printkhex(*address);
		printk("     :    ");
		vga_write_buffer((char)*address);
		// vga_putnbr_hex(*(address + 1));
		// vga_putnbr_hex(*(address + 2));
		// vga_putnbr_hex(*(address + 3));
		printk("\n");
	}
		
}
