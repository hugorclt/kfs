#include "idt.h"

__attribute__((aligned(0x10))) // aligned for performance
static t_idt_descriptor	idt[MAX_IDT_ENTRIES];
t_idtr					idtr;

static void	idt_init_descriptor(uint8_t i, void* handler, uint8_t flags)
{
    t_idt_descriptor* descriptor = &idt[i];

    descriptor->i_handler_low		= (uint32_t)handler & 0xFFFF;
    descriptor->segment_selector	= 0x08; // offset code segment GDT
    descriptor->types_attributes	= flags;
    descriptor->i_handler_high		= (uint32_t)handler >> 16;
}



void	idt_init(void)
{
    for (uint8_t i = 0; i < 32; i++)
	{
        idt_init_descriptor(i, isr_stub_table[i], 0x8E);
    }

    idtr.size =	(uint16_t) sizeof(t_idt_descriptor) * MAX_IDT_ENTRIES - 1;
	idtr.idt =	(uintptr_t) &idt[0];

	load_idt(&idtr);
}
