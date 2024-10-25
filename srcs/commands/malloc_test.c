#include "sbrk.h"
#include "pmm.h"
#include "kmalloc.h"
#include "printk.h"
#include "utils.h"

#define HEAP_SIZE			HEAP_END - HEAP_START
#define ALLOC_MAX			HEAP_SIZE - PAGE_FRAME_SIZE
#define MALLOC_HEADER_SIZE	8

char	*alloc_and_set_str(char	*str)
{
	char *alloc = (char *) kmalloc(strlen(str) * sizeof(char) + 1);
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

void	cmd_malloc()
{
	char	*test1 = alloc_and_set_str("hello 1\n");
	if (!test1)
	{
		printk("test1: alloc casse\n");
		return ;
	}
	char	*test2 = alloc_and_set_str("hello 2\n");
	if (!test2)
	{
		printk("test2: alloc casse\n");
		return ;
	}
	printk("test1: value = %s", test1);
	printk("test1: addr = %p, test1: size = %u\n", test1, ksize(test1));


	printk("test2: value = %s", test2);
	printk("test2: addr = %p, test2: size = %u\n", test2, ksize(test2));
	

	kfree(test1);
	printk("test1: free\n");

	char	*test3 = alloc_and_set_str("hello 3\n");
	if (!test3)
	{
		printk("test3: alloc casse\n");
		return ;
	}
	printk("test3: value = %s", test3);
	printk("test3: addr = %p, test3: size = %u\n", test3, ksize(test3));

	kfree(test2);
	printk("test2: free\n");

	kfree(test3);
	printk("test3: free\n");
}

// void	cmd_fat_malloc()
// {
// 	size_t alloc_size = ALLOC_MAX - MALLOC_HEADER_SIZE;
// 	printk("fat_malloc: allocating %u\n", alloc_size);
// 	char *fat_malloc = kmalloc(alloc_size);
// 	if (!fat_malloc)
// 	{
// 		printk("fat malloc == NULL\n");
// 		return ;
// 	}
// 	printk("fat_malloc: addr = %p\nfat_malloc: size = %u\n", fat_malloc, ksize(fat_malloc));
// 	kfree(fat_malloc);
// 	printk("fat_malloc: free\n");
// }

// printk("ptr: will malloc 10000 now\n");
// 	void *ptr = kmalloc(10000);
// 	if (!ptr)
// 	{
// 		printk("ptr: alloc casse\n");
// 		return ;
// 	}
// 	printk("ptr: addr = %p, ptr: size = %u\n", ptr, ksize(ptr));
// 	kfree(ptr);
// 	printk("ptr: free\n");
