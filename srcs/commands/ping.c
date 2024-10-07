#include "commands.h"
#include "vga.h"
#include "printk.h"

void ping()
{
	vga_set_fg_color(VGA_COLOR_LIGHT_GREEN);
	printk("pong\n");
	vga_set_fg_color(VGA_COLOR_WHITE);
}
