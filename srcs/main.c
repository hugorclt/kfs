#include "debug.h"
#include "commands.h"
#include "printk.h"
#include "gdt.h"
#include "idt.h"
#include "vga.h"
#include "shell.h"
#include "pmm.h"
#include "vmm.h"
#include "multiboot.h"
#include <stdint.h>

void	kernel_main(uint32_t magic, multiboot_info_t *bootInfo) 
{
	pmm_init(bootInfo);
	vmm_init();
	(void) magic;
	(void) bootInfo;
	gdt_init();
	idt_init();
	
	shell();

	// shell();
	while(1);
}
