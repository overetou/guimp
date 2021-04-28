//
// Created by osc on 26/04/2021.
//
#include "ui.h"

void ui_colorblock_1(t_ui_elem *e)
{
	ui_colorize_elem(e, 70, 70, 70, UI_ALPHA_OPAQUE);
}

void ui_colorblock_2(t_ui_elem *e)
{
	SDL_Color   fg = {120, 120, 120, UI_ALPHA_OPAQUE};
	SDL_Color   bg = {50, 50, 50, UI_ALPHA_OPAQUE};
	SDL_Surface *surface;
	SDL_Texture *texture;
	SDL_Rect    text_rect = {e->actual_sizes.x, e->actual_sizes.y,
						   0, 0};

	ui_colorize_elem(e, 50, 50, 50, UI_ALPHA_OPAQUE);
	surface = TTF_RenderText_Shaded(e->store, "Dark Souls", fg, bg);
	TTF_SizeText(e->store, "Dark Souls", &(text_rect.w), &(text_rect.h));
	ui_sdl_critical_check(surface != NULL);
	texture = SDL_CreateTextureFromSurface(EL_RENDERER(e), surface);
	SDL_RenderCopy(EL_RENDERER(e), texture, NULL, &text_rect);
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);
}
