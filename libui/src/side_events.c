#include "ui.h"

void	ui_add_side_event(t_ui_win *win, void (*event_handler_func)(void*, SDL_Event*), void *store)
{
	t_ui_side_event_block	*new_bloc = ui_secure_malloc(sizeof(t_ui_side_event_block));

	new_bloc->event_handler_func = event_handler_func;
	new_bloc->store = store;
	new_bloc->next = win->side_events;
}

void	ui_add_exclusive_side_event(t_ui_win *win, void (*event_handler_func)(void*, SDL_Event*), void *store)
{
	t_ui_side_event_block	*traveler = win->side_events;

	while (traveler)
	{
		if (traveler->event_handler_func == event_handler_func)
		{
			traveler->store = store;
			return;
		}
	}
	ui_add_exclusive_side_event(win, event_handler_func, store);
}
