//
// Created by osc on 22/04/2021.
//
#include "ui.h"

#define EL_RENDERER(e) ((t_ui_win*)(e->win))->rend

t_ui_img *ui_load_img_for_win(t_ui_win *win, const char *img_path)
{
	return IMG_LoadTexture(win->rend, img_path);
}

t_ui_img *ui_paint_elem(t_ui_elem *e, int r, int g, int b, int a)
{
	t_ui_img *new = SDL_CreateTexture(e->win, EL_RENDERER(e),
								   SDL_TEXTUREACCESS_STATIC,
								   e->actual_sizes.w, e->actual_sizes.h);
}

//Creates an elem with given parameters. All other settings will be negative
// or set to nonexistent, excepted for sensible. You can set them manually or
// use the appropriate functions.
t_ui_elem *ui_create_virgin_elem(t_percentage x, t_percentage y, t_percentage w,
                                 t_percentage h, char display_priority)
{
	t_ui_elem *new = ui_secure_malloc(sizeof(t_ui_elem));

	new->proportions.x = x;
	new->proportions.y = y;
	new->proportions.w = w;
	new->proportions.h = h;
	new->display_priority = display_priority;
	new->next = NULL;
	new->prev = NULL;
	new->img = NULL;
	new->sensible = UI_TRUE;
	new->sensible_zones = NULL;
	new->has_sub_hovers = UI_FALSE;
	new->hover_func = NULL;
	new->has_sub_clicks = UI_FALSE;
	new->click_func = NULL;
	new->sub_elems = NULL;
}
