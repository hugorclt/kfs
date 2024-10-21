#pragma once

#include <stdint.h>

#define PDE_MAX 1024
#define PTE_MAX 1024

typedef struct s_page_directory {
	uintptr_t entries[PDE_MAX];
} t_page_directory;

typedef struct s_page_table {
	uintptr_t entries[PTE_MAX];
} t_page_table;
