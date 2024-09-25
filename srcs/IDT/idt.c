#include "idt.h"
#include "pic.h"

idt_entry_t idt_entries[IDT_MAX_DESCRIPTORS];
idtr idt;

void handle_keyboard_interrupt()
{
	printk("oui");
	outb(PIC1_COMMAND_PORT, 0x20);
	// unsigned char scan_code = inb(0x60);
	printk("treslongstringdefouquidepasseafond");
}

void init_idt()
{
	PIC_remap(0x20, 0x28);

	unsigned int handler = (unsigned int)interrupt_handler_33;
	idt_entries[33].isr_low = handler & 0x0000FFFF; // lower 16 bits
	idt_entries[33].kernel_cs = 0x08;
	idt_entries[33].reserved = 0;
	idt_entries[33].attributes = 0x8e;
	idt_entries[33].isr_high = (handler & 0xFFFF0000) >> 16;

	idt.address = (unsigned int)&idt_entries;
	idt.size = (sizeof(idt_entry_t) * IDT_MAX_DESCRIPTORS) - 1;

	load_idt((unsigned int *)&idt);
	printk("end init");
}
