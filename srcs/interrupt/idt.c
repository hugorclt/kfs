#include "idt.h"
#include "pic.h"
#include "printk.h"
#include "io_port.h"
#include "handler.h"
#include <stdint.h>
#include "utils.h"

__attribute__((aligned(0x10))) // aligned for performance
	static t_idt_descriptor	idt[MAX_IDT_ENTRIES];
	t_idtr					idtr;

void syscall_handler(t_register register_state)
{

}

static void	idt_init_descriptor(uint8_t i, uint32_t handler, uint8_t flags)
{
	t_idt_descriptor* descriptor = &idt[i];

	descriptor->i_handler_low		= (uint32_t)handler & 0xFFFF;
	descriptor->segment_selector	= 0x08; // offset code segment GDT
	descriptor->types_attributes	= flags;
	descriptor->i_handler_high		= (uint32_t)handler >> 16;
	descriptor->reserved			= 0;
}

void	idt_init(void)
{
	idtr.size =	(uint16_t) sizeof(t_idt_descriptor) * MAX_IDT_ENTRIES - 1;
	idtr.idt =	(uintptr_t) &idt[0];
	memset(&idt, 0, sizeof(t_idt_descriptor) * MAX_IDT_ENTRIES);
	
	pic_init(0x20, 0x28);

	for (uint8_t i = 0; i < 32; i++)
		idt_init_descriptor(i, (uint32_t) system_isr_stub_table[i], 0x8E);
	for (uint8_t i = 0; i < 16; i++)
		idt_init_descriptor(i + 32, (uint32_t) hardware_isr_stub_table[i], 0x8E);
	idt_init_descriptor(0x80, (uint32_t)syscall_handler_wrapper, 0x8E | (3 << 5));

	

	interrupt_handlers_init();
	keyboard_init();
	load_idt(&idtr);
}
