//
// Created by osc on 13/04/2021.
//
#include "ui.h"

t_ui_master ui_m;

void percent_rect_to_sdl_rect(t_percent_rect *rect, SDL_Rect *rect_1);

//You should call SDL_init, SDL_Create_Window and IMG_Init with the parameters
// you want before calling this. For now only one window is supported by the
// library.
void	ui_init(SDL_Window *win, SDL_Renderer *renderer)
{
	ui_m.win = win;
	ui_update_window_size();
	ui_m.renderer = renderer;
}

void	ui_update_window_size(void)
{
	SDL_GetWindowSize(ui_m.win, &(ui_m.win_width), &(ui_m.win_height));
}

void 	ui_refresh(void)
{
	SDL_RenderPresent(ui_m.renderer);
}

//This will free everything that ui lib used by for itself but you still need
// to call IMG_Quit() and SDL_Quit()
void ui_quit(void)
{

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
