#include <print.h>

static size_t	strlen(const char* str)
{
	size_t	i = 0;
	while(str[i++]);
	return (i);
}

void	printk(const char* str)
{
	for(size_t i = 0; i < strlen(str); i++)
	{
		vga_write_buffer(str[i]);
	}
}
