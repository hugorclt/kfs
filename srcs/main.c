#include <vga.h>



void kernel_main(void) 
{
	// vga_set_fg_color(VGA_COLOR_WHITE);
	// vga_set_bg_color(VGA_COLOR_BLACK);

	for(size_t i = 0; i < 1999; i++)
	{
		vga_write_buffer('A');
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
