//
// Created by osc on 27/04/2021.
//
#include "ui.h"

//Returns a pointer to a sized font.
TTF_Font *ui_load_font(const char *path, int size)
{
	TTF_Font    *new = TTF_OpenFont(path, size);

	ui_sdl_critical_check(new != NULL);
	return (NULL);
}

TTF_Font *ui_close_font(TTF_Font *font)
{
	TTF_CloseFont(font);
}

void ui_colorize_elem(t_ui_elem *e, int r, int g, int b, int a)
{
	ui_sdl_critical_check(
			SDL_SetRenderDrawColor(EL_RENDERER(e), r, g, b, a) == 0
			&& SDL_RenderFillRect(EL_RENDERER(e), &(e->actual_sizes)) == 0
			);
}
