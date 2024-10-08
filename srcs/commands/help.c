#include "commands.h"
#include "vga.h"

void	cmd_help()
{
	char	*cmds[] = {"stack", "ping", "hello", "shutdown", "reboot", "clear", "halt", "help"};

	printk("Usage:  ");
	vga_set_fg_color(VGA_COLOR_LIGHT_BROWN);
	for(size_t i = 0; i < 8; i++)
	{
		printk("%s  ", cmds[i]);
	}
	vga_set_fg_color(VGA_COLOR_WHITE);
	printk("\n");
}
