#include "memory.h"
#include "printk.h"
#include "stddef.h"

uint32_t	total_page_frame;
uintptr_t	start_physical_memory;

uint8_t		bitmap[MAX_PAGE_FRAME];

void print_memory_map(multiboot_info_t *bootInfo)
{
	for (size_t i = 0; i < bootInfo->mmap_length; i += sizeof(multiboot_memory_map_t)) {
		multiboot_memory_map_t *map_entry = (multiboot_memory_map_t *)(bootInfo->mmap_addr + i);

		printk("%p - %p: %d \n", map_entry->addr_low, map_entry->len_low, map_entry->type);
	}
	unsigned int vaddr = (unsigned int) &kernel_virtual_start;
	unsigned int vend = (unsigned int) &kernel_virtual_end;

	printk("kernel_virtual_start = %p\nkernel_virtual_end = %p\n", vaddr, vend);
}

void	init_memory_var(multiboot_info_t *bootInfo)
{
	for (size_t i = 0; i < bootInfo->mmap_length; i += sizeof(multiboot_memory_map_t)) {
		if (i == 0)
			continue ;

		multiboot_memory_map_t *map_entry = (multiboot_memory_map_t *)(bootInfo->mmap_addr + i);
		if (map_entry->type == MULTIBOOT_MEMORY_AVAILABLE)
		{
			start_physical_memory = map_entry->addr_low;
			total_page_frame = map_entry->len_low / PAGE_FRAME_SIZE;
			return ;
		}		
	}
	// TO DO : ADD PANIC HANDLER IN CASE OF GRUB ERROR
}

size_t	get_page_frame_index(uintptr_t addr)
{
	size_t index = ( addr - start_physical_memory ) / PAGE_FRAME_SIZE;
	return (index);
}

uintptr_t	get_page_frame_addr(size_t index)
{
	return (index * PAGE_FRAME_SIZE + start_physical_memory);

}

static void	init_bitmap()
{
	for (size_t i = 0; i < total_page_frame; i++)
	{
		bitmap[i] = FREE;
	}
	uintptr_t addr_start_kernel = (uintptr_t) &kernel_physical_start;
	size_t kernel_page_index = get_page_frame_index(addr_start_kernel);
	bitmap[kernel_page_index] = ALLOCATED;
}

static uintptr_t	allocate_page_frame()
{
	for (size_t i = 0; i < total_page_frame; i++)
	{
		if (bitmap[i] == FREE)
		{
			bitmap[i] = ALLOCATED;
			return (get_page_frame_addr(i));
		}
	}
	// HANDLE ERROR: if no page left to alloc
	return (0);
}

void	free_page_frame(uintptr_t addr)
{
	bitmap[get_page_frame_index(addr)] = FREE;
}

void	test_physical_allocator(void)
{
	uintptr_t addr_start_kernel = (uintptr_t) &kernel_physical_start;
	printk("kernel physical start addr = %p\n", addr_start_kernel);
	size_t kernel_page_index = get_page_frame_index(addr_start_kernel);
	printk("kernel page index = %d\n", kernel_page_index);

	uintptr_t addr1 = allocate_page_frame();
	uintptr_t addr2 = allocate_page_frame();
	printk("total_page_frame = %d\n", total_page_frame);
	printk("addr1 = %p\n", addr1);
	printk("addr2 = %p\n", addr2);
	free_page_frame(addr1);
	addr1 = allocate_page_frame();
	printk("addr1 = %p\n", addr1);
	uintptr_t addr3 = allocate_page_frame();
	printk("addr3 = %p\n", addr3);
	printk("\n\n");
}

void	init_memory(multiboot_info_t *bootInfo)
{
	init_memory_var(bootInfo);
	init_bitmap();
}
