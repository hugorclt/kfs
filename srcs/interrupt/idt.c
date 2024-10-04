#include "idt.h"
#include "pic.h"
#include "print.h"
#include "io_port.h"
#include "handler.h"

__attribute__((aligned(0x10))) // aligned for performance
static t_idt_descriptor	idt[MAX_IDT_ENTRIES];
t_idtr					idtr;

static void	idt_init_descriptor(uint8_t i, uint32_t handler, uint8_t flags)
{
    t_idt_descriptor* descriptor = &idt[i];

    descriptor->i_handler_low		= (uint32_t)handler & 0xFFFF;
    descriptor->segment_selector	= 0x08; // offset code segment GDT
    descriptor->types_attributes	= flags;
    descriptor->i_handler_high		= (uint32_t)handler >> 16;
    descriptor->reserved		= 0;
}

void	idt_init(void)
{
	pic_init(0x20, 0x28);

    for (uint8_t i = 0; i < 32; i++)
	{
		if (i == 13)
        	idt_init_descriptor(i, (uint32_t) general_p_fault_wrapper, 0x8E);
		else 
        	idt_init_descriptor(i, (uint32_t) isr_stub_table[i], 0x8E);
    }

	//End of system interrupt, beginning of hardware interrupt (IRQ)
	//https://wiki.osdev.org/Interrupts

	//IRQ#0 == 32 : clock
    idt_init_descriptor(32, (uint32_t) clock_handler_wrapper, 0x8E);

	//IRQ#1 == 33 : keyboard
    idt_init_descriptor(33, (uint32_t) keyboard_handler_wrapper, 0x8E);

	idtr.size =	(uint16_t) sizeof(t_idt_descriptor) * MAX_IDT_ENTRIES - 1;
	idtr.idt =	(uintptr_t) &idt[0];

	load_idt(&idtr);
}
