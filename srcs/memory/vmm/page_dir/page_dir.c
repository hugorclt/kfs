#include "page_dir.h"
#include "utils.h"
#include <stdint.h>

t_page_directory page_dir;

t_page_directory *get_page_dir()
{
	return &page_dir;
}

void	page_dir_init()
{
	memset(&(page_dir.entries), 0, PDE_MAX);
}

void	pde_add_attrib(uint32_t *entry, uint32_t flag)
{
	(*entry) = (*entry) | flag;
}

bool	pde_look_attrib(uint32_t *entry, uint32_t flag)
{
	return ((*entry & flag) == flag);
}

void	pde_add_phys_addr(uint32_t *entry, void *target)
{
	(*entry) = (target & 0xFFFFF000) | (*entry & 0x00000FFF);
}

void	pde_del_attrib(uint32_t *entry, uint32_t flag)
{
	(*entry) = (*entry) & ~flag;
}

void	pde_del_all_attrib(uint32_t *entry)
{
	(*entry) = ((*entry) & ~0x00000FFF);
}

uintptr_t pde_find_pt_addr(uint32_t *entry)
{
	return ((*entry) & 0xFFFFF000);
}

