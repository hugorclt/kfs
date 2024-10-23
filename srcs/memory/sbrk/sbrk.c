#include "sbrk.h"
#include "pmm.h"
#include "stddef.h"
#include "vmm.h"
#include <stdint.h>
#include "printk.h"

uintptr_t heap_start = 0xC0400000;
size_t heap_end = 0xEFFFFFFF;
size_t heap_used = 0;


void *sbrk(size_t size)
{
	printk("sbrk: enter\n");

	// Not enough space
	int nb_page_to_allocate = (size / PAGE_FRAME_SIZE) + 1;

	if (heap_start + heap_used + nb_page_to_allocate * PAGE_FRAME_SIZE > heap_end)
	{
		printk("brk: error1\n");
		return NULL;
	}

	for (int i = 0; i < nb_page_to_allocate; i++)
	{
		printk("sbrk: allocate a page\n");

		if (!vmm_alloc_page(heap_start + heap_used + PAGE_FRAME_SIZE * i))
		{
			printk("brk: error2\n");
			return (NULL);
		}
	}
	printk("brk: exit for loop\n");

	uintptr_t start_block = heap_start + heap_used;
	heap_used += nb_page_to_allocate * PAGE_FRAME_SIZE;
	printk("sbrk: exit\n");
	return ((void *)start_block);
}
