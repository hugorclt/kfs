#include "handler.h"
#include "stddef.h"
#include "printk.h"


int syscall_read(int fd, const void* buffer, size_t count)
{
	(void) buffer;

	printk("In syscall_read");
	printk("fd: %d\n", fd);
	printk("count: %u\n", count);

	return (fd);
}

int syscall_handler(t_pt_regs *regs)
{
	printk("in syscall handler\n");
	int syscall_number = regs->eax;
    int result = -ENOSYS; // Default to -ENOSYS if syscall is unimplemented
			  printk("syscall_number: %d, %d, %d, %d\n", syscall_number, regs->ebx, regs->ecx, regs->edx);

	switch(syscall_number)
	{
		case SYSCALL_READ:
			result = syscall_read(
				(int)regs->ebx,          // fd
        	    (void *)regs->ecx,       // buffer
        	    (size_t)regs->edx        // count
        	    );
			break;
		
		default:
			break;
	}
	return (result);
	printk("Syscall return\n");
}
