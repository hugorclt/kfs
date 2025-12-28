#include "sbrk.h"
#include "pmm.h"
#include "stddef.h"
#include "vmm.h"
#include <stdint.h>
#include "printk.h"

size_t heap_used = 0;

void *sbrk(size_t size)
{
  uintptr_t old_heap_top = HEAP_START + heap_used;
  uintptr_t new_heap_top = old_heap_top + size;

  if (new_heap_top > HEAP_END)
    return NULL;

  uintptr_t current_page = (old_heap_top & ~(PAGE_FRAME_SIZE - 1));
  for (uintptr_t addr = current_page; addr < new_heap_top; addr += PAGE_FRAME_SIZE)
  {
    if (vmm_is_mapped(addr) == false)
    {
      vmm_alloc_page(addr);
    }
  }
  heap_used += size; 
  return (void *)old_heap_top;
}
