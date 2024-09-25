#pragma once

#include "pic.h"
#include "print.h"
#include <stdbool.h>
#include <stdint.h>

#define IDT_MAX_DESCRIPTORS 256
#define INTERRUPT_KEYBOARD 33

// ASM function
void load_idt(unsigned int *idt_address);
void interrupt_handler_33();
void segments_load_registers();

typedef struct {
	uint16_t isr_low;   // The lower 16 bits of the ISR's address
	uint16_t kernel_cs; // The GDT segment selector that the CPU will load into CS before calling the ISR
	uint8_t reserved;   // Set to zero
	uint8_t attributes; // Type and attributes; see the IDT page
	uint16_t isr_high;  // The higher 16 bits of the ISR's address
} __attribute__((packed)) idt_entry_t;

typedef struct {
	unsigned short size;
	unsigned int address;
} __attribute__((packed)) idtr;

struct cpu_state {
	/* the state of the registers */
	unsigned int eax;
	unsigned int ebx;
	unsigned int ecx;
	unsigned int edx;
	unsigned int ebp;
	unsigned int esi;
	unsigned int edi;
} __attribute__((packed));

struct stack_state {
	/* the state of the stack */
	unsigned int error_code;
	unsigned int eip;
	unsigned int cs;
	unsigned int eflags;
} __attribute__((packed));

void handle_keyboard_interrupt();
void init_idt();
