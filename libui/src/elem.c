//
// Created by osc on 22/04/2021.
//
#include "ui.h"

//Creates an elem with given parameters. All other settings will be negative
// or set to nonexistent. You can set them manually or use the appropriate
// functions.
t_ui_elem *ui_create_virgin_elem(t_percentage x, t_percentage y, t_percentage w,
                                 t_percentage h, char display_priority)
{
	t_ui_elem *new = ui_secure_malloc(sizeof(t_ui_elem));

	new->surface.x = x;
	new->surface.y = y;
	new->surface.w = w;
	new->surface.h = h;
	new->display_priority = display_priority;
	new->next = NULL;
	new->prev = NULL;
	new->img = NULL;
	new->sensible = UI_FALSE;
	new->sensible_zones = NULL;
	new->has_sub_hovers = UI_FALSE;
	new->hover_func = NULL;
	new->has_sub_clicks = UI_FALSE;
	new->click_func = NULL;
	new->sub_elems = NULL;
}
