#include "print.h"
#include "vga.h"
#include <stdint.h>

static size_t	strlen(const char* str)
{
	size_t	i = 0;
	while(str[i])
	{
		i++;
	}
	return (i);
}

void	printk(const char* str)
{
	for (size_t i = 0; i < strlen(str); i++)
	{
		vga_write_buffer(str[i]);
	}
}

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
		// vga_putnbr_hex(*(address + 1));
		// vga_putnbr_hex(*(address + 2));
		// vga_putnbr_hex(*(address + 3));
		printk("\n");
	}
		
}
