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
	e->img = SDL_CreateTexture(e->win, EL_RENDERER(e),SDL_TEXTUREACCESS_STATIC,
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
	new->has_sub_hovers = UI_FALSE;
	new->hover_func = NULL;
	new->has_sub_clicks = UI_FALSE;
	new->click_func = NULL;
	new->sub_elems = NULL;
}

//Incorporates the described element inside its parent. Returns the new
// element's pointer for optionnal use.
t_ui_elem *ui_add_elem(t_ui_elem *parent, t_percentage x, t_percentage y,
					   t_percentage w, t_percentage h,
					   char disp_priority, t_ui_img *img, UI_BOOL sensible,
					   void(*hover_func)(void*), void(*click_func)(void*))
{
	t_ui_elem *new = ui_secure_malloc(sizeof(t_ui_elem));

	new->parent = parent;
	new->win = parent->win;
	new->proportions.x = x;
	new->proportions.y = y;
	new->proportions.w = w;
	new->proportions.h = h;
	new->display_priority = disp_priority;
	new->img = img;
	new->sensible = sensible;
	new->nb_sensible_zones = 0;
	new->has_sub_hovers = UI_FALSE;
	new->hover_func = hover_func;
	new->has_sub_clicks = UI_FALSE;
	new->click_func = click_func;
	new->sub_elems = NULL;
	add_link_to_list(&(parent->sub_elems), new);//TODO: replace this by a
	// specialised function that puts the link in its rightful pos in the
	// queue, based on its display priority. Name of the func:
	// ui_incorporate_elem. Note: if there is already an elem with the same
	// display priority in the queue, the arriving elem is placed first and
	// the contested + all of its followers see their display priority
	// incremented.
	return new;
}

void ui_remove_elem(t_ui_elem *e)
{
	remove_link_from_list(&(e->parent->sub_elems), e);
	if (e->img)
		SDL_DestroyTexture(e->img);
	while (e->sub_elems)
		ui_remove_elem(e->sub_elems);
	free(e);
}

void ui_transfer_elem(t_ui_elem *new_parent, t_ui_elem *e,
					  char new_disp_priority)
{
	remove_link_from_list(&(e->parent->sub_elems), e);
	add_link_to_list(&(new_parent->sub_elems), e);
	e->parent = new_parent;
}
