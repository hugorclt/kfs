#include "debug/debug.h"
#include "print.h"
#include "printk.h"
#include "gdt.h"
#include "idt.h"
#include "vga.h"
#define	nb_gdt_descriptor	7
#define	size_gdt_descriptor	8


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

void	test_special_char(void)
{
	printk("Hello test\n0123\n0123\n\n0123\n");
	printk("abc123\r");
	printk("A\n");
	printk("B");

	for (size_t i = 0; i < 100; i++)
	{
		for (size_t i = 0; i < 26; i++)
		{
			char	str[2];
			str[0] = 'A' + i;
			str[1] = '\0';
			printk("\n-");
			printk(str);
		}
	}
	
}

void	kernel_main(void) 
{
	// test_special_char();
	vga_clear_buffer();
	kernel_hello();
	gdt_init();
	idt_init();


	// printmemk((char *)0x800,
		// ( (nb_gdt_descriptor * size_gdt_descriptor) / 4));

	while(1);
}
