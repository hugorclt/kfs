#include "debug.h"
#include "commands.h"
#include "printk.h"
#include "gdt.h"
#include "idt.h"
#include "vga.h"
#include "shell.h"

void	kernel_main(void) 
{
	
	gdt_init();
	idt_init();

	// shell();
	while(1);
}
