//
// Created by osc on 26/04/2021.
//
#include "ui.h"

void ui_colorblock_1(t_ui_elem *e)
{
	ui_sdl_critical_check(
	SDL_SetRenderDrawColor(EL_RENDERER(e), 70, 70, 70, UI_ALPHA_OPAQUE)
	 == 0);
	ui_sdl_critical_check(
	SDL_RenderFillRect(EL_RENDERER(e), &(e->actual_sizes))
	== 0);
}

void ui_colorblock_2(t_ui_elem *e)
{
	ui_sdl_critical_check(
	SDL_SetRenderDrawColor(EL_RENDERER(e), 50, 50, 50, UI_ALPHA_OPAQUE)
	== 0);
	ui_sdl_critical_check(
	SDL_RenderFillRect(EL_RENDERER(e), &(e->actual_sizes))
	== 0);
}