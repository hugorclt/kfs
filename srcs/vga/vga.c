#include <vga.h>

uint16_t*		vga_buffer	= (uint16_t*) 0xB8000;
size_t 			vga_y		= 0;
size_t			vga_x		= 0;
enum vga_color	fg_color = VGA_COLOR_WHITE;
enum vga_color	bg_color = VGA_COLOR_BLACK;



inline static uint8_t	vga_entry_color(enum vga_color fg, enum vga_color bg) 
{
	return (fg | (bg << 4));
}

inline uint16_t			vga_entry(unsigned char uc, enum vga_color fg, enum vga_color bg)
{
	uint8_t	color = vga_entry_color(fg, bg);

	return ((uint16_t) uc | ((uint16_t) color << 8));
}

inline static size_t	vga_index(size_t x, size_t y)
{
	return ((y * VGA_MAX_X) + x);
}

void					vga_set_fg_color(enum vga_color color)
{
	fg_color = color;
}

void					vga_set_bg_color(enum vga_color color)
{
	bg_color = color;
}

void					vga_clear_line(size_t y)
{
	for (size_t x = 0; x < VGA_MAX_X; x++)
	{
		size_t index = vga_index(x, y);

		vga_buffer[index] = vga_entry(' ', fg_color, bg_color);
	}
}

void					vga_copy_line(size_t dst_y, size_t src_y)
{
	for (size_t x = 0; x < VGA_MAX_X; x++)
	{
		size_t	dst_index = vga_index(x, dst_y);
		size_t	src_index = vga_index(x, src_y);

		vga_buffer[dst_index] = vga_buffer[src_index];
	}
}

void					vga_scroll_one_line()
{
	for (size_t y = 0; y < VGA_MAX_Y - 1; y++)
	{
		vga_copy_line(y, y + 1);
	}
	vga_clear_line(VGA_MAX_Y - 1);
}

static bool					vga_write_special_char(unsigned char uc )
{
	if (uc == '\n')
	{
		vga_x = 0;
		vga_y += 1;
		return (1);
	}
	else if (uc == '\r')
	{
		vga_x = 0;
		return (1);
	}
	return (0);
}

static void					vga_write_char(unsigned char uc)
{
	size_t index = vga_index(vga_x, vga_y);
	vga_buffer[index] = vga_entry(uc, fg_color, bg_color);
	vga_x += 1;
}

void					vga_write_buffer(unsigned char uc)
{
	if (!vga_write_special_char(uc))
		vga_write_char(uc);

	if (vga_x >= VGA_MAX_X)
	{
		vga_x = 0;
		vga_y += 1;
	}
	if (vga_y >= VGA_MAX_Y)
	{
		vga_scroll_one_line();
		vga_y -= 1;
		vga_x = 0;
	}
}



void					vga_clear_buffer()
{
	for (size_t y = 0; y < VGA_MAX_Y; y++)
	{
		for (size_t x = 0; x < VGA_MAX_X; x++)
		{
			size_t index = vga_index(x, y);
			vga_buffer[index] = vga_entry(' ', fg_color, bg_color);
		}
	}
	vga_x = 0;
	vga_y = 0;
}