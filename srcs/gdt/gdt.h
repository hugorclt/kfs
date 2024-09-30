#pragma once

#include <stdint.h>

typedef struct s_gdtr {
	uint16_t	size;
	uint32_t	gdt;
}	t_gdtr __attribute__((packed));


// union test
// {
// 	struct elem1 {
// 		uint8_t	elemt1_1 : 1;
// 		uint8_t	elem1_2 : 1;
// 	};
// 	uint8_t elem;
// }
// ;
