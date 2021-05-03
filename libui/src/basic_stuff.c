//
// Created by osc on 22/04/2021.
//
#include "ui.h"

void mem_copy(char *dest, const char *src, int len)
{
	int i = 0;

	while (i != len)
	{
		dest[i] = src[i];
		i++;
	}
}

void add_link_to_list(t_link **list, t_link *new_link)
{
	new_link->next = *list;
	if (new_link->next)
		new_link->next->prev = new_link;
	new_link->prev = NULL;
	*list = new_link;
}

void init_list(t_link **list, t_link *new_link)
{
	puts("init_list");
	*list = new_link;
	new_link->next = NULL;
	new_link->prev = NULL;
}

void list_add_link_at_start(t_link **list, t_link *new_link)
{
	puts("list_add_link_at_start");
	new_link->next = *list;
	*list = new_link;
	new_link->prev = NULL;
	new_link->next->prev = new_link;
}

void list_add_link_at_end(t_link *last_link, t_link *new_link)
{
	puts("list_add_link_at_end");
	last_link->next = new_link;
	new_link->prev = last_link;
	new_link->next = NULL;
}

void list_add_link_in_the_middle(t_link *next_link_to_be, t_link *new_link)
{
	puts("list_add_link_in_the_middle");
	new_link->next = next_link_to_be;
	new_link->prev = next_link_to_be->prev;
	next_link_to_be->prev = new_link;
	new_link->prev->next = new_link;
}

void remove_link_from_list(t_link **list, t_link *to_remove)
{
	if (to_remove->prev)
	{
		printf("Removing an element in the middle of the list. Updated list "
		 "will be: %p.\n", to_remove->next);
		to_remove->prev->next = to_remove->next;
		if (to_remove->next)
			to_remove->next->prev = to_remove->prev;
	}
	else
	{
		printf("Removing the first link of the list. It will be "
	   "replaced by: %p.\n", to_remove->next);
		*list = to_remove->next;
		if (*list)
			(*list)->prev = NULL;
	}
}

void free_list(t_link *list, void(*free_func)(void*))
{
	t_link *next;

	while (list)
	{
		next = list->next;
		free_func(list);
		list = next;
	}
}
