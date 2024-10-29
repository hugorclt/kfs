#include "debug.h"
#include "commands.h"
#include "printk.h"
#include "gdt.h"
#include "idt.h"
#include "signal/signal.h"
#include "vga.h"
#include "shell.h"
#include "pmm.h"
#include "vmm.h"
#include "multiboot.h"
#include <stdint.h>
#include "utils.h"
#include "kmalloc.h"
#include "sbrk.h"
#include "signal.h"
#include "commands.h"



void	kernel_main(uint32_t magic, multiboot_info_t *bootInfo) 
{
	(void) magic;
	gdt_init();
	idt_init();
	pmm_init(bootInfo);
	vmm_init();
	init_signal();

	test_syscall_read(1, NULL, 1090);
	// printk("%p\n", test_syscall_read);
	// shell();
	while(1);
}
