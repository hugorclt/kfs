#include "shell.h"
#include "printk.h"
#include "utils.h"
#include "vga.h"
#include "handler.h"


void	fill_user_input_echo(char *input)
{
	char	c = '\0';
	do
	{
		c = get_last_char();
		if (c == '\0' || c == '\n')
			continue ;
		if (c == '\b')
		{
			input[strlen(input) - 1] = '\0';
			vga_erase_last_char_unprotected();
		}
		else 
		{
			input[strlen(input)] = c;
			input[strlen(input) + 1] = '\0';
			printk("%c", c);
		}
	}
	while(c != '\n' && strlen(input) < (80 - strlen("KFS>")));
	if (c == '\n' || strlen(input) >= (80 - strlen("KFS>")))
		printk("\n");
}

void	cmd_echo(void)
{
	printk("Please enter an input: \n");

	char	input[128] = {0};
	fill_user_input_echo(input);
	if (strlen(input))
		printk("%s\n", input);
}
