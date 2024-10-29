#include "commands.h"

void	test_syscall_read(int fd, void * buffer, size_t count)
{
	printk("in test_syscall_read\n");
	int ret = test_syscall_read_asm(fd, buffer, count);
	printk("test\n");
	printk("test\n");
	// printk("return value of syscall_read: %d\n", ret);
}
