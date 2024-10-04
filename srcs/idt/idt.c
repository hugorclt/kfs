#include "idt.h"
#include "idt/pic/pic.h"
#include "print.h"

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

void	keyboard_handler()
{
	printk("Hello, Keyboard\n");
	pic_send_eoi(KEYBOARD_IRQ);
}

void	clock_handler()
{
	// printk("In: Clock handler\n");
	pic_send_eoi(CLOCK_IRQ);
}

void	exception_print()
{
	printk("In: System Exeption != 13 \n");
}

void gp_handler()
{
	printk("In: General Protection Fault == 13\n");
}

void	idt_init(void)
{
	pic_init(0x20, 0x28);

    for (uint8_t i = 0; i < 32; i++)
	{
		if (i == 13)
        	idt_init_descriptor(i, general_p_fault_wrapper, 0x8E);
		else 
        	idt_init_descriptor(i, isr_stub_table[i], 0x8E);
    }

	//End of system interrupt, beginning of hardware interrupt (IRQ)
	//https://wiki.osdev.org/Interrupts

	//IRQ#0 == 32 : clock
    idt_init_descriptor(32, clock_handler_wrapper, 0x8E);


	//IRQ#1 == 33 : keyboard
    idt_init_descriptor(33, keyboard_handler_wrapper, 0x8E);

	idtr.size =	(uint16_t) sizeof(t_idt_descriptor) * MAX_IDT_ENTRIES - 1;
	idtr.idt =	(uintptr_t) &idt[0];

	load_idt(&idtr);
}
