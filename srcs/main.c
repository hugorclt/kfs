#include <stdint.h>
#include <stddef.h>
#include "print.h"
#include "gdt.h"
#include "vga.h"


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

#define	nb_gdt_descriptor	7
#define	size_gdt_descriptor	8

void	kernel_main(void) 
{
	

	// test_special_char();
	// vga_clear_buffer();
	// kernel_hello();	
	gdt_init();
	int i = 0x42;
	int i2 = 0x42;
	int i3 = 0x42;
	int i4 = 0x42;
	int i5 = 0x42;
	int i6 = 0x42;
	int i7 = 0x42;
	int i8 = 0x42;
	int i9 = 0x42;
	int i10 = 0x42;
	// printmemk((char *)0x800,
	// 	( (nb_gdt_descriptor * size_gdt_descriptor) / 4));
	printmemk((char *)0x4000, 1000);

}
