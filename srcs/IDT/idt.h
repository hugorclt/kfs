#pragma once

#include "pic.h"
#include <stdbool.h>
#include <stdint.h>

#define IDT_MAX_DESCRIPTORS 256

typedef struct {
	uint16_t isr_low;   // The lower 16 bits of the ISR's address
	uint16_t kernel_cs; // The GDT segment selector that the CPU will load into CS before calling the ISR
	uint8_t reserved;   // Set to zero
	uint8_t attributes; // Type and attributes; see the IDT page
	uint16_t isr_high;  // The higher 16 bits of the ISR's address
} __attribute__((packed)) idt_entry_t;

typedef struct {
	uint16_t limit;
	uint32_t base;
} __attribute__((packed)) idtr_t;

__attribute__((aligned(0x10))) static idt_entry_t idt[256];
static idtr_t idtr;

void init_idt();
