#include "page_table.h"
#include "utils.h"
#include <stdint.h>

t_page_table page_table;

t_page_table get_page_table()
{
	return page_table;
}

void	page_table_init()
{
	memset(&(page_table.entries), 0, PTE_MAX);
}

void	pte_add_attrib(uint32_t *entry, uint32_t flag)
{
	(*entry) = (*entry) | flag;
}

void	pte_del_attrib(uint32_t *entry, uint32_t flag)
{
	(*entry) = (*entry) & ~flag;
}

void	pte_del_all_attrib(uint32_t *entry)
{
	(*entry) = ((*entry) & ~0x00000FFF);
}

void	pte_add_phys_addr(uint32_t *entry, uint32_t target)
{
	(*entry) = (target & 0xFFFFF000) | (*entry & 0x00000FFF);
}

uintptr_t pte_find_phys_addr(uint32_t *entry)
{
	return ((*entry) & 0xFFFFF000);
}
