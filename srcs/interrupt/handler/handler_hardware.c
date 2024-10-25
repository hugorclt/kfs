#include "pic.h"
#include "printk.h"
#include "handler.h"
#include "io_port.h"
#include "pic.h"
#include "vga.h"

#define K_DATA_PORT		0x60
#define K_STATUS_PORT	0x64

char keyboard_layout_QWERTY [128] =
{
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',   
	0, /* <-- Tab */
  'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',     
    0, /* <-- control key */
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`',  0, '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/',   0,
  '*',
    0,  /* Alt */
  ' ',  /* Space bar */
    0,  /* Caps lock */
    0,  /* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,  /* < ... F10 */
    0,  /* 69 - Num lock*/
    0,  /* Scroll Lock */
    0,  /* Home key */
    0,  /* Up Arrow */
    0,  /* Page Up */
  '-',
    0,  /* Left Arrow */
    0,
    0,  /* Right Arrow */
  '+',
    0,  /* 79 - End key*/
    0,  /* Down Arrow */
    0,  /* Page Down */
    0,  /* Insert Key */
    0,  /* Delete Key */
    0,   0,   0,
    0,  /* F11 Key */
    0,  /* F12 Key */
    0,  /* All other keys are undefined */
};

char keyboard_layout_AZERTY[128] = {
    0,  27, '&', 0, '"', '\'', '(', '-', 0, '_', 0, 0, ')', '=', '\b',   
    0,   /* <-- Tab */
  'a', 'z', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '^', '$', '\n',     
    0,   /* <-- Control key */
  'q', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'm', 0, '`',   0,  '*', 'w', 'x', 'c', 'v', 'b', 'n', ',', ';', ':', '!',   0,
  '*',
    0,   /* Alt */
  ' ',   /* Space bar */
    0,   /* Caps lock */
    0,   /* 59 - F1 key ... > */
    0,    0,    0,    0,    0,    0,    0,    0,
    0,   /* < ... F10 */
    0,   /* 69 - Num lock */
    0,   /* Scroll Lock */
    0,   /* Home key */
    0,   /* Up Arrow */
    0,   /* Page Up */
  '-',
    0,   /* Left Arrow */
    0,
    0,   /* Right Arrow */
  '+',
    0,   /* 79 - End key */
    0,   /* Down Arrow */
    0,   /* Page Down */
    0,   /* Insert Key */
    0,   /* Delete Key */
    0,    0,    0,
    0,   /* F11 Key */
    0,   /* F12 Key */
    0    /* All other keys are undefined */
};

char *actual_layout = keyboard_layout_QWERTY;

char *get_actual_layout()
{
	return actual_layout;
}

void	switch_layout()
{
	printk("Keyboard switched to");
	vga_set_fg_color(VGA_COLOR_LIGHT_GREEN);
	if (actual_layout[16] == 'q')
	{
		actual_layout = keyboard_layout_AZERTY;
		printk(" azerty");
	}
	else
	{
		actual_layout = keyboard_layout_QWERTY;
		printk(" qwerty");
	}
	vga_set_fg_color(VGA_COLOR_WHITE);
	printk("\n");

}

void	hardware_handler(int code) 
{
	launch_interrupt(code);
	pic_send_eoi(code - 31);
}

void	keyboard_init()
{
	register_interrupt_handler(KEYBOARD, keyboard_handler);
}

static char	last_char = '\0';

char	get_last_char()
{
	char ret = last_char;
	last_char = '\0';
	return (ret);
}

void	keyboard_handler()
{
	// Doc: http://www.brokenthorn.com/Resources/OSDev19.html

	if (inb(K_STATUS_PORT) & 0x1)
	{
		uint8_t	scan_code = inb(K_DATA_PORT);
		if (scan_code > 127)
			return ;
		last_char = get_actual_layout()[scan_code];
	}
}
