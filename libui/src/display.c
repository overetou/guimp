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

void ui_display_img_at_center_of_elem(t_ui_elem *e, t_ui_img *img)
{
	SDL_Rect rect;

	ui_sdl_critical_check(
			SDL_QueryTexture(img, NULL, NULL, &(rect.w), &(rect.h))
			== 0);
	rect.x = e->actual_sizes.x + (e->actual_sizes.w - rect.w) / 2;
	rect.y = e->actual_sizes.y + (e->actual_sizes.h - rect.h) / 2;
	ui_sdl_critical_check(SDL_RenderCopy(UI_EL_REND(e), img, NULL, &rect) == 0);
}

void ui_display_img(t_ui_elem *e, t_ui_img *img, t_percentage x, t_percentage y)
{
	SDL_Rect rect;

	ui_sdl_critical_check(
			SDL_QueryTexture(img, NULL, NULL, &(rect.w), &(rect.h))
			== 0);
	rect.x = e->actual_sizes.x + ((e->actual_sizes.w * x) / 100);
	rect.y = e->actual_sizes.y + ((e->actual_sizes.h * y) / 100);
	ui_sdl_critical_check(SDL_RenderCopy(UI_EL_REND(e), img, NULL, &rect) == 0);
}

t_ui_img *ui_text_to_texture(const char *text, int font_index, t_ui_color
*foreground, t_ui_color *background, t_ui_elem *e)
{
	SDL_Surface *surface;
	t_ui_img    *to_return;

	surface = TTF_RenderText_Shaded(UI_EL_UI(e)->fonts[font_index], text, *foreground,
								 *background);
	ui_sdl_critical_check(surface != NULL);
	to_return = SDL_CreateTextureFromSurface(UI_EL_REND(e), surface);
	ui_sdl_critical_check(to_return != NULL);
	SDL_FreeSurface(surface);
	return to_return;
}

void ui_close_font(TTF_Font *font)
{
	TTF_CloseFont(font);
}

void ui_colorize_elem(t_ui_elem *e, int r, int g, int b, int a)
{
	ui_sdl_critical_check(
			SDL_SetRenderDrawColor(UI_EL_REND(e), r, g, b, a) == 0
			&& SDL_RenderFillRect(UI_EL_REND(e), &(e->actual_sizes)) == 0
			);
}
