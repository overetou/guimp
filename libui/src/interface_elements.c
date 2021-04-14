//
// Created by osc on 14/04/2021.
//
#include "ui.h"

void 	ui_create_button(t_ui *ui, t_percent_rect *button_space, void(*callback)
		(SDL_Event *e))
{
	SDL_Rect	to_draw;

	win_percent_rect_to_sdl_rect(NULL, button_space, &to_draw);
	SDL_RenderDrawRect(ui->renderer, &to_draw);
	(void)callback;
}
