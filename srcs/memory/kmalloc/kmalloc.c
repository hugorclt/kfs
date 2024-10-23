#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include "sbrk.h"
#include "pmm.h"

typedef struct s_list_allocator {
	size_t			size;
	struct s_list_allocator *next;
} t_list_allocator;

t_list_allocator *list;
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

	while (tmp)
	{
		if (tmp->next->next && tmp->next == elem)
		{
			tmp->next = tmp->next->next;			
			break ;
		}
		tmp = tmp->next;
	}
}

t_list_allocator *lst_add_front(void *addr, size_t size)
{
	t_list_allocator *new_node = create_node(addr, size); 

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
		if (temp->size + header_padding >= size)
			return (temp);
		temp = temp->next;
	}

	return (NULL);	
}

void	kfree(void *addr)
{
	t_list_allocator *node = (t_list_allocator *)(addr - header_padding);

	node->next = list;
	list = node;
	return ;
}

void	*alloc_space(size_t size, t_list_allocator *free_block)
{
	if (free_block->size != size)
	{
		t_list_allocator *new_block = lst_add_front((void*)((uintptr_t)free_block + size), free_block->size - size);
		new_block->next->next = free_block->next;
	}

}

void	*kmalloc(size_t size)
{
	t_list_allocator *free_block = find_free_block(size);

	if (!free_block)
	{
		void *new_space = sbrk(size);
		if (!new_space)
			return (NULL);
		free_block = lst_add_front(new_space, (size / PAGE_FRAME_SIZE + 1) * 4096);
	}



	// free_block->size = size;

	return (free_block);
}
