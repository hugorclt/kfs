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
#include "utils.h"
#include "kmalloc.h"

void	kernel_main(uint32_t magic, multiboot_info_t *bootInfo) 
{
	(void) magic;
	gdt_init();
	pmm_init(bootInfo);
	vmm_init();
	idt_init();
	// print_memory_map(bootInfo);


	// shell();
	char *str = (char *) kmalloc(10 * sizeof(char));
	if (!str)
		printk("malloc casse\n");
	// printk("str addrr = %p\n", str);
	for (size_t i = 0; i < 9; i++)
	{
		str[i] = 'A';
	}
	str[9] = '\0';
	// printk("%s\n", str);

	// kfree(str);


	printk("infinite loop \n");
	while(1);
}
