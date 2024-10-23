#include "vmm.h"
#include "page_tab/page_table.h"
#include "pmm.h"
#include "page_dir.h"
#include "page_table.h"
#include <stdint.h>
#include <stdbool.h>
#include "utils.h"
#include "printk.h"

// bool	vmm_alloc_page(uintptr_t *entry)
// {
// 	void *p = pmm_allocate();
//
// 	if (!p)
// 		return (false);
//
// 	pte_add_phys_addr(entry, (uintptr_t)p);
// 	pte_add_attrib(entry, I86_PTE_WRITABLE);
// 	pte_add_attrib(entry, I86_PTE_PRESENT);
// 	return (true);
// }

void	vmm_free_page(uint32_t *entry)
{
	void *p = (void *)pte_find_phys_addr(entry);
	if (p)
		pmm_free((uintptr_t)p);

	pte_del_all_attrib(entry);
}

uint32_t *vmm_table_lookup(t_page_table *page_table, uintptr_t virtual_addr)
{
	if (page_table)
		return &(page_table->entries[PAGE_TABLE_INDEX(virtual_addr)]);
	return (NULL);
}

uint32_t *vmm_directory_lookup(t_page_directory *page_directory, uintptr_t virtual_addr)
{
	if (page_directory)
		return &(page_directory->entries[PAGE_DIRECTORY_INDEX(virtual_addr)]);
	return (NULL);
}

bool	vmm_map_page(uintptr_t physical_address, uintptr_t virtual_address)
{
	t_page_directory *dir = get_page_dir();

	uint32_t *dir_entry = vmm_directory_lookup(dir, virtual_address);
	if (!pde_look_attrib(dir_entry, PDE_PRESENT))
	{
		t_page_table *pt_phys = (t_page_table *)pmm_allocate();
		if (pt_phys == NULL)
			return (false);

		pde_add_attrib(dir_entry, PDE_PRESENT);
		pde_add_attrib(dir_entry, PDE_READ_WRITE);
		pde_add_phys_addr(dir_entry, (uint32_t)pt_phys);		
	}

	t_page_table *pt_phys = (t_page_table *)PAGE_GET_PHYSICAL_ADDRESS(dir_entry);
	uint32_t *tab_entry = vmm_table_lookup(pt_phys, virtual_address);

	pte_add_attrib(tab_entry, I86_PTE_PRESENT);
	pte_add_phys_addr(tab_entry, physical_address);
	return (true);
}

void	vmm_init()
{
	t_page_table *identity_page = pmm_allocate();
	if (!identity_page)
	{
		printk("Out of Memory\n");
		return ;
	}

	t_page_table *kernel_page = pmm_allocate();
	if (!kernel_page)
	{
		printk("Out of Memory\n");
		return ;
	}

	memset(identity_page, 0, sizeof(t_page_table));
	memset(kernel_page, 0, sizeof(t_page_table));

	// Identity mapping
	for (size_t i = 0, frame=0x0, virt=0x0; i < 1024; i++, frame += 4096, virt += 4096)
	{
		uint32_t page = 0;
		pte_add_attrib(&page, I86_PTE_PRESENT);
		pte_add_phys_addr(&page, frame);

		identity_page->entries[PAGE_TABLE_INDEX(virt)] = page;
	}

	//kernel map 7768
	for (size_t i = 0, frame=0x000000, virt=0xC0000000; i < 1024; i++, frame += 4096, virt += 4096)
	{
		uint32_t page = 0;
		pte_add_attrib(&page, I86_PTE_PRESENT);
		pte_add_phys_addr(&page, frame);

		kernel_page->entries[PAGE_TABLE_INDEX(virt)] = page;
	}
	
	t_page_directory *dir = pmm_allocate_blocks(3);
	if (!dir)
	{
		printk("Out of Memory\n");
		return ;
	}


	memset(dir, 0, sizeof(t_page_directory));

	uint32_t *pde_identity = &dir->entries[PAGE_DIRECTORY_INDEX(0x0)];
	pde_add_attrib(pde_identity, PDE_PRESENT);
	pde_add_attrib(pde_identity, PDE_READ_WRITE);
	pde_add_phys_addr(pde_identity, (uint32_t)identity_page);

	uint32_t *pde_kernel = &dir->entries[PAGE_DIRECTORY_INDEX(0xc0000000)];
	pde_add_attrib(pde_kernel, PDE_PRESENT);
	pde_add_attrib(pde_kernel, PDE_READ_WRITE);
	pde_add_phys_addr(pde_kernel, (uint32_t)kernel_page);

	enable_paging((uint32_t)dir);
}

bool	vmm_alloc_page(uintptr_t virtual_address)
{
	void *p = pmm_allocate();
	if (!p)
		return (false);

	if (!vmm_map_page((uintptr_t)p, virtual_address))
		return (false);
	return (true);
}
