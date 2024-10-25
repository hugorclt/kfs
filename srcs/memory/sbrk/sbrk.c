#include "sbrk.h"
#include "pmm.h"
#include "stddef.h"
#include "vmm.h"
#include <stdint.h>
#include "printk.h"

size_t heap_used = 0;

void *sbrk(size_t size)
{
	int nb_page_to_allocate = (size / PAGE_FRAME_SIZE) + 1;


	if (HEAP_START + heap_used + nb_page_to_allocate * PAGE_FRAME_SIZE > HEAP_END)
		return NULL;

	uintptr_t start_block = HEAP_START + heap_used;
	heap_used += nb_page_to_allocate * PAGE_FRAME_SIZE;
	return ((void *)start_block);
}
