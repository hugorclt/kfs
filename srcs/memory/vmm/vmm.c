#include "vmm.h"
#include "page_tab/page_table.h"
#include "pmm.h"
#include "page_dir.h"
#include "page_table.h"
#include <stdint.h>
#include <stdbool.h>
#include "utils.h"
#include "printk.h"
#include "commands.h"


void vmm_print_mapping(uintptr_t vaddr)
{
    uint32_t *page_dir = (uint32_t *)PAGE_DIR_VIRTUAL;
    int dir_index = PAGE_DIRECTORY_INDEX(vaddr);
    int table_index = PAGE_TABLE_INDEX(vaddr);
    
    printk("\n=== Mapping info for virtual address 0x%x ===\n", vaddr);
    printk("Directory index: %d, Table index: %d\n", dir_index, table_index);
    
    uint32_t pde = page_dir[dir_index];
    printk("PDE[%d] = 0x%x\n", dir_index, pde);
    
    if (!(pde & PDE_PRESENT)) {
        printk("  -> Page table NOT PRESENT\n");
        return;
    }
    
    printk("  -> Page table is PRESENT\n");
    printk("  -> Physical address of page table: 0x%x\n", pde & 0xFFFFF000);
    printk("  -> Flags: %s%s%s\n",
           (pde & PDE_PRESENT) ? "PRESENT " : "",
           (pde & PDE_READ_WRITE) ? "RW " : "RO ",
           (pde & PDE_USER) ? "USER" : "SUPERVISOR");
    
    uint32_t *page_table = (uint32_t *)(PAGE_TABLE_VIRTUAL + (dir_index * PAGE_FRAME_SIZE));
    uint32_t pte = page_table[table_index];
    
    printk("PTE[%d] = 0x%x\n", table_index, pte);
    
    if (!(pte & I86_PTE_PRESENT)) {
        printk("  -> Page NOT MAPPED\n");
        return;
    }
    
    printk("  -> Page is MAPPED\n");
    printk("  -> Physical address: 0x%x\n", pte & 0xFFFFF000);
    printk("  -> Flags: %s%s%s\n",
           (pte & I86_PTE_PRESENT) ? "PRESENT " : "",
           (pte & I86_PTE_WRITABLE) ? "RW " : "RO ",
           (pte & I86_PTE_USER) ? "USER" : "SUPERVISOR");
}

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

bool vmm_is_mapped(uintptr_t virtual_address) {
    uint32_t *pde = vmm_directory_lookup((t_page_directory *)PAGE_DIR_VIRTUAL, virtual_address);

    if (!pde || !(*pde & PDE_PRESENT)) {
        return false;
    }

    uint32_t dir_index = PAGE_DIRECTORY_INDEX(virtual_address);
    t_page_table *ptbl = (t_page_table *)(PAGE_TABLE_VIRTUAL + (dir_index * 0x1000));
    
    uint32_t *pte = vmm_table_lookup(ptbl, virtual_address);
    return (pte && (*pte & I86_PTE_PRESENT));
}


bool	vmm_map_page(unsigned long physical_address, unsigned long virtual_address)
{
	int dir_index = PAGE_DIRECTORY_INDEX(virtual_address);
	int table_index = PAGE_TABLE_INDEX(virtual_address);

	uint32_t *kernel_page_dir = (uint32_t *)PAGE_DIR_VIRTUAL;
     
    if(kernel_page_dir[dir_index] & 1){
        unsigned long *page_table = (unsigned long *) (0xFFC00000 + (dir_index * 0x1000)); // virt addr of page table
        if(!(page_table[table_index] & 1)){
            page_table[table_index] = physical_address | 3;
            return true;
        }else{
            return false;
        }
    }
  unsigned long *new_page_table = (unsigned long *) pmm_allocate();
  unsigned long *page_table = (unsigned long *) (0xFFC00000 + (dir_index * 0x1000)); // virt addr of page tbl
 
  kernel_page_dir[dir_index] = (unsigned long) new_page_table | 3; // add the new page table into the pdir
  page_table[table_index] = physical_address | 3; // map the page!
  return true;
}

void	vmm_init()
{
	uint32_t identity_page_phys = (uint32_t)pmm_allocate();
  uint32_t kernel_page_phys = (uint32_t)pmm_allocate();
	
  t_page_table *identity_page = (t_page_table *)identity_page_phys;
  t_page_table *kernel_page = (t_page_table *)kernel_page_phys;

	memset(identity_page, 0, sizeof(t_page_table));
	memset(kernel_page, 0, sizeof(t_page_table));

	for (size_t i = 0, frame=0x0, virt=0x0; i < 1024; i++, frame += 4096, virt += 4096)
	{
		uint32_t page = 0;
		pte_add_attrib(&page, I86_PTE_PRESENT);
		pte_add_attrib(&page, I86_PTE_WRITABLE);
		pte_add_phys_addr(&page, frame);

		identity_page->entries[PAGE_TABLE_INDEX(virt)] = page;
	}

	for (size_t i = 0, frame=0x000000, virt=0xC0000000; i < 1024; i++, frame += 4096, virt += 4096)
	{
		uint32_t page = 0;
		pte_add_attrib(&page, I86_PTE_PRESENT);
		pte_add_attrib(&page, I86_PTE_WRITABLE);
		pte_add_phys_addr(&page, frame);

		kernel_page->entries[PAGE_TABLE_INDEX(virt)] = page;
	}
	
	uint32_t dir_phys = (uint32_t)pmm_allocate();
  t_page_directory *dir = (t_page_directory *)dir_phys;

	memset(dir, 0, sizeof(t_page_directory));

	uint32_t *pde_identity = &dir->entries[PAGE_DIRECTORY_INDEX(0x0)];
	pde_add_attrib(pde_identity, PDE_PRESENT);
	pde_add_attrib(pde_identity, PDE_READ_WRITE);
	pde_add_phys_addr(pde_identity, identity_page_phys);

	uint32_t *pde_kernel = &dir->entries[PAGE_DIRECTORY_INDEX(0xc0000000)];
	pde_add_attrib(pde_kernel, PDE_PRESENT);
	pde_add_attrib(pde_kernel, PDE_READ_WRITE);
	pde_add_phys_addr(pde_kernel, kernel_page_phys);
	
	uint32_t *pde_recursive = &dir->entries[1023];
	pde_add_attrib(pde_recursive, PDE_PRESENT);
	pde_add_attrib(pde_recursive, PDE_READ_WRITE);
	pde_add_phys_addr(pde_recursive, dir_phys);
  
	enable_paging((uint32_t)dir);
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
