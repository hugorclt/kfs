#include "debug.h"
#include "commands.h"
#include "memory/memory.h"
#include "printk.h"
#include "gdt.h"
#include "idt.h"
#include "vga.h"
#include "shell.h"
#include "memory.h"
#include <stdint.h>
#include "multiboot.h"

void print_memory_map(multiboot_info_t *bootInfo)
{
	for (size_t i = 0; i < bootInfo->mmap_length; i += sizeof(multiboot_memory_map_t)) {
		multiboot_memory_map_t *map_entry = (multiboot_memory_map_t *)(bootInfo->mmap_addr + i);

		printk("%p - %p: %d (%d)\n", map_entry->addr_low, map_entry->len_low, map_entry->type, map_entry->size);
		// printk("address low: %x, %x\n", map_entry->addr_low, map_entry->len_low);
		// printk("len_low: %p\n", map_entry->len_low);
		// printk("type: %d\n", map_entry->type);
		// printk("size: %d\n", map_entry->size);
	}

}

void	kernel_main(uint32_t magic, multiboot_info_t *bootInfo) 
{	
	gdt_init();
	idt_init();

	print_memory_map(bootInfo);
	// shell();
	while(1);
}
