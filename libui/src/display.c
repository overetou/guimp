//
// Created by osc on 27/04/2021.
//
#include "ui.h"

void ui_colorize_elem(t_ui_elem *e, int r, int g, int b, int a)
{
	ui_sdl_critical_check(
			SDL_SetRenderDrawColor(EL_RENDERER(e), r, g, b, a) == 0
			&& SDL_RenderFillRect(EL_RENDERER(e), &(e->actual_sizes)) == 0
			);
}
