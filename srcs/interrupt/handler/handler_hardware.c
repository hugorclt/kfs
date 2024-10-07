#include "print.h"
#include "handler.h"
#include "io_port.h"
#include "../pic/pic.h"

void	keyboard_handler()
{
	// TODO : handle on key press and ignore on key release

	printk("Hello, Keyboard\n");
	 unsigned char scan_code = inb(0x60);
	 (void)scan_code;
	pic_send_eoi(KEYBOARD_IRQ);
}

void	clock_handler()
{
	// printk("In: Clock handler\n");
	pic_send_eoi(CLOCK_IRQ);
}
