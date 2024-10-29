#include "commands.h"

void	test_syscall_read(int fd, void *buffer, size_t count)
{
	printk("calling read with args: %d, %p, %u\n", fd, buffer, count);
	int ret = test_syscall_read_asm(fd, buffer, count);
	printk("return value of syscall_read: %d\n", ret);
}
