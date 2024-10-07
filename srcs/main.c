#include "debug.h"
#include "commands.h"
#include "printk.h"
#include "gdt.h"
#include "idt.h"
#include "vga.h"
#include "shell.h"

void	kernel_hello(void)
{
	vga_set_fg_color(VGA_COLOR_WHITE);
	vga_set_bg_color(VGA_COLOR_BLACK);
	printk("\nHello 42!\n");
	printk("Kernel From Scratch by ");

	vga_set_fg_color(VGA_COLOR_LIGHT_RED);
	printk("Hugo");
	vga_set_fg_color(VGA_COLOR_WHITE);
	printk(" and ");
	vga_set_fg_color(VGA_COLOR_LIGHT_CYAN);
	printk("Adrian");
	vga_set_fg_color(VGA_COLOR_WHITE);
	vga_set_bg_color(VGA_COLOR_BLACK);
	printk(" ");
	printk("\n\n");

}

void	kernel_main(void) 
{
	vga_clear_buffer();
	kernel_hello();
	gdt_init();
	idt_init();

	

	shell();
	while(1);
}
