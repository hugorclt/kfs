#pragma once

#include <stdint.h>

typedef struct s_gdtr {
	uint16_t	size;
	uint32_t	offset;
}	t_gdtr __attribute__((packed));
