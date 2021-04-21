//
// Created by osc on 13/04/2021.
//
#include "ui.h"

t_ui    *ui_init(uint32_t ui_flags, int img_flags)
{
	t_ui    *new = ui_secure_malloc(sizeof(t_ui));

	ui_sdl_critical_check(SDL_Init(ui_flags));
	ui_sdl_critical_check(IMG_Init(img_flags));
	new->total_wins_nb = 0;
	return new;
}

void    ui_create_window(t_ui *ui, const char *title, int x, int y, int w,
						 int h, uint32_t flags, uint32_t render_flags)
{
	SDL_Window      *new_win;
	SDL_Renderer    *new_rend;

	new_win = SDL_CreateWindow(title, x, y, w, h, flags);
	new_rend = SDL_CreateRenderer(new_win, -1, render_flags);
	ui_update_window_size(ui, new_win);
}

//Rework that func so that it takes a t_ui_window* as parameter (and no ui
// parameter)
void	ui_update_window_size(t_ui *ui, SDL_Window *win)
{
	SDL_GetWindowSize(win, &(ui->win_width), &(ui->win_height));
}

void 	ui_refresh(t_ui *ui)
{
	SDL_RenderPresent(ui->renderer);
}

//Destroys everything the given ui knows of.
void ui_close(t_ui *to_destroy)
{
	free(to_destroy);
	IMG_Quit();
	SDL_Quit();
}

void 	ui_colorize_window(t_ui *ui, SDL_Color *color)
{
	SDL_SetRenderDrawColor(ui->renderer, color->r, color->g, color->b,
	                       color->a);
	SDL_RenderClear(ui->renderer);
}
