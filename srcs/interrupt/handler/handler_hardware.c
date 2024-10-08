#include "pic.h"
#include "printk.h"
#include "handler.h"
#include "io_port.h"
#include "pic.h"
#include "printk.h"
#include "utils.h"
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

void	hardware_handler(int code) 
{
	launch_interrupt(code);
	pic_send_eoi(code - 31);
}

void	keyboard_init()
{
	register_interrupt_handler(KEYBOARD, keyboard_handler);
}

char	stdin[128] = {0};

char*	get_stdin(void)
{
	if (stdin[strlen(stdin) - 1] == '\n')
	{
		stdin[strlen(stdin) - 1] = '\0';
		return (stdin);
	}
	else
		return (NULL);
}

void	clean_stdin(void)
{
	memset(&stdin, '\0', strlen(stdin));
}

static void	write_stdin(char c)
{
	if (c == '\b')
	{
		stdin[strlen(stdin) - 1] = '\0';
	}
	else
	{
		stdin[strlen(stdin)] = c;
		stdin[strlen(stdin) + 1] = '\0';
	}
}

static void	write_vga(char c, uint8_t scan_code)
{
	if (c == '\b')
		vga_erase_last_char();
	if (scan_code <= 127 && c != '\0' && c != '\b')
		printk("%c", c);
}

void	keyboard_handler()
{
	// Doc: http://www.brokenthorn.com/Resources/OSDev19.html

	if (inb(K_STATUS_PORT) & 0x1)
	{
		uint8_t	scan_code = inb(K_DATA_PORT);
		char	c = keyboard_layout_QWERTY[scan_code];

		write_vga(c, scan_code);
		write_stdin(c);	
	}
}
