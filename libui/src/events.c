//
// Created by osc on 28/04/2021.
//
#include "ui.h"

void ui_handle_click(t_ui *ui, SDL_Event *ev)
{

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
				ui_handle_click(ui, &ev);
				break;
		}
	}
}
