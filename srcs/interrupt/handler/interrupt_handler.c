#include "handler.h"
#include "utils.h"

t_interrupt_handler interrupt_handlers[256];

void interrupt_handlers_init()
{
	memset(&interrupt_handlers, 0, 256);
}

void register_interrupt_handler(int index, t_interrupt_handler func)
{
	interrupt_handlers[index] = func;
}

void launch_interrupt(int index)
{
	if (interrupt_handlers[index] != 0)
		interrupt_handlers[index]();
}
