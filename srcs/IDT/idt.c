#include "idt.h"

void idt_set_descriptor(uint8_t vector, void *isr, uint8_t flags)
{
	idt_entry_t *descriptor = &idt[vector];

	descriptor->isr_low = (uint32_t)isr & 0xFFFF;
	descriptor->kernel_cs = 0x08; // this value can be whatever offset your kernel code selector is in your GDT
	descriptor->attributes = flags;
	descriptor->isr_high = (uint32_t)isr >> 16;
	descriptor->reserved = 0;
}

static bool vectors[IDT_MAX_DESCRIPTORS];

extern void *isr_stub_table[];

void init_idt()
{
	PIC_remap(0x20, 0x28);
	// idtr.base = (uintptr_t)&idt[0];
	// idtr.limit = (uint16_t)sizeof(idt_entry_t) * IDT_MAX_DESCRIPTORS - 1;
	//
	// for(uint8_t vector = 0; vector < 32; vector++)
	// {
	// 	idt_set_descriptor(vector, isr_stub_table[vector], 0x8E);
	// 	vectors[vector] = true;
	// }
	// Set ISRs for IRQ 0-15 (remapped to 0x20-0x2F)
	for(uint8_t vector = 0x20; vector <= 0x2F; vector++)
	{
		idt_set_descriptor(vector, isr_stub_table[vector], 0x8E);
		vectors[vector] = true;
	}
	// idt_set_descriptor(0x21, isr_stub_table[0x21], 0x8E);

	__asm__ volatile("lidt %0" : : "m"(idtr)); // load the new IDT
	__asm__ volatile("sti");		   // set the interrupt flag
}
