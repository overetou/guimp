//
// Created by osc on 26/04/2021.
//
#include "ui.h"

void ui_colorblock_1(t_ui_elem *e)
{
	SDL_SetRenderDrawColor(EL_RENDERER(e), 55, 55, 55, UI_ALPHA_OPAQUE);
	SDL_RenderDrawRect(EL_RENDERER(e), &(e->actual_sizes));
}

void ui_colorblock_2(t_ui_elem *e)
{
	SDL_SetRenderDrawColor(EL_RENDERER(e), 50, 50, 50, UI_ALPHA_OPAQUE);
	SDL_RenderDrawRect(EL_RENDERER(e), &(e->actual_sizes));
}
