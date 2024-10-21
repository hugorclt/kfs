#include "debug.h"
#include "commands.h"
#include "printk.h"
#include "gdt.h"
#include "idt.h"
#include "vga.h"
#include "shell.h"
#include "pmm.h"
#include "multiboot.h"
#include <stdint.h>

#define CEIL_DIV(a,b) (((a + b) - 1) / b)

void	kernel_main(uint32_t magic, multiboot_info_t *bootInfo) 
{
	(void) magic;
	gdt_init();
	idt_init();


	// shell();
	while(1);
}
