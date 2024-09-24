#include "idt.h"
#include "print.h"

__attribute__((noreturn)) void exception_handler()
{
	printk("test");
	__asm__ volatile("cli; hlt"); // Completely hangs the computer
}
