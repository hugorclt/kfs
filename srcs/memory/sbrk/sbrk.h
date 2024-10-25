#pragma once

#include "stddef.h"

void *sbrk(size_t size);

#define HEAP_START	0xC0400000
#define HEAP_END	0xC07FFFFF
