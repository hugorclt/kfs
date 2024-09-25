#include "print.h"
#include <stdint.h>
#include <sys/types.h>

int g_cursor_y = 0;
int g_cursor_x = 0;

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
	uint16_t ret = 0;
	uint8_t color = 0, c = 0;

	color = back_color;
	color <<= 4;
	color |= fore_color;
	ret = color;
	ret <<= 8;
	c = ch;
	ret |= c;

	return ret;
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

// 0x21
// index: 2
//  -> 1
//  index: 3 -> 1
//  index: 3 -> 5
void ft_putnbr(uint32_t n)
{
	uint16_t *vga_buffer = (uint16_t *)0xB8000;
	char *base;
	unsigned int nb;

	base = "0123456789";
	nb = n;
	if(nb >= 16)
	{
		ft_putnbr(nb / 16);
		ft_putnbr(nb % 16);
	}
	else
	{
		int index = g_cursor_y * VGA_WIDTH + g_cursor_x;
		vga_buffer[index] = vga_entry(base[nb % 16], WHITE, BLACK);
		g_cursor_x += 1;
	}
}

void ft_putnbr_base(uint32_t n)
{
	uint16_t *vga_buffer = (uint16_t *)0xB8000;
	char *base;
	unsigned int nb;

	base = "0123456789ABCDEF";
	nb = n;
	if(nb >= 16)
	{
		ft_putnbr_base(nb / 16);
		ft_putnbr_base(nb % 16);
	}
	else
	{
		int index = g_cursor_y * VGA_WIDTH + g_cursor_x;
		vga_buffer[index] = vga_entry(base[nb % 16], WHITE, BLACK);
		g_cursor_x += 1;
	}
}

void printkd(uint32_t hex)
{
	ft_putnbr(hex);
	g_cursor_y += 1;
	g_cursor_x = 0;
}

void printkx(uint32_t hex)
{
	uint16_t *vga_buffer = (uint16_t *)0xB8000;
	int index = g_cursor_y * VGA_WIDTH + 0;
	vga_buffer[index] = vga_entry('0', YELLOW, BLACK);
	vga_buffer[index + 1] = vga_entry('x', YELLOW, BLACK);

	ft_putnbr_base(hex);
	g_cursor_y += 1;
	g_cursor_x = 0;
}

void printk(char *str)
{
	uint16_t *vga_buffer = (uint16_t *)0xB8000;
	int i = 0;

	while(i < strlen(str))
	{
		int index = g_cursor_y * VGA_WIDTH + g_cursor_x;
		vga_buffer[index] = vga_entry(str[i], WHITE, BLACK);
		i++;
		g_cursor_x++;
	}
	g_cursor_x = 0;
	g_cursor_y += 1;
}
