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

void* page_table_virtual_address(uint16_t page_table_number) {
  // First 10 bits are set to 1
  uint32_t virtual_address = 0xFFC00000;

  virtual_address |= (page_table_number << 12);

  return (void*) virtual_address;
}

// bool	vmm_map_page(uintptr_t physical_address, uintptr_t virtual_address)
// {
// 	printk("vmm_map_page: enter\n");
//
// 	t_page_directory *dir = get_page_dir();
// 	printk("vmm_map_page: after get_page_dir()\n");
//
//
// 	uint32_t *dir_entry = vmm_directory_lookup(dir, virtual_address);
// 	printk("dir_entry: %X\n", dir_entry);
// 	printk("page directory index: %d\n", PAGE_DIRECTORY_INDEX(virtual_address));
//
// 	if (!pde_look_attrib(dir_entry, PDE_PRESENT))
// 	{
// 		t_page_table *pt_phys = (t_page_table *)pmm_allocate();
//
// 		if (pt_phys == NULL)
// 			return (false);
//
// 		pde_add_attrib(dir_entry, PDE_PRESENT);
// 		pde_add_attrib(dir_entry, PDE_READ_WRITE);
// 		pde_add_phys_addr(dir_entry, (uint32_t)pt_phys);
// 		printk("dir_entry 2: %X\n", dir_entry);
//
// 	}
//
// 	// t_page_table *pt_phys = (t_page_table *)PAGE_GET_PHYSICAL_ADDRESS(dir_entry);
// 	t_page_table *pt_virt = (t_page_table *)page_table_virtual_address(PAGE_TABLE_INDEX(virtual_address));
// 	uint32_t *tab_entry = vmm_table_lookup(pt_virt, virtual_address);
//
// 	pte_add_attrib(tab_entry, I86_PTE_PRESENT);
// 	pte_add_phys_addr(tab_entry, physical_address);
//
// 	printk("vmm_map_page: exit\n");
//
// 	return (true);
// }

bool	vmm_map_page(uintptr_t physical_address, uintptr_t virtual_address)
{
	int dir_index = PAGE_DIRECTORY_INDEX(virtual_address);
	int table_index = PAGE_TABLE_INDEX(virtual_address);
	t_page_directory *dir = (t_page_directory *)PAGE_DIR_VIRTUAL;

	bool dir_entry_present = pde_look_attrib(&dir->entries[dir_index], PDE_PRESENT);
	uint32_t page_table_virtual = (uint32_t)PAGE_TABLE_VIRTUAL + (table_index) * PAGE_FRAME_SIZE;
	if (!dir_entry_present)
	{
		uintptr_t page_table_physique = (uintptr_t)pmm_allocate(); 

		if (!page_table_physique)
			return (false);

		//directory entry
		pde_add_attrib(&dir->entries[PAGE_DIRECTORY_INDEX(virtual_address)], PDE_PRESENT);
		pde_add_attrib(&dir->entries[PAGE_DIRECTORY_INDEX(virtual_address)], PDE_READ_WRITE);
		pde_add_phys_addr(&dir->entries[PAGE_DIRECTORY_INDEX(virtual_address)], page_table_physique);
		
	}
	pte_add_attrib(&page_table_virtual, I86_PTE_PRESENT);
	pte_add_attrib(&page_table_virtual, I86_PTE_WRITABLE);
	pte_add_phys_addr(&page_table_virtual, physical_address);	
	return (true);
}
//
bool	vmm_map_page(unsigned long phys_address, unsigned long virt_address){
	int dir_index = PAGE_DIRECTORY_INDEX(virt_address);
	int table_index = PAGE_TABLE_INDEX(virt_address);
	uint32_t *kernel_page_dir = (uint32_t *)PAGE_DIR_VIRTUAL;
    // pageinfo pginf = mm_virtaddrtopageindex(virt_address); // get the PDE and PTE indexes for the addr
     
    if(kernel_page_dir[dir_index] & 1){
        // page table exists.
        unsigned long *page_table = (unsigned long *) (0xFFC00000 + (dir_index * 0x1000)); // virt addr of page table
        if(!(page_table[table_index] & 1)){
            // page isn't mapped
            page_table[table_index] = phys_address | 3;
        }else{
            // page is already mapped
            return false;
        }
    }else{
        // doesn't exist, so alloc a page and add into pdir
        unsigned long *new_page_table = (unsigned long *) pmm_allocate();
        unsigned long *page_table = (unsigned long *) (0xFFC00000 + (dir_index * 0x1000)); // virt addr of page tbl
 
        kernel_page_dir[dir_index] = (unsigned long) new_page_table | 3; // add the new page table into the pdir
        page_table[table_index] = phys_address | 3; // map the page!
    }
    return true;
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

	//kernel map 768
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

	uint32_t *pde_recursive = &dir->entries[PAGE_DIRECTORY_INDEX(0xFFC00000)];
	pde_add_attrib(pde_recursive, PDE_PRESENT);
	pde_add_attrib(pde_recursive, PDE_READ_WRITE);
	pde_add_phys_addr(pde_recursive, (uint32_t)dir);

	enable_paging((uint32_t)dir);
	printk("pde_kernel: %X\n", pde_kernel);

}

bool	vmm_alloc_page(uintptr_t virtual_address)
{
	void *p = pmm_allocate();

	if (!p)
		return (false);

	if (!vmm_map_page((uintptr_t)p, virtual_address))
	{
		return (false);
		
	}
	
	return (true);
}
