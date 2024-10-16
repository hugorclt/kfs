#include "debug.h"
#include "commands.h"
#include "printk.h"
#include "gdt.h"
#include "idt.h"
#include "vga.h"
#include "shell.h"
#include "memory.h"
#include "multiboot.h"

void	kernel_main(uint32_t magic, multiboot_info_t *bootInfo) 
{
	(void) magic;
	gdt_init();
	idt_init();
	init_memory(bootInfo);

	// shell();
	while(1);
}
