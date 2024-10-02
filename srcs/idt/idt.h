#pragma once

#include "stdint.h"

#define MAX_IDT_ENTRIES 255

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

t_idtr			idtr;
t_idt_descriptor	idt[MAX_IDT_ENTRIES];
