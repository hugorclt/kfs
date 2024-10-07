#include "commands.h"
#include <stdint.h>

void 	hexdump(void *start, size_t byte)
{
	for (size_t i = 0; i < byte; i++) {
		uint8_t *address = start + i * 8;
		printk("%p :", (uint32_t)address);
		for (int j = 0; j < 8; j++)
		{
			printk(" %X ", (uint8_t)*(address + j));
		}
		printk("| ");
		for (int j = 0; j < 8; j++)
		{
			if ((uint8_t)*(address + j) < 33 || (uint8_t)*(address + j) >= 127)
				printk(".");
			else
				printk("%c", (uint8_t)*(address + j));
		}
		printk("\n");
	}
	
}
