#include "vga.h"
#include "printk.h"

void	cmd_hello(void)
{
	vga_set_fg_color(VGA_COLOR_WHITE);
	vga_set_bg_color(VGA_COLOR_BLACK);
	printk("Hello 42!\n");
	printk("Kernel From Scratch by ");

	vga_set_fg_color(VGA_COLOR_LIGHT_RED);
	printk("Hugo");
	vga_set_fg_color(VGA_COLOR_WHITE);
	printk(" and ");
	vga_set_fg_color(VGA_COLOR_LIGHT_CYAN);
	printk("Adrian");
	vga_set_fg_color(VGA_COLOR_WHITE);
	vga_set_bg_color(VGA_COLOR_BLACK);
	printk(" \n\n");
}
