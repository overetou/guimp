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

t_ui_win * ui_add_window(t_ui *ui, const char *title, int x, int y, int w,
                         int h, uint32_t flags, uint32_t render_flags)
{
	t_ui_win    *win = ui->wins + ui->total_wins_nb;

	win->sdl_ptr = SDL_CreateWindow(title, x, y, w, h, flags);
	win->rend = SDL_CreateRenderer(win->sdl_ptr, -1, render_flags);
	ui_update_window_size(NULL);
	(ui->total_wins_nb)++;
	return win;
}

//Rework that func so that it takes a t_ui_window* as parameter (and no ui
// parameter)
void ui_update_window_size(t_ui_win *win)
{
	SDL_GetWindowSize(win->sdl_ptr, &(win->width), &(win->height));
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
