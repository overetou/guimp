#include "ui.h"

void	ui_add_perma_func(t_ui *ui, void (*func)(t_ui*, void*), void *store)
{
	t_permanent_func_block	*block = ui->perma_funcs;
	t_permanent_func_block	*new_block = malloc(sizeof(t_permanent_func_block));

	new_block->func = func;
	new_block->store = store;
	new_block->next = NULL;
	if (block)
	{
		while (block->next)
			block = block->next;
		block->next = new_block;
	}
	else
		ui->perma_funcs = new_block;
}

void	ui_remove_permafunc(t_ui *ui, t_permanent_func_block *to_delete)
{
	t_permanent_func_block	*block = ui->perma_funcs;
    void                    *to_free = to_delete->next;

	if (to_delete->next)
	{
		to_delete->func = to_delete->next->func;
		to_delete->store = to_delete->next->store;
		to_delete->next = to_delete->next->next;
		free(to_free);
	}
	else
	{
		if (block == to_delete)
			ui->perma_funcs = NULL;
		else
		{
			while (block->next != to_delete)
				block = block->next;
			block->next = NULL;
		}
	}
	
}
