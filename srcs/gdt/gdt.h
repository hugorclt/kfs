#pragma once

#include <stdint.h>

typedef struct s_gdtr {
	uint16_t	size;
	uint32_t	gdt;
}	t_gdtr __attribute__((packed));

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

typedef struct s_gdt_descriptor{
	uint16_t limit_low;	
	uint16_t base_low;
	uint8_t base_middle;
	uint8_t access_byte;
} t_gdt_descriptor __attribute__((packed));




// union test
// {
// 	struct elem1 {
// 		uint8_t	elemt1_1 : 1;
// 		uint8_t	elem1_2 : 1;
// 	};
// 	uint8_t elem;
// }
// ;
