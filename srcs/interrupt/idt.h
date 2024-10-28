#pragma once

#include <stdint.h>

#define MAX_IDT_ENTRIES 256
#define SYSCALL_INDEX_IDT 0x80

typedef struct __attribute__((packed)) s_idtr {
	uint16_t	size;
	uint32_t	idt;
}	t_idtr;

typedef struct __attribute__((packed)) s_idt_descriptor {
	uint16_t	i_handler_low;
	uint16_t	segment_selector;
	uint8_t		reserved; // always zero
	uint8_t		types_attributes; // Gate type | DPL (ring) | P (present bit: 1)
	uint16_t	i_handler_high;
}	t_idt_descriptor;

extern void*	system_isr_stub_table[];	//system interrupt
extern void*	hardware_isr_stub_table[];	//hardware interrupt
extern void*	syscall_handler_wrapper;
extern void		load_idt(t_idtr *idtr);

void	idt_init(void);
