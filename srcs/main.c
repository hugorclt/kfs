#include <vga.h>



void kernel_main(void) 
{
	// vga_set_fg_color(VGA_COLOR_WHITE);
	// vga_set_bg_color(VGA_COLOR_BLACK);

	for (int y = 0; y < 26; y++) 
	{
		for (int x = 0; x < 80; x++)
		{
			vga_write_buffer('a' + y);
		}
	}
}

// To do
// utils strlen
// printkf -> similair a printf
// gestion \b, \r, \t
// color terminal et colour police en global / singleton
// %d, %i, %s, %X, %p
//clear buffer vga
//quand ligne max atteint -> clear ligne 1 puis decaler tout de une ligne


//DONE
// utils true index_vga

//todo
// clear line 
// advance line
