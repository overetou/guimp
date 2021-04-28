//
// Created by osc on 27/04/2021.
//
#include "ui.h"

//Returns a pointer to a sized font.
TTF_Font *ui_load_font(const char *path, int size)
{
	TTF_Font    *new = TTF_OpenFont(path, size);

	ui_sdl_critical_check(new != NULL);
	return (new);
}

void    ui_display_centered_text_line(t_ui_elem *e, const char *text_line,
									  t_ui_color *foreground,
									  t_ui_color *background)
{
	SDL_Surface *surface;
	SDL_Texture *texture;
	SDL_Rect    text_rect;

	surface = TTF_RenderText_Shaded(e->store, text_line, *foreground,
								 *background);
	ui_sdl_critical_check(surface != NULL);
	ui_sdl_critical_check(
			TTF_SizeText(e->store, text_line, &(text_rect.w), &(text_rect.h))
			== 0);
	text_rect.x = e->actual_sizes.x + (e->actual_sizes.w - text_rect.w) / 2;
	text_rect.y = e->actual_sizes.y + (e->actual_sizes.h - text_rect.h) / 2;
	texture = SDL_CreateTextureFromSurface(EL_RENDERER(e), surface);
	ui_sdl_critical_check(texture != NULL);
	ui_sdl_critical_check(
	SDL_RenderCopy(EL_RENDERER(e), texture, NULL, &text_rect)
	 == 0);
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);
}

void ui_close_font(TTF_Font *font)
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
