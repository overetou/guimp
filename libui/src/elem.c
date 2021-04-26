//
// Created by osc on 22/04/2021.
//
#include "ui.h"

//You have to specify the window for wich the img will be active. If you want
// to use the same image for several window, call this function several time.
//I know, this is not ideal, but that's how SDL works.
t_ui_img *ui_load_img(t_ui_win *win, const char *img_path)
{
	return IMG_LoadTexture(win->rend, img_path);
}

//Creates an elem with given parameters. All other settings will be negative
// or set to nonexistent, excepted for sensible. You can set them manually or
// use the appropriate functions.
t_ui_elem *ui_create_virgin_elem(t_percentage x, t_percentage y, t_percentage w,
                                 t_percentage h, char display_priority,
                                 void (*display_func)(t_ui_elem *))
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
	new->display_func = display_func;
	new->sensible = UI_TRUE;
	new->has_sub_hovers = UI_FALSE;
	new->hover_func = NULL;
	new->has_sub_clicks = UI_FALSE;
	new->click_func = NULL;
	new->sub_elems = NULL;
	return new;
}

//Incorporates the described element inside its parent. Returns the new
// element's pointer for optionnal use.
t_ui_elem *ui_add_elem(t_ui_elem *parent, t_percentage x, t_percentage y,
					   t_percentage w, t_percentage h,
					   char disp_priority, void(*display_func)(t_ui_elem*),
					   UI_BOOL sensible, void(*hover_func)(void*),
					   void(*click_func)(void*))
{
	t_ui_elem *new = ui_secure_malloc(sizeof(t_ui_elem));

	new->parent = parent;
	new->win = parent->win;
	new->proportions.x = x;
	new->proportions.y = y;
	new->proportions.w = w;
	new->proportions.h = h;
	new->display_priority = disp_priority;
	new->display_func = display_func;
	new->img = NULL;
	new->sensible = sensible;
	new->nb_sensible_zones = 0;
	new->has_sub_hovers = UI_FALSE;
	new->hover_func = hover_func;
	new->has_sub_clicks = UI_FALSE;
	new->click_func = click_func;
	new->sub_elems = NULL;
	add_link_to_list((t_link**)(&(parent->sub_elems)), (t_link*)new);//TODO:
	// replace this by a specialised function that puts the link in its
	// rightful pos in the queue, based on its display priority. Name of the
	// func: ui_incorporate_elem. Note: if there is already an elem with the
	// same display priority in the queue, the arriving elem is placed first and
	// the contested + all of its followers see their display priority
	// incremented.
	ui_infer_elem_actual_size(new);
	return new;
}

void ui_remove_elem(t_ui_elem *e)
{
	remove_link_from_list((t_link**)(&(e->parent->sub_elems)), (t_link*)e);
	/*if (e->img)
		SDL_DestroyTexture(e->img);*/
	while (e->sub_elems)
		ui_remove_elem(e->sub_elems);
	free(e);
}

void ui_transfer_elem(t_ui_elem *new_parent, t_ui_elem *e,
					  char new_disp_priority)
{
	remove_link_from_list((t_link**)(&(e->parent->sub_elems)), (t_link*)e);
	e->display_priority = new_disp_priority;
	add_link_to_list((t_link**)(&(new_parent->sub_elems)), (t_link*)e);
	//TODO: same as in add elem, replace the func.
	e->parent = new_parent;
}

void ui_display_elem(t_ui_elem *e)
{
	e->display_func(e);
}

void resolve_and_display_elem(t_ui_elem *e)
{
	if (e->display_priority)
	{
		//ui_infer_elem_actual_size(e);
		ui_display_elem(e);
		e = e->sub_elems;
		while (e)
		{
			resolve_and_display_elem(e);
			e = e->next;
		}
	}
}
