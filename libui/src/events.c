//
// Created by osc on 28/04/2021.
//
#include "ui.h"

void ui_handle_click(t_ui *ui, SDL_Event *ev)
{

}

void ui_handle_events(t_ui *ui)
{
	t_ui_bool   keep_going = UI_TRUE;
	SDL_Event   ev;

	while (keep_going)
	{
		ui_sdl_critical_check(SDL_WaitEvent(&ev) == 1);
		switch (ev.type)
		{
			case SDL_QUIT:
				keep_going = UI_FALSE;
				break;
			case SDL_MOUSEBUTTONDOWN:
				ui_handle_click(ui, &ev);
				break;
		}
	}
}
