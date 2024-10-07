#include "handler.h"
#include "print.h"

void system_handler(int err_code)
{
	switch(err_code) {
		case 0:
			printk("Division by Zero\n");
			break;
		case 1:
			printk("Debug\n");
			break;
		case 2:
			printk("Non Maskable Interrupt\n");
			break;
		case 3:
			printk("Breakpoint\n");
			break;
		case 4:
			printk("Overflow\n");
			break;
		case 5:
			printk("Bound Range Exceeded\n");
			break;
		case 6:
			printk("Invalid Opcode\n");
			break;
		case 7:
			printk("Device Not Available\n");
			break;
		case 8:
			printk("Double Fault\n");
			break;
		case 10:
			printk("Invalid TSS\n");
			break;
		case 11:
			printk("Segment Not Present\n");
			break;
		case 12:
			printk("Stack-Segment Fault\n");
			break;
		case 13:
			printk("General Protection Fault\n");
			break;
		case 14:
			printk("Page Fault\n");
			break;
		default:
			printk("ISR code = undefined");
			break;
	}
}

void	exception_print()
{
	printk("In: System Exeption != 13 \n");
}

void	gp_handler()
{
	printk("In: General Protection Fault == 13\n");
}
