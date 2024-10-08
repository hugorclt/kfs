#include "commands.h"
#include <stdint.h>

void print_uint8_hex(uint8_t num) {
    char buffer[3];
    char hex_chars[] = "0123456789ABCDEF";

    buffer[0] = hex_chars[(num >> 4) & 0xF];
    buffer[1] = hex_chars[num & 0xF];
    buffer[2] = '\0';

    printk(" %s ", buffer);
}

void 	cmd_hexdump(void *start, size_t byte)
{
	for (size_t i = 0; i < byte; i++) {
		uint8_t *address = start + i * 8;
		printk("%p :", (uint32_t)address);
		for (int j = 0; j < 8; j++)
		{
			print_uint8_hex((uint8_t)*(address + j));
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
