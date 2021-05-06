//
// Created by osc on 22/04/2021.
//
#include "ui.h"

//You have to specify the window for wich the store will be active. If you want
// to use the same image for several window, call this function several time.
//I know, this is not ideal, but that's how SDL works.
t_ui_img *ui_load_img(t_ui_win *win, const char *img_path)
{
	return IMG_LoadTexture(win->rend, img_path);
}

//Creates an elem with given parameters. All other settings will be negative
// or set to nonexistent, excepted for sensible. You can set them manually or
// use the appropriate functions.
t_ui_elem *ui_create_virgin_elem(int x, int y, int w,
                                 int h, t_ui_win *win,
                                 char display_priority,
                                 void (*display_func)(t_ui_elem *))
{
	t_ui_elem *new = ui_secure_malloc(sizeof(t_ui_elem));

	new->relative_dimensions.x = x;
	new->relative_dimensions.y = y;
	new->relative_dimensions.w = w;
	new->relative_dimensions.h = h;
	new->win = win;
	new->display_priority = display_priority;
	new->next = NULL;
	new->prev = NULL;
	new->store = NULL;
	new->display_func = display_func;
	new->sensible = UI_TRUE;
	new->has_sub_hovers = UI_FALSE;
	new->hover_func = NULL;
	new->has_sub_clicks = UI_FALSE;
	new->click_func = NULL;
	new->nb_sensible_zones = 0;
	new->sub_elems = NULL;
	new->parent = NULL;
	return new;
}

//TODO: This could be optimised with better classification algorithms but as
// it is not supposed to scale madly maybe it is fine to leave it as is.
// However it is expected that people may always pass 1 as display priority.
// In such a case, it may be good to keep a pointer on the 1 elem to operate
// smoothly.
static void incorporate_sub_elem(t_ui_elem **list, t_ui_elem *to_incorporate)
{
	t_ui_elem *traveler;

	if (*list == NULL)
		init_list((t_link**)list, (t_link*)to_incorporate);
	else
	{
		traveler = *list;
		if (to_incorporate->display_priority == 0)
			(void)to_incorporate;/*TODO: Add our little friend efficiently.*/
		else
		{
			while (to_incorporate->display_priority <= traveler->display_priority)
			{
				if (traveler->next)
					traveler = traveler->next;
				else
				{
					list_add_link_at_end((t_link*)traveler, (t_link*)to_incorporate);
					return;
				}
			}
			if (traveler == *list)
				list_add_link_at_start((t_link**)list, (t_link*)to_incorporate);
			else
				list_add_link_in_the_middle((t_link*)traveler, (t_link*)to_incorporate);
		}
	}
}

//Incorporates the described element inside its parent. Returns the new
// element's pointer for optional use.
t_ui_elem *
ui_add_elem(t_ui_elem *parent, int x, int y, int w,
            int h, char disp_priority,
            void (*display_func)(t_ui_elem *), t_ui_bool sensible,
            void (*store_free_func)(void *))
{
	t_ui_elem *new = ui_secure_malloc(sizeof(t_ui_elem));

	new->parent = parent;
	new->win = parent->win;
	new->relative_dimensions.x = x;
	new->relative_dimensions.y = y;
	new->relative_dimensions.w = w;
	new->relative_dimensions.h = h;
	new->display_priority = disp_priority;
	new->display_func = display_func;
	new->store = NULL;
	new->sensible = sensible;
	new->nb_sensible_zones = 0;
	new->has_sub_hovers = UI_FALSE;
	new->hover_func = NULL;
	new->has_sub_clicks = UI_FALSE;
	new->click_func = NULL;
	new->sub_elems = NULL;
	incorporate_sub_elem(&(parent->sub_elems), new);
	ui_infer_elem_actual_size(new);
	new->free_store_func = store_free_func;
	return new;
}

void ui_remove_elem(t_ui_elem *e)
{
	remove_link_from_list((t_link**)(&(e->parent->sub_elems)), (t_link*)e);
	e->free_store_func(e->store);
	while (e->sub_elems)
		ui_remove_elem(e->sub_elems);
	free(e);
}

void ui_transfer_elem(t_ui_elem *new_parent, t_ui_elem *e,
					  char new_disp_priority)
{
	remove_link_from_list((t_link**)(&(e->parent->sub_elems)), (t_link*)e);
	e->display_priority = new_disp_priority;
	incorporate_sub_elem(&(new_parent->sub_elems), e);
	e->parent = new_parent;
}

void ui_display_elem(t_ui_elem *e)
{
	e->display_func(e);
}

void display_elem(t_ui_elem *e)
{
	e->display_func(e);
	e = e->sub_elems;
	while (e && e->display_priority)
	{
		display_elem(e);
		e = e->next;
	}
}
