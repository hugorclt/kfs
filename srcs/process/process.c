#include "process.h"
#include "kmalloc.h"

static inline void* get_esp(void)
{
    void* esp;
    asm volatile("mov %%esp, %0" : "=r"(esp));
    return esp;
}

static inline void* get_cr3(void)
{
    void* cr3;
    asm volatile("mov %%cr3, %0" : "=r"(cr3));
    return cr3;
}

void initialize_multitasking()
{
  process_list_head = kmalloc(sizeof(thread_control_block_t));

  process_list_head->pid = 0;
  process_list_head->esp = get_esp();
  process_list_head->esp0 = 0;
  process_list_head->cr3 = get_cr3();
  process_list_head->next = NULL;
  process_list_head->state = 0;
}
