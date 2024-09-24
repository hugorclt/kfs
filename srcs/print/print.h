#pragma once

#include <stddef.h>
#include <stdint.h>

#define VGA_ADDRESS 0xB8000
#define BUFSIZE 2200

#define VGA_WIDTH 80
#define VGA_HEIGHT 25

enum vga_color {
	BLACK,
	BLUE,
	GREEN,
	CYAN,
	RED,
	MAGENTA,
	BROWN,
	GREY,
	DARK_GREY,
	BRIGHT_BLUE,
	BRIGHT_GREEN,
	BRIGHT_CYAN,
	BRIGHT_RED,
	BRIGHT_MAGENTA,
	YELLOW,
	WHITE,
};

void printk(char *str);
void init_vga(uint8_t fore_color, uint8_t back_color);
