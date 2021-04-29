//
// Created by osc on 28/04/2021.
//
#include "ui.h"

static t_ui_win *ui_find_win_from_id(t_ui *ui, SDL_Window *wanted)
{
	t_ui_win *win = ui->wins;

	while (win->sdl_ptr != wanted)
		win = win->next;
	return win;
}

t_ui_bool ui_is_point_in_rect(Sint32 x, Sint32 y, SDL_Rect *rect)
{
	return x >= rect->x && x <= rect->x + rect->w
	&& y >= rect->y && y <= rect->y + rect->h;
}

void ui_handle_click(t_ui *ui, SDL_MouseButtonEvent *ev)
{
	t_ui_win    *win = ui_find_win_from_id(ui, SDL_GetWindowFromID(ev->windowID));
	t_ui_elem   *e = win->content;

	while (e)
	{
		if (e->sensible)
		{
			if (e->has_sub_clicks)
			{
				if (ui_is_point_in_rect(ev->x, ev->y, &(e->actual_sizes)))
					e = e->sub_elems;
			}
			else
			{
				if (e->click_func && ui_is_point_in_rect(ev->x, ev->y,
				&(e->sensible_rects)))
					e->click_func(e);
				else
					e = e->next;
			}
		}
		else
			e = e->next;
	}
}

void ui_handle_events(t_ui *ui)
{
	SDL_Event   ev;

	ui->keep_going = UI_TRUE;
	while (ui->keep_going)
	{
		ui_sdl_critical_check(SDL_WaitEvent(&ev) == 1);
		switch (ev.type)
		{
			case SDL_QUIT:
				ui->keep_going = UI_FALSE;
				break;
			case SDL_MOUSEBUTTONDOWN:
				ui_handle_click(ui, (SDL_MouseButtonEvent*)(&ev));
				break;
		}
	}
}
