#include "pic.h"
#include "print.h"
#include "handler.h"
#include "io_port.h"


void	hardware_handler(int code) 
{
	printkhex(code);
	printk("\n");
	launch_interrupt(code);
	pic_send_eoi(code - 31);

}

void	keyboard_init()
{
	register_interrupt_handler(KEYBOARD, keyboard_handler);
}

void	keyboard_handler()
{
	// TODO : handle on key press and ignore on key release

	printk("Hello, Keyboard\n");
	 unsigned char scan_code = inb(0x60);
	 (void)scan_code;
}

void	clock_handler()
{
	// printk("In: Clock handler\n");
}
