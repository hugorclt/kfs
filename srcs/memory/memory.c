#include "memory.h"
#include "printk.h"
#include "stddef.h"

void print_memory_map(multiboot_info_t *bootInfo)
{
	for (size_t i = 0; i < bootInfo->mmap_length; i += sizeof(multiboot_memory_map_t)) {
		multiboot_memory_map_t *map_entry = (multiboot_memory_map_t *)(bootInfo->mmap_addr + i);

		printk("%p - %p: %d \n", map_entry->addr_low, map_entry->len_low, map_entry->type);
		// printk("address low: %x, %x\n", map_entry->addr_low, map_entry->len_low);
		// printk("len_low: %p\n", map_entry->len_low);
		// printk("type: %d\n", map_entry->type);
		// printk("size: %d\n", map_entry->size);
	}
}
