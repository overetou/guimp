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
	t_ui_color fg = {200, 200, 200, UI_ALPHA_OPAQUE};
	t_ui_color bg = {50, 50, 50, UI_ALPHA_OPAQUE};

	new = ui_add_elem(
			parent,
			x, y, w, h,
			1,
			ui_display_button,
			UI_TRUE,
			free);
	new->store = malloc(sizeof(t_ui_button_store));
	((t_ui_button_store*)(new->store))->text_img = ui_text_to_texture(
			text, 0, &fg, &bg, new);
	ui_add_clickable_zones(
			new,
			&(((t_ui_button_store*)(new->store))->sensible_zone),
			click_func,
			1);
	return new;
}
