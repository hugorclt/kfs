#include "shell.h"
#include "debug.h"
#include "printk.h"
#include "handler.h"
#include "utils.h"
#include "commands.h"
#include "vga.h"

static void	fill_user_input(char *input)
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
			vga_erase_last_char();
		}
		else 
		{
			input[strlen(input)] = c;
			input[strlen(input) + 1] = '\0';
			printk("%c", c);
		}
	}
	while(c != '\n' && strlen(input) < (80 - strlen("KFS>")));
	if (c == '\n')
		printk("\n");
}

static bool	check_user_input(const char *input, const char *cmd)
{
	if (strlen(input) != strlen(cmd))
		return false;
	return (!strncmp(input, cmd, strlen(input)));
}

static void	print_prompt(void)
{
	vga_set_fg_color(VGA_COLOR_LIGHT_GREY);
	printk("KFS");
	vga_set_fg_color(VGA_COLOR_BROWN);
	printk(">");
	vga_set_fg_color(VGA_COLOR_WHITE);

}

void	shell(void)
{
	vga_clear_buffer();
	cmd_hello();

	while (1)
	{
		char	input[128] = {0}; 
		print_prompt();
		fill_user_input(input);

		if (strlen(input) == 0)
			continue ;
		else if (check_user_input(input, "stack"))
			cmd_hexdump((void *)get_esp(), 20);
		else if (check_user_input(input, "ping"))
			cmd_ping();
		else if (check_user_input(input, "shutdown"))
			cmd_shutdown();
		else if (check_user_input(input, "reboot"))
			cmd_reboot();
		else if (check_user_input(input, "clear"))
			vga_clear_buffer();
		else if (check_user_input(input, "hello"))
			cmd_hello();
		else if (check_user_input(input, "help"))
			cmd_help();
		else if (check_user_input(input, "halt"))
			panic();
		else
			printk("Error: unknown cmd: %s\n", input);
	}
}
