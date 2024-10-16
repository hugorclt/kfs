#pragma once

#define PAGE_PRESENT 0x1
#define PAGE_RW 0x2
#define PAGE_USER 0x4
#define PAGE_4MB 0x80

#include <stdint.h>
#include "multiboot.h"

void print_memory_map(multiboot_info_t *bootInfo);
extern void kernel_virtual_start(void);
extern void kernel_virtual_end(void);
extern void kernel_physical_start(void);
extern void kernel_physical_end(void);

typedef struct s_page_directory
{
    uint32_t entries[1024];
} t_page_directory;


memoire_total = 32MiB
page_frame_size = 4MiB

max_page_frame = memoire_total / page_frame_size

init_bitmap() {
	bitmap[size_page_frame] = FREE

	kernel_page = ( addresse_kernel - address_multiboot_start )/ page_frame_size
	bitmap[kernel_page] = ALLOCATED
}
uintptr_t allocate_page_frame() {
	for (int i =0; i < total_pf; i++) {
		if bitmap[i] == FREE {
			bitmap[i] = ALLOCATED 
			return i * page_frame_size + address_multiboot_start
		}
		return 0
	}
}

free_page_frame(uintptr_t addr) {
	int i = (addr - multiboot_start) / page_frame_size;

	bitmap[i] = FREE;
}
