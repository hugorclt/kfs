#pragma once

#include <stdint.h>


// t_gdtr* == GDT_BASE ??
// ou
// t_gdtr.gdt == GDT_BASE ??
// Adrian -> je pense que c'est t_gdtr.gdt (comme le tuto)
//

#define	GDT_BASE	0x00000800
#define GDT_SIZE	7

typedef struct s_gdtr {
	uint16_t	size;
	uint32_t	gdt;
}	t_gdtr __attribute__ ((packed));

typedef struct s_gdt_descriptor {
    uint16_t	limit_low;
    uint16_t	base_low;
    uint8_t		base_mid;
    uint8_t		access;
    uint8_t		limit_high	: 4;
    uint8_t		flags		: 4;
    uint8_t		base_high;
}	t_gdt_descriptor __attribute__ ((packed));

// gdtr = pointeur ? Pour le tuto non
// asm("lgdtl (gdtr)");
	// --> (gdtr) takes adress of gdtr
t_gdtr *gdtr = (t_gdtr *) GDT_BASE; //faux non?
t_gdt_descriptor gdt[GDT_SIZE];

/*
 * access_bytes
 * 	S: Descriptor type = 1/Code:Data segment, 0/System segment. (Stack?)
 * 	DPL: descriptor privilege field (2 bits) = 0-3/Ring level (0 kernel, 3 user, 1-2 useless)
 * 	P: segment present = 1 or 0 if segment is loaded in memory (kfs-3?)
 *
 * Flags
 * 	DB: size flag = 1/32 bits, 0/16 bits
 * 	G: granularity = 0/no multiplication, 1/ size * 1024 = 0-4GB
 *
 *
 *
 */

//Segment Selector in register



// union test
// {
// 	struct elem1 {
// 		uint8_t	elemt1_1 : 1;
// 		uint8_t	elem1_2 : 1;
// 	};
// 	uint8_t elem;
// }
// ;
