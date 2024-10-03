#include "idt.h"

__attribute__((aligned(0x10))) // aligned for performance
static t_idt_descriptor	idt[MAX_IDT_ENTRIES];
t_idtr					idtr;
