#include "shell.h"
#include "debug.h"
#include "printk.h"
#include "handler.h"
#include "utils.h"
#include "commands.h"
#include <stdint.h>


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

void	shell(void)
{
	while (1)
	{
		char	input[2048] = {0}; // proteger si on ecrit 2049 ?
		printk("KFS>");
		fill_user_input(input);

		if (strlen(input) == 0)
			continue ;
		else if (!strncmp(input, "stack", strlen(input)))
		{
			hexdump((void *)get_esp(), 20);
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
