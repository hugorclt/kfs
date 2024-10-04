#include "utils.h"

void	*memset(void *b, int c, unsigned int len)
{
	unsigned int	i;

	i = 0;
	while (i < len)
    {
		((char *)(b))[i] = c;
        i++;
    }
	return b;
}

