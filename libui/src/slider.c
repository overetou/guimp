#include "ui.h"

void	ui_free_slider_store(void *to_free)
{

}

void	ui_display_slider(t_ui_elem *e)
{

}

void	ui_slider_clicked(t_ui_elem *e, SDL_MouseButtonEvent *ev)
{

}

t_ui_elem	*ui_create_slider(t_ui_elem *parent, int x, int y, int w)
{
	t_ui_elem	*new;

	new = ui_add_elem(parent, x, y, w, 0, 1, ui_display_slider, UI_TRUE,
		free, ui_resolve_w_as_percentage_keep_actual_h);
	new->store = ui_secure_malloc(sizeof(t_slider_store));
	ui_add_clickable_zones(new, &(((t_slider_store*)(new->store))->sensible_zone), ui_slider_clicked,
	1, ui_resolve_w_as_percentage_keep_actual_h);
	return new;
}