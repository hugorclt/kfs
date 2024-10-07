#pragma once

#include "printk.h"
#include <stddef.h>
#include <stdint.h>


void 	hexdump(void *start, size_t byte);
void	ping();
void shutdown();
void reboot();
extern void panic();
extern void fatal();
