//
// Created by osc on 14/04/2021.
//
#include "ui.h"

t_ui_elem   *ui_create_button(t_ui_elem *parent, t_percentage x,
							  t_percentage y, t_percentage w, t_percentage h,
							  const char *text,
							  void (*click_func)(t_ui_elem*,
							  		SDL_MouseButtonEvent*))
{
	t_ui_elem *new;

	new = ui_add_elem(
			parent,
			x, y, w, h,
			1,
			ui_colorblock_2,
			UI_TRUE,
			free);
	new->store = malloc(sizeof(t_percent_rect));
	ui_add_clickable_zones(new, new->store, click_func, 1);
}
