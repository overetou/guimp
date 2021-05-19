//
// Created by osc on 13/04/2021.
//
#include "ui.h"

t_ui    *ui_init(uint32_t ui_flags, int img_flags)
{
	t_ui    *new = ui_secure_malloc(sizeof(t_ui));

	ui_sdl_critical_check(SDL_Init(ui_flags) == 0);
	ui_sdl_critical_check(IMG_Init(img_flags) == img_flags);
	ui_sdl_critical_check(TTF_Init() == 0);
	new->wins = NULL;
	new->focused = NULL;
	return new;
}

//Adds a window to the ui with the given parameters. Display func is the
// function that will be called upon refreshing the interface. It should be
// created by the user.
t_ui_win *ui_add_window(t_ui *ui, const char *title, int x, int y, int w, int h,
                        uint32_t flags, uint32_t render_flags,
                        void (*display_func)(t_ui_elem *))
{
	t_ui_win    *win = ui_secure_malloc(sizeof(t_ui_win));

	add_link_to_list((t_link**)(&(ui->wins)), (t_link*)win);
	win->sdl_ptr = SDL_CreateWindow(title, x, y, w, h, flags);
	ui_sdl_critical_check(win->sdl_ptr != NULL);
	win->rend = SDL_CreateRenderer(win->sdl_ptr, -1, render_flags);
	ui_sdl_critical_check(win->rend != NULL);
	ui_update_window_size(win);
	win->content = ui_create_virgin_elem(0, 0, 100, 100, win, 1, display_func);
	ui_resolve_win_content_actual_size(win);
	win->ui = ui;
	return win;
}

static void ui_free_window(void *win)
{
	t_ui_elem *e = ((t_ui_win*)(win))->content;

	while (e->sub_elems)
		ui_remove_elem(e->sub_elems);
	e->free_store_func(e->store);
	free(e);
	SDL_DestroyRenderer(((t_ui_win*)(win))->rend);
	SDL_DestroyWindow(((t_ui_win*)(win))->sdl_ptr);
	free(win);
}

void    ui_remove_win(t_ui *ui, t_ui_win *win)
{
	remove_link_from_list((t_link**)(&(ui->wins)), (t_link*)win);
	ui_free_window(win);
}

//Rework that func so that it takes a t_ui_window* as parameter (and no ui
// parameter)
void ui_update_window_size(t_ui_win *win)
{
	ui_sdl_critical_check(
	SDL_GetRendererOutputSize(win->rend, &(win->width), &(win->height)
	) == 0);
}

//Destroys everything the given ui knows of. This includes every interface
// elements attached to the ui but not those that were only generated and not
// given to the ui.
void ui_close(t_ui *to_destroy)
{
	free_list((t_link*)(to_destroy->wins), ui_free_window);
	free(to_destroy);
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

void refresh_win(t_ui_win *win)
{
	t_ui_elem *sub_e;
	win->content->display_func(win->content);
	sub_e = win->content->sub_elems;
	while (sub_e && sub_e->display_priority)
	{
		ui_display_elem(sub_e);
		sub_e = sub_e->next;
	}
	SDL_RenderPresent(win->rend);
}
