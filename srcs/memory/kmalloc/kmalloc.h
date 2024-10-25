#pragma once

#include "stddef.h"

void	kfree(void *addr);
void	*kmalloc(size_t size);
void	kmalloc_test();
size_t	ksize(void *addr);
