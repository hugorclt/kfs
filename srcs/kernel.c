#include "kernel.h"

/*
16 bit video buffer elements(register ax)
8 bits(ah) higher :
  lower 4 bits - forec olor
  higher 4 bits - back color

8 bits(al) lower :
  8 bits : ASCII character to print
*/
uint16 vga_entry(unsigned char ch, uint8 fore_color, uint8 back_color)
{
	uint16 ax = 0;
	uint8 ah = 0, al = 0;

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
void clear_vga_buffer(uint16 **buffer, uint8 fore_color, uint8 back_color)
{
	uint32 i;

	for(i = 0; i < BUFSIZE; i++)
	{
		(*buffer)[i] = vga_entry(NULL, fore_color, back_color);
	}
}

// initialize vga buffer
void init_vga(uint8 fore_color, uint8 back_color)
{
	vga_buffer = (uint16 *)VGA_ADDRESS;		       // point vga_buffer pointer to VGA_ADDRESS
	clear_vga_buffer(&vga_buffer, fore_color, back_color); // clear buffer
}

void terminal_putchar(char c, int color)
{
	static int curr_x = 0;
	static int curr_y = 0;

	if(curr_x > VGA_WIDTH)
	{
		curr_x = 0;
		curr_y += 1;
		if(curr_y > VGA_HEIGHT)
		{
			curr_y = 0;
		}
	}

	int index = curr_y * VGA_WIDTH + curr_x;
	vga_buffer[index] = vga_entry(c, color, BLACK);
	curr_x += 1;
}

void terminal_putstring(char *str, int size)
{
	for(int i = 0; i < size; i++)
	{
		terminal_putchar(str[i], WHITE);
	}
}

void kernel_entry()
{
	// first init vga with fore & back colors
	init_vga(WHITE, BLACK);

	terminal_putstring("42", sizeof("42"));
}
