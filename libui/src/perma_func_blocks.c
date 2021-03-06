#include "ui.h"

t_perma_func_block	*ui_add_perma_func(t_ui *ui, void (*func)(void*), void *store)
{
	t_perma_func_block	*block = ui->perma_funcs;
	t_perma_func_block	*new_block = malloc(sizeof(t_perma_func_block));

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
	return new_block;
}

void	ui_remove_permafunc(t_ui *ui, t_perma_func_block *to_delete)
{
	t_perma_func_block	*block = ui->perma_funcs;

	if (to_delete->next)
	{
		to_delete->func = to_delete->next->func;
		to_delete->store = to_delete->next->store;
		to_delete->next = to_delete->next->next;
		free(to_delete->next);
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
		free(to_delete);
	}
}
