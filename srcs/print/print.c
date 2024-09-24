#include "print.h"
#include <stdint.h>

/*
16 bit video buffer elements(register ax)
8 bits(ah) higher :
  lower 4 bits - forec olor
  higher 4 bits - back color

8 bits(al) lower :
  8 bits : ASCII character to print
*/
uint16_t vga_entry(unsigned char ch, uint8_t fore_color, uint8_t back_color)
{
	uint16_t ax = 0;
	uint8_t ah = 0, al = 0;

	ah = back_color;
	ah <<= 4;
	ah |= fore_color;
	ax = ah;
	ax <<= 8;
	al = ch;
	ax |= al;

	return ax;
}

// clear video buffer array
void clear_vga_buffer(uint16_t **buffer, uint8_t fore_color, uint8_t back_color)
{
	uint32_t i;

	for(i = 0; i < BUFSIZE; i++)
	{
		(*buffer)[i] = vga_entry(' ', fore_color, back_color);
	}
}

// initialize vga buffer
void init_vga(uint8_t fore_color, uint8_t back_color)
{
	uint16_t *vga_buffer = (uint16_t *)0xB8000;
	clear_vga_buffer(&vga_buffer, fore_color, back_color); // clear buffer
}

int strlen(char *str)
{
	int i = 0;

	while(str[i])
		i++;
	return (i);
}

void printk(char *str)
{
	uint16_t *vga_buffer = (uint16_t *)0xB8000;
	for(int i = 0; i < strlen(str); i++)
		vga_buffer[i] = vga_entry(str[i], WHITE, BLACK);
}
