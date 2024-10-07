#pragma once

#include "stddef.h"

void	*memcpy(void *dst, const void *src, size_t n);
void	*memset(void *b, int c, unsigned int len);
size_t	strlen(const char* str);
int		strncmp(const char *s1, const char *s2, size_t n);
