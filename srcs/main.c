#include <print.h>
#include <stdint.h>
#include <stddef.h>


void kernel_main(void) 
{
	vga_set_fg_color(VGA_COLOR_WHITE);
	vga_set_bg_color(VGA_COLOR_BLACK);

	// for (int y = 0; y < VGA_MAX_Y; y++) 
	// {
	// 	for (int x = 0; x < VGA_MAX_X; x++)
	// 	{
	// 		vga_write_buffer('a' + y);
	// 	}
	// }
	// vga_write_buffer('0');
	printk("Hello world!\naaaa\rA");

}


// \r pose un espace ??
// cursor
// tester masse de \n
// fonction presentation 42 kfs de hugo et adrian




//DONE
// utils true index_vga
// color terminal et colour police en global / singleton
//clear buffer vga
//quand ligne max atteint -> clear ligne 1 puis decaler tout de une ligne
// clear line 
// advance line
