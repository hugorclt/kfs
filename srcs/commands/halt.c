#include "commands.h"
#include "vga.h"

void	cmd_halt()
{
	vga_set_fg_color(VGA_COLOR_RED);
	printk("PANIC!");
	vga_set_fg_color(VGA_COLOR_WHITE);
	printk("\n");
	panic();
}
