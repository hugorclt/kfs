#include "shell.h"
#include "printk.h"
#include "handler.h"
#include "utils.h"
#include "commands.h"

void	fill_user_input(char *input)
{
	char	c;
	do
	{
		c = get_last_char();
		if (c == '\0' || c == '\n')
			continue ;
		input[strlen(input)] = c;
		input[strlen(input) + 1] = '\0';
		clean_last_char();
	}
	while(c != '\n');
	clean_last_char();
}

#define	nb_gdt_descriptor	7
#define	size_gdt_descriptor	8

void	shell(void)
{
	while (1)
	{
		char	input[2048] = {0}; // proteger si on ecrit 2049 ?
		printk("KFS>");
		fill_user_input(input);

		if (strlen(input) == 0)
			continue ;
		else if (!strncmp(input, "hexdump", strlen(input)))
		{
			hexdump((char *)0x800,
			( (nb_gdt_descriptor * size_gdt_descriptor) / 4));
		}
		else if (!strncmp(input, "ping", strlen(input)))
			ping();
		else if (!strncmp(input, "shutdown", strlen(input)))
			shutdown();
		else if (!strncmp(input, "reboot", strlen(input)))
			reboot();
		else
			printk("Error: unknown cmd: %s\n", input);
	}
}
