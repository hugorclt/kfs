#pragma once

#define PAGE_PRESENT 0x1
#define PAGE_RW 0x2
#define PAGE_USER 0x4
#define PAGE_4MB 0x80

#include <stdint.h>

typedef struct s_page_directory
{
    uint32_t entries[1024];
} t_page_directory;

