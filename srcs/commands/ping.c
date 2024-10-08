#include "commands.h"
#include "vga.h"
#include "printk.h"

void cmd_ping()
{
	vga_set_fg_color(VGA_COLOR_LIGHT_GREEN);
	printk("pong");
	vga_set_fg_color(VGA_COLOR_WHITE);
	printk("\n");
}
