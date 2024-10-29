#include "pmm.h"
#include "printk.h"
#include "stddef.h"
#include <stdint.h>
#include "stdbool.h"

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
	//0xC0000000 + kernelSize*512
	size_t kernel_page_index = get_page_frame_index(addr_start_kernel);
	// bitmap[kernel_page_index] = ALLOCATED;
	for (size_t i = 0; i < 1024; i++)
	{
		bitmap[kernel_page_index + i] = ALLOCATED;
	}
}

void	*pmm_allocate()
{
	for (size_t i = 0; i < total_page_frame; i++)
	{
		if (bitmap[i] == FREE)
		{
			bitmap[i] = ALLOCATED;
			return ((void*)get_page_frame_addr(i));
		}
	}
	// HANDLE ERROR: if no page left to alloc
	return (0);
}

void	*pmm_allocate_blocks(size_t	n)
{
	for (size_t i = 0; i < total_page_frame; i++)
	{
		if (bitmap[i] == FREE)
		{
			size_t	start_of_free_blocks = i;
			size_t	j = i;
			bool	array_found = false;
			while (bitmap[j] == FREE && array_found == false)
			{
				if (j - start_of_free_blocks >= n)
					array_found = true;
				j++;
			}
			if (array_found == true)
			{
				for (size_t k = start_of_free_blocks; k < n; k++)
				{
					bitmap[k] = ALLOCATED;
				}
				return ((void*)get_page_frame_addr(start_of_free_blocks));
			}
		}
	}
	return (NULL);
}

void	pmm_free(uintptr_t addr)
{
	bitmap[get_page_frame_index(addr)] = FREE;
}

void	test_physical_allocator(void)
{
	// uintptr_t addr_start_kernel = (uintptr_t) &kernel_physical_start;
	uintptr_t addr_start_kernel = (uintptr_t) 0x100000;

	printk("kernel physical start addr = %p\n", addr_start_kernel);
	size_t kernel_page_index = get_page_frame_index(addr_start_kernel);
	printk("kernel page index = %d\n", kernel_page_index);

	uintptr_t addr1 = (uintptr_t)pmm_allocate();
	uintptr_t addr2 = (uintptr_t)pmm_allocate();
	printk("total_page_frame = %d\n", total_page_frame);
	printk("addr1 = %p\n", addr1);
	printk("addr2 = %p\n", addr2);
	pmm_free(addr1);
	addr1 = (uintptr_t)pmm_allocate();
	printk("addr1 = %p\n", addr1);
	uintptr_t addr3 = (uintptr_t)pmm_allocate();
	printk("addr3 = %p\n", addr3);
	printk("\n\n");
}


void	pmm_init(multiboot_info_t *bootInfo)
{
	init_memory_var(bootInfo);
	init_bitmap();
}

size_t pmm_size(uintptr_t addr)
{
	(void)addr;
	return (4096);
}
