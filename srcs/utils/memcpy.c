#include "utils.h"

void	*memcpy(void *dst, const void *src, size_t n)
{
	size_t i;

	if (!dst && !src)
		return (0);
	i = 0;
	while (i < n)
	{
		((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (dst);
}
