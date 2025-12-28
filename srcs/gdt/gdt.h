#pragma once

#include <stdint.h>

#define	GDT_BASE	0x00000800
#define GDT_SIZE	8

typedef struct __attribute__ ((packed)) s_gdtr {
	uint16_t	size;
	uint32_t	gdt;
}	t_gdtr;

typedef struct __attribute__ ((packed)) s_gdt_descriptor {
    uint16_t	limit_low;
    uint16_t	base_low;
    uint8_t		base_mid;
    uint8_t		access;
    uint8_t		flags;
    uint8_t		base_high;
}	t_gdt_descriptor;

struct tss_entry_struct {
  uint32_t prev_tss;
  uint32_t esp0;
  uint32_t ss0;
  uint32_t esp1;
  uint32_t ss1;
  uint32_t esp2;
  uint32_t ss2;
  uint32_t cr3;
  uint32_t eip;
  uint32_t eflags;
  uint32_t eax;
  uint32_t ecx;
  uint32_t edx;
  uint32_t ebx;
  uint32_t esp;
  uint32_t ebp;
  uint32_t esi;
  uint32_t edi;
  uint32_t es;
  uint32_t cs;
  uint32_t ss;
  uint32_t ds;
  uint32_t fs;
  uint32_t gs;
  uint32_t ldt;
  uint32_t trap;
  uint32_t iomap_base;
} __attribute__((packed));

// extern void load_gdt(uint32_t gdt);
extern void load_gdt(t_gdtr *gdt);
extern void load_tss();

void gdt_init(void);
void write_tss(uint16_t ss0, uint32_t esp0, t_gdt_descriptor *gdt_entry);
