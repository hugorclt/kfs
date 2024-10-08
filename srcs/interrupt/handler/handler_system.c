#include "handler.h"
#include "printk.h"

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
		case 16:
			printk("Floating Point Exception\n");
			break;
		case 17:
			printk("Alignement Check\n");
			break;
		case 18:
			printk("Machine check\n");
			break;
		case 19:
			printk("SIMD Floating Point Exception\n");
			break;
		case 20:
			printk("Virtualization Exception\n");
			break;
		case 21:
			printk("Hypervisor Injection Exception\n");
			break;
		case 28:
			printk("VMM Communication Exception\n");
			break;
		case 29:
			printk("Security Exception\n");
			break;
		default:
			printk("ISR code = RESERVED\n");
			break;
	}
}
