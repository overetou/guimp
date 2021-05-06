//
// Created by osc on 14/04/2021.
//
#include "ui.h"

void        ui_free_button_store(void *to_free)
{
	SDL_DestroyTexture(((t_ui_button_store*)(to_free))->text_img);
	free(to_free);
}

t_ui_elem   *ui_create_button(t_ui_elem *parent, int x,
							  int y, int w, int h,
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
			ui_free_button_store, ui_resolve_as_percentages);
	new->store = ui_secure_malloc(sizeof(t_ui_button_store));
	((t_ui_button_store*)(new->store))->text_img = ui_text_to_texture(
			text, 0, &fg, &bg, new);
	((t_ui_button_store*)(new->store))->sensible_zone.x = 0;
	((t_ui_button_store*)(new->store))->sensible_zone.y = 0;
	((t_ui_button_store*)(new->store))->sensible_zone.w = 100;
	((t_ui_button_store*)(new->store))->sensible_zone.h = 100;
	ui_add_clickable_zones(
			new,
			&(((t_ui_button_store*)(new->store))->sensible_zone),
			click_func,
			1, ui_resolve_as_percentages);
	return new;
}
