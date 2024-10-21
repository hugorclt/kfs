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
	(void) magic;
	gdt_init();
	pmm_init(bootInfo);
	print_memory_map(bootInfo);
	vmm_init();
	idt_init();

	shell();

	while(1);
}
