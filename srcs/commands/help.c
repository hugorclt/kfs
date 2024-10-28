#include "commands.h"
#include "vga.h"

static size_t	tab_size(char	*tab[])
{
	size_t i = 0;
	while (tab[i])
		i++;
	return i;
}

void	cmd_help()
{
	char	*cmds[] = {"stack", "ping", "hello", "shutdown", "reboot", "clear", "halt", "help",
		"switchkbr", "  ", "malloc", "echo", "signal", "signalqueue", NULL};

	printk("Usage:  ");
	vga_set_fg_color(VGA_COLOR_LIGHT_BROWN);
	for(size_t i = 0; i < tab_size(cmds); i++)
		printk("%s  ", cmds[i]);
	vga_set_fg_color(VGA_COLOR_WHITE);
	printk("\n");
}
