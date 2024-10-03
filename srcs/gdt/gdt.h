#pragma once

#include <stdint.h>

#define	GDT_BASE	0x00000800
#define GDT_SIZE	7

typedef struct __attribute__ ((packed)) s_gdtr {
	uint16_t	size;
	uint32_t	gdt;
}	t_gdtr;

typedef struct __attribute__ ((packed)) s_gdt_descriptor {
    uint16_t	limit_low;
    uint16_t	base_low;
    uint8_t		base_mid;
    uint8_t		access;
    uint8_t		limit_high	: 4;
    uint8_t		flags		: 4;
    uint8_t		base_high;
}	t_gdt_descriptor;

void gdt_init(void);
extern void load_gdt(t_gdtr *gdt);

