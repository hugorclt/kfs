#include "handler.h"
#include "stddef.h"
#include "printk.h"


int syscall_read(int fd, const void* buffer, size_t count)
{
	(void) buffer;

	printk("----In syscall_read----\n");
	printk("fd: %d\n", fd);
	printk("buffer: %p\n", buffer);
	printk("count: %u\n", count);
	
	printk("returning: %d\n", fd);
	printk("----Out syscall_read---\n");

	return (fd);
}

int syscall_handler(t_pt_regs *regs)
{
	int syscall_number = regs->eax;
	int result = -ENOSYS; // Default to -ENOSYS if syscall is unimplemented

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
}
