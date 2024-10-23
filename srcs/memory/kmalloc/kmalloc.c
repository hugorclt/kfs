#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include "sbrk.h"
#include "pmm.h"
#include "printk.h"

typedef struct s_list_allocator {
	size_t			size;
	struct s_list_allocator *next;
} t_list_allocator;

t_list_allocator *list = NULL;
size_t		header_padding = sizeof(t_list_allocator);

t_list_allocator *create_node(void *addr, size_t size)
{
	t_list_allocator *new_node = (t_list_allocator*)addr;
	new_node->size = size;
	new_node->next = NULL;
	
	return (new_node);
}

t_list_allocator *remove_node(t_list_allocator *elem)
{
	t_list_allocator *tmp = list;

	if (elem == NULL)
		return NULL;
	if (tmp == elem)
	{
		list = elem->next;
		return (list);
	}

	while (tmp && tmp->next != elem)
	{
		tmp = tmp->next;
	}
	if (!tmp)
		return (NULL);
	tmp->next = tmp->next->next;
	return (list);
}

t_list_allocator *lst_add_front(t_list_allocator *new_node)
{
	if (!list)
	{
		list = new_node;
	}
	else
	{
		new_node->next = list;
		list = new_node;
	}
	return (new_node);
}

t_list_allocator *find_free_block(size_t size)
{
	t_list_allocator *temp = list;

	while (temp)
	{
		if (temp->size >= size)
			return (temp);
		temp = temp->next;
	}

	return (NULL);	
}

void	kfree(void *addr)
{
	if (!addr)
		return ;
	t_list_allocator *new_node = (t_list_allocator *)(addr - header_padding);
	lst_add_front(new_node);
}

void	*alloc_space(size_t size, t_list_allocator *free_block)
{

	if (free_block->size != size)
	{
		t_list_allocator *new_block = create_node((void*)((uintptr_t)free_block + size), free_block->size - size);
		lst_add_front(new_block);
	}
	remove_node(free_block);

	return (free_block);
}

void	*kmalloc(size_t size)
{
	size_t				real_size = size + header_padding;
	t_list_allocator	*free_block = find_free_block(real_size);

	if (!free_block)
	{
		void *new_space = sbrk(real_size);
		printk("new space: %X\n", new_space);
		if (!new_space)
			return (NULL);
		t_list_allocator *new_node = create_node(new_space,  (real_size / PAGE_FRAME_SIZE + 1) * 4096); 
		free_block = lst_add_front(new_node);
	}

	alloc_space(real_size, free_block);

	return (free_block + header_padding);
}
