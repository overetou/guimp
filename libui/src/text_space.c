#include "ui.h"

void	ui_free_text_space_store(void *to_free)
{
	(void)to_free;
}

void	ui_display_text_space(t_ui_elem *e)
{
	(void)e;
}

void	ui_text_space_clicked(t_ui_elem *e, SDL_MouseButtonEvent *ev)
{
	(void)e;
	(void)ev;

}

t_ui_elem	*ui_create_text_space(t_ui_elem *parent, int x, int y, int w, int h)
{
	t_ui_elem			*new;
	t_text_space_store	*store;

	new = ui_add_elem(parent, x, y, 0, 0, 1, ui_display_text_space, UI_TRUE,
	free, ui_resolve_keep_actual_dimensions);
	new->actual_dimensions.w = w;
	new->actual_dimensions.h = h;
	store = new->store;
	store->police_font = 0;
	store->sub_w = 80;//TODO: center the sub rectangle.
	store->sub_h = 80;
	store->sensible_zone.x = 0;
	store->sensible_zone.y = 0;
	store->sensible_zone.w = w;
	store->sensible_zone.h = h;
	ui_add_clickable_zones(new, &(store->sensible_zone), ui_text_space_clicked, 1,
	ui_resolve_keep_actual_dimensions);
	return new;
}
