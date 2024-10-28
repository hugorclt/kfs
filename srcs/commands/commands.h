#pragma once

#include "printk.h"
#include <stddef.h>
#include <stdint.h>


void		cmd_hexdump(void *start, size_t byte);
void		cmd_ping(void);
void		cmd_shutdown(void);
void		cmd_reboot(void);
void		cmd_hello(void);
void		cmd_help(void);
void		cmd_halt(void);
void		cmd_malloc();
void		cmd_echo(void);


extern void	panic();
extern void	fatal();
