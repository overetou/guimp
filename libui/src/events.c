#include "ui.h"

static t_ui_win *ui_find_win(t_ui *ui, SDL_Window *wanted)
{
	t_ui_win *win = ui->wins;

	while (win->sdl_ptr != wanted)
		win = win->next;
	return win;
}

t_ui_bool ui_is_point_in_rect(Sint32 x, Sint32 y, SDL_Rect *rect)
{
	return x >= rect->x &&
		x <= rect->x + rect->w &&
		y >= rect->y &&
		y <= rect->y + rect->h;
}

void	ui_transmit_click_event(t_ui_elem *e, SDL_MouseButtonEvent *ev)
{
	while (e)
	{
		if (e->sensible)
		{
			if (e->click_func && ui_is_point_in_rect(ev->x, ev->y,
						&(e->sensible_zones_actual_dimensions)))
			{
				e->click_func(e, ev);
				break;
			}
			if (e->has_sub_clicks && ui_is_point_in_rect(ev->x, ev->y, &(e->actual_dimensions)))
				e = e->sub_elems;
			else
				e = e->next;
		}
		else
			e = e->next;
	}
}

void ui_handle_click(t_ui_win *win, SDL_MouseButtonEvent *ev)
{
	//printf("Clicked at pos: %d, %d.\n", ev->x, ev->y);//TMP
	ui_transmit_click_event(win->content, ev);
}

void	ui_default_event_handler(t_ui_win *win, SDL_Event *ev)
{
	if (ev->type == SDL_MOUSEBUTTONDOWN)
		ui_handle_click(win, (SDL_MouseButtonEvent*)ev);
}

void	go_trough_side_events(t_ui_win	*win, SDL_Event *ev)
{
	t_ui_event_block	*traveler = win->side_events;

	while (traveler)
	{
		traveler->event_handler_func(win, traveler->store, ev);
		traveler = traveler->next;
	}
}

void	ui_handle_events(t_ui *ui)
{
	SDL_Event			ev;
	t_perma_func_block	*perma_func;
	t_ui_win    		*win;

	ui->keep_going = UI_TRUE;
	while (ui->keep_going)
	{
		while (SDL_PollEvent(&ev))
		{
			win = ui_find_win(ui, SDL_GetWindowFromID(((SDL_WindowEvent*)(&ev))->windowID));
			go_trough_side_events(win, &ev);
			win->main_events->event_handler_func(win, win->main_events->store, &ev);
		}
		perma_func = ui->perma_funcs;
		while (perma_func)
		{
			perma_func->func(perma_func->store);
			perma_func = perma_func->next;
		}
		SDL_Delay(35);
	}
}
