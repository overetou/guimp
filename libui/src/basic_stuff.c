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

void remove_link_from_list(t_link **list, t_link *to_remove)
{
	if (to_remove->prev)
		to_remove->prev->next = to_remove->next;
	else
		*list = to_remove->next;
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
