#pragma once

#include <stdint.h>
#include <vga.h>

// void	printk(const char* str);
void	printkhex(uint32_t nb);
void 	printmemk(void *address, size_t byte);
