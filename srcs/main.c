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

	for (size_t i = 0; i < 25; i++)
	{
		char c = 'A' + i;
		printk(&c);
		printk("\n-");
	}
}

void	kernel_main(void) 
{
	kernel_hello();

	// test_special_char();
}

// for (int y = 0; y < VGA_MAX_Y; y++) 
	// {
	// 	for (int x = 0; x < VGA_MAX_X; x++)
	// 	{
	// 		vga_write_buffer('a' + y);
	// 	}
	// }
	// vga_write_buffer('0');

//TODO
// cursor


//DONE
// utils true index_vga
// color terminal et colour police en global / singleton
//clear buffer vga
//quand ligne max atteint -> clear ligne 1 puis decaler tout de une ligne
// clear line 
// advance line
// fonction presentation 42 kfs de hugo et adrian
// debug de \r et \n --> a cause du strlen de adrian
// tester masse de \n
