//
// Created by osc on 13/04/2021.
//
#include "ui.h"

//TODO: It may be good to separate that function in separate calls. 1 for sdl,
// img and ttf init, 2 for adding windows to the ui.
t_ui    *ui_init(
		uint32_t ui_flags,
		int img_flags,
		const char *title,
		int win_x,
		int win_y,
		int win_w,
        int win_h,
        uint32_t win_flags)
{
	t_ui    *new = ui_secure_malloc(sizeof(t_ui));
	SDL_Init(win_flags);
	IMG_Init(img_flags);
	new->win = SDL_CreateWindow(title,
	                       SDL_WINDOWPOS_UNDEFINED,
	                       SDL_WINDOWPOS_UNDEFINED,
	                       500,
	                       500,
	                       SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	new->renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
	new->win = win;
	ui_update_window_size();
	new->renderer = renderer;
	return new;
}

void percent_rect_to_sdl_rect(t_percent_rect *rect, SDL_Rect *rect_1);

void	ui_update_window_size(void)
{
	SDL_GetWindowSize(ui_m.win, &(ui_m.win_width), &(ui_m.win_height));
}

void 	ui_refresh(void)
{
	SDL_RenderPresent(ui_m.renderer);
}

//Destroys everything the given ui knows of.
void ui_close(t_ui *to_destroy)
{
	free(to_destroy);
}

void 	ui_colorize_window(SDL_Color *color)
{
	SDL_SetRenderDrawColor(ui_m.renderer, color->r, color->g, color->b,
	                       color->a);
	SDL_RenderClear(ui_m.renderer);
}

void 	ui_create_button(t_percent_rect *button_space, void(*callback)
		(SDL_Event *e))
{
	SDL_Rect	to_draw;

	percent_rect_to_sdl_rect(button_space, &to_draw);
	SDL_RenderDrawRect(ui_m.renderer, &to_draw);
	(void)callback;
}

void percent_rect_to_sdl_rect(t_percent_rect *p_rect, SDL_Rect *sdl_rect)
{
	sdl_rect->x = ui_m.win_width * p_rect->x / 100;
	sdl_rect->y = ui_m.win_height * p_rect->y / 100;
	sdl_rect->w = ui_m.win_width * p_rect->w / 100;
	sdl_rect->h = ui_m.win_height * p_rect->h / 100;
}
