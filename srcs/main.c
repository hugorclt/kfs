#include <print.h>
#include <stdint.h>
#include <stddef.h>


void	kernel_hello(void)
{
	vga_set_fg_color(VGA_COLOR_WHITE);
	vga_set_bg_color(VGA_COLOR_BLACK);
	printk("Hello 42!\n\n");
	printk("Kernel From Scratch by ");

	vga_set_fg_color(VGA_COLOR_LIGHT_RED);
	printk("Hugo");
	vga_set_fg_color(VGA_COLOR_WHITE);
	printk(" and ");
	vga_set_fg_color(VGA_COLOR_LIGHT_CYAN);
	printk("Adrian");

	
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
	// vga_clear_buffer();
	// kernel_hello();	
}

