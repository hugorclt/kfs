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
	(void) bootInfo;
	gdt_init();

	printk("before pmm init\n");
	
	pmm_init(bootInfo);
	printk("after pmm init\n");

	printk("\n------- Memory Map ---------\n");
	print_memory_map(bootInfo);
	printk("----------------------------\n");


	printk("before vmm init\n");
	vmm_init();
	printk("after vmm init\n");

	idt_init();

	shell();

	
	while(1);
}
