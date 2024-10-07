#include "print.h"
#include "handler.h"
#include "io_port.h"
#include "pic.h"

#define K_DATA_PORT		0x60
#define K_STATUS_PORT	0x64

char keyboard_layout_QWERTY [128] =
{
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',   
  '\t', /* <-- Tab */
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

// static char qwerty_kb_table[128] = {
// 	0,
//     0,
//     '1',
//     '2',
//     '3',
//     '4',
//     '5',
//     '6',
//     '7',
//     '8',
//     '9',
//     '0',
//     '-',
// 	'=',
// 	'\b',           /* backspace */
// 	'\t',           /* tabulation */
//     'q',
// 	'w',
// 	'e',
// 	'r',
// 	't',
// 	'y',
// 	'u',
// 	'i',
// 	'o',
// 	'p',
// 	'[',
// 	']',
// 	'\n',           /* enter */
// 	CTRL_KEY,       /* control */
// 	'a',
//     's',
// 	'd',
// 	'f',
// 	'g',
// 	'h',
// 	'j',
// 	'k',
// 	'l',
// 	';',
// 	'\'',
// 	'`',
// 	SHIFT_KEY,       /* left shift */
// 	'\\',
// 	'z',
// 	'x',
//     'c',
// 	'v',
// 	'b',
// 	'n',
// 	'm',
// 	',',
// 	'.',
// 	'/',
// 	SHIFT_KEY,      /* right shift */
// 	'*',
// 	0,              /* alt */
// 	' ',            /* space */
// 	CAPSLOCK_KEY,   /* caps lock */
// 	0,              /* F1 */
// 	0,              /* F2 */
// 	0,              /* F3 */
// 	0,              /* F4 */
// 	0,              /* F5 */
//     0,              /* F6 */
// 	0,              /* F7 */
// 	0,              /* F8 */
// 	0,              /* F9 */
// 	0,              /* F10 */
// 	0,              /* num lock */
// 	0,              /* scroll lock */
// 	0,              /* HOME */
// 	0,              /* up arrow */
// 	0,              /* PAGEUP */
// 	'-',
// 	LEFT_ARROW_KEY, /* left arrow */
// 	0,
// 	RIGHT_ARROW_KEY,/* right arrow */
// 	'+',
// 	0,              /* END */
// 	0,              /* down arrow */
// 	0,              /* PAGEDOWN */
// 	0,              /* INSERT */
// 	0,              /* DEL */
// 	0,
// 	0,
// 	0,
// 	0,              /* F11 */
// 	0,              /* F12 */
// 	0               /* undefined keys */
// };

void	keyboard_handler()
{
	// TODO : handle on key press and ignore on key release
	// Doc: http://www.brokenthorn.com/Resources/OSDev19.html
	if (inb(K_STATUS_PORT) & 0x1)
	{
		uint8_t	scan_code = inb(K_DATA_PORT);
		if (scan_code <= 128)
		{
			char	str[2];
			str[0] = keyboard_layout_QWERTY[scan_code];
			str[1] = '\0';
			printk(str);
		}
		pic_send_eoi(KEYBOARD_IRQ);
		
	}
}

void	clock_handler()
{
		pic_send_eoi(CLOCK_IRQ);
}
