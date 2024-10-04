#include "handler.h"
#include "print.h"


void	exception_print()
{
	printk("In: System Exeption != 13 \n");
}

void	gp_handler()
{
	printk("In: General Protection Fault == 13\n");
}
