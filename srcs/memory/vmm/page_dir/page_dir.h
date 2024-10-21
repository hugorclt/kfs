#pragma once

#include <stdint.h>
#include <stdbool.h>
typedef enum {
    PDE_PRESENT       = 0x01,
    PDE_READ_WRITE    = 0x02,
    PDE_USER          = 0x04,
    PDE_WRITE_THROUGH = 0x08,
    PDE_CACHE_DISABLE = 0x10,
    PDE_ACCESSED      = 0x20,
    PDE_DIRTY         = 0x40,          // 4MB entry only
    PDE_PAGE_SIZE     = 0x80,          // 0 = 4KB page, 1 = 4MB page
    PDE_GLOBAL        = 0x100,         // 4MB entry only
    PDE_PAT           = 0x2000,        // 4MB entry only
    PDE_FRAME         = 0x7FFFF000,    // bits 12+
} PAGE_DIR_FLAGS;


#define PDE_MAX 1024

typedef struct s_page_directory {
	uint32_t entries[PDE_MAX];
} t_page_directory;

void	page_dir_init();
t_page_directory *get_page_dir();
void	pde_add_attrib(uint32_t *entry, uint32_t flag);
void	pde_add_phys_addr(uint32_t *entry, uint32_t target);
void	pde_del_attrib(uint32_t *entry, uint32_t flag);
uintptr_t pde_find_find_addr(uint32_t *entry);
bool	pde_look_attrib(uint32_t *entry, uint32_t flag);
