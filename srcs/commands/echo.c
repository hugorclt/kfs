#include "shell.h"
#include "printk.h"
#include "utils.h"

void	cmd_echo(void)
{
	printk("Please enter an input: \n");

	char	input[128] = {0};
	fill_user_input(input);
	if (strlen(input))
		printk("%s\n", input);
}
