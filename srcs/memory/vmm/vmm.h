#pragma once

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#define PAGE_DIRECTORY_INDEX(x) (((x) >> 22) & 0x3ff)
#define PAGE_TABLE_INDEX(x) (((x) >> 12) & 0x3ff)
#define PAGE_GET_PHYSICAL_ADDRESS(x) (*x & ~0xfff)

extern void flush_tlb_entry(uint32_t entry);
// extern void enable_paging(bool enable, uint32_t dir);
extern void enable_paging(uint32_t dir);
bool	vmm_alloc_page(uintptr_t virtual_address);


void		vmm_init();
