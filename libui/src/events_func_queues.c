#include "ui.h"

t_ui_event_block	*ui_add_event(t_ui_event_block **list, void (*event_handler_func)(void *win, void *store, SDL_Event*), void *store)
{
	t_ui_event_block	*new_bloc = ui_secure_malloc(sizeof(t_ui_event_block));

	new_bloc->event_handler_func = event_handler_func;
	new_bloc->store = store;
	new_bloc->next = *list;
	*list = new_bloc;
	return new_bloc;
}

t_ui_event_block	*ui_add_main_event(t_ui_win *win, void (*event_handler_func)(void*, void*, SDL_Event*), void *store)
{
	return ui_add_event(&(win->main_events), event_handler_func, store);
}

t_ui_event_block	*ui_add_side_event(t_ui_win *win, void (*event_handler_func)(void*, void*, SDL_Event*), void *store)
{
	return ui_add_event(&(win->side_events), event_handler_func, store);
}

t_ui_event_block	*ui_add_exclusive_side_event(t_ui_win *win, void (*event_handler_func)(void *win, void *store, SDL_Event*), void *store)
{
	t_ui_event_block	*traveler = win->side_events;

	while (traveler)
	{
		if (traveler->event_handler_func == event_handler_func)
		{
			traveler->store = store;
			return traveler;
		}
	}
	return ui_add_side_event(&(win->side_events), event_handler_func, store);
}

void	ui_close_current_main_event(t_ui_win *win)
{
	t_ui_event_block	*to_remove = win->main_events;

	win->main_events = to_remove->next;
	free(to_remove);
}

//Remove any event bloc from its list.
void	ui_remove_event(t_ui_event_block **list, t_ui_event_block *to_remove)
{
	t_ui_event_block	*prev;

	if (*list == to_remove)
		*list = to_remove->next;
	else
	{
		prev = *list
		while (prev->next != to_remove)
			prev = prev->next;
		prev->next = to_remove->next;
	}
	free(to_remove);
}

void	ui_quit_on_sdl_quit(void *win, void *store, SDL_Event *ev)
{
	if (ev->type == SDL_QUIT)
		((t_ui*)win->ui)->keep_going = UI_FALSE;
}
