#pragma once

#define PAGE_PRESENT 0x1
#define PAGE_RW 0x2
#define PAGE_USER 0x4
#define PAGE_4MB 0x80

#include <stdint.h>
#include "multiboot.h"

extern void kernel_virtual_start(void);
extern void kernel_virtual_end(void);
extern void kernel_physical_start(void);
extern void kernel_physical_end(void);

void	print_memory_map(multiboot_info_t *bootInfo);
void	init_memory(multiboot_info_t *bootInfo);

// typedef struct s_page_directory
// {
//     uint32_t entries[1024];
// } t_page_directory;


#define PAGE_FRAME_SIZE		4194304 // 4 Mib
#define MAX_PAGE_FRAME		1024

#define FREE		0
#define	ALLOCATED	1
