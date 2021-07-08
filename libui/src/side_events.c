#include "ui.h"

t_ui_side_event_block	*ui_add_side_event(t_ui_win *win, void (*event_handler_func)(void*, SDL_Event*), void *store)
{
	t_ui_side_event_block	*new_bloc = ui_secure_malloc(sizeof(t_ui_side_event_block));

	new_bloc->event_handler_func = event_handler_func;
	new_bloc->store = store;
	new_bloc->next = win->side_events;
	return new_bloc;
}

t_ui_side_event_block	*ui_add_exclusive_side_event(t_ui_win *win, void (*event_handler_func)(void*, SDL_Event*), void *store)
{
	t_ui_side_event_block	*traveler = win->side_events;

	while (traveler)
	{
		if (traveler->event_handler_func == event_handler_func)
		{
			traveler->store = store;
			return traveler;
		}
	}
	return ui_add_exclusive_side_event(win, event_handler_func, store);
}

void	ui_remove_side_event(win, t_ui_side_event_block *to_remove)
{
	t_ui_side_event_block	*prev;

	if (win->side_events == to_remove)
		win->side_events = to_remove->next;
	else
	{
		prev = win->side_events;
		while (prev->next != to_remove)
			prev = prev->next;
		prev->next = to_remove->next;
	}
	free(to_remove);
}
