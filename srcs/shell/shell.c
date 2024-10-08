#include "shell.h"
#include "printk.h"
#include "handler.h"
#include "utils.h"
#include "commands.h"
#include "vga.h"

static void	fill_user_input(char *input)
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
		char	input[2048] = {0}; // proteger si on ecrit 2049 ?
		print_prompt();
		fill_user_input(input);

		if (strlen(input) == 0)
			continue ;
		else if (!strncmp(input, "hexdump", strlen(input)))
		{
			cmd_hexdump((char *)0x800,
			( (nb_gdt_descriptor * size_gdt_descriptor) / 4));
		}
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
		else
			printk("Error: unknown cmd: %s\n", input);
	}
}
