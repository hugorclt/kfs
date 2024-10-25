#include "debug.h"
#include "commands.h"
#include "printk.h"
#include "gdt.h"
#include "idt.h"
#include "vga.h"
#include "shell.h"
#include "pmm.h"
#include "vmm.h"
#include "multiboot.h"
#include <stdint.h>
#include "utils.h"
#include "kmalloc.h"

char	*alloc_and_set_str(char	*str)
{
	char *alloc = (char *) kmalloc(strlen(str) * sizeof(char));
	if (!alloc)
	{
		printk("malloc casse: test = \n", str);
		return NULL;
	}
	for (size_t i = 0; i < strlen(str); i++)
	{
		alloc[i] = str[i];
	}
	alloc[strlen(str)] = '\0';
	return (alloc);
}
void	malloc_test()
{
	printk("will malloc 10000 now\n");
	void *ptr = kmalloc(10000);
	printk("ptr addr = %p\n", ptr);
	kfree(ptr);
	char	*test1 = alloc_and_set_str("hello 1\n");
	char	*test2 = alloc_and_set_str("hello 2\n");
	printk("test1 value: %s", test1);
	printk("test1 addr = %p\n", test1);

	printk("test2 value: %s", test2);
	printk("test2 addr = %p\n", test2);

	kfree(test1);
	char	*test3 = alloc_and_set_str("hello 3\n");
	printk("test3 value: %s", test3);
	printk("test3 addr = %p\n", test3);
	kfree(test2);
	kfree(test3);

}

void	kernel_main(uint32_t magic, multiboot_info_t *bootInfo) 
{
	(void) magic;
	gdt_init();
	pmm_init(bootInfo);
	vmm_init();
	idt_init();
	printk("");

	// print_memory_map(bootInfo);
	malloc_test();

	shell();

	printk("infinite loop \n");
	while(1);
}
