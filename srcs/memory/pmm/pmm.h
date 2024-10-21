#pragma once

#include <stdint.h>
#include "multiboot.h"
#include <stddef.h>

extern void kernel_virtual_start(void);
extern void kernel_virtual_end(void);
extern void kernel_physical_start(void);
extern void kernel_physical_end(void);

void	print_memory_map(multiboot_info_t *bootInfo);
void	test_physical_allocator(void);

void	pmm_init(multiboot_info_t *bootInfo);
void	*pmm_allocate();
void	*pmm_allocate_blocks(size_t	n);
void	pmm_free(uintptr_t addr);


#define PAGE_FRAME_SIZE		4096// 4 KiB
#define MAX_PAGE_FRAME		1024 * 1024

#define FREE		0
#define	ALLOCATED	1
