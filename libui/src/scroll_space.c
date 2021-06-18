#include "ui.h"

void	ui_display_scroll_space(t_ui_elem *e)
{
	ui_display_elem(e->sub_elems);
}

void	ui_scroll_space_clicked(t_ui_elem *e, SDL_MouseButtonEvent *ev)
{

}

void	move_scroll_vision(t_ui_elem *scroll_space, int x, int y)
{
	t_scroll_space_store	*store = scroll_space->store;

	if (store->virtual_space.x + x < 0)
		store->virtual_space.x = 0;
	else if (store->virtual_space.x + x > store->virtual_space.w - 
			scroll_space->actual_dimensions.w)
		store->virtual_space.x = store->virtual_space.w -
			scroll_space->actual_dimensions.w;
}

//Once an element has been added to the scroll_space, call this func. You will then
//be good to go.
void			ui_lock_scrollable_elem(t_ui_elem *scrollable_elem)
{
	scrollable_elem->display_priority = 0;
}

t_ui_elem	*ui_create_scroll_space(t_ui_elem *parent, int x, int y, int w, int h)
{
	t_ui_elem							*new;
	t_scroll_space_store	*store;

	new = ui_add_elem(parent, x, y, w, h, 1, ui_display_scroll_space, UI_TRUE,
			free, ui_resolve_as_percentages);
	new->store = ui_secure_malloc(sizeof(t_scroll_space_store));
	store = new->store;
	store->virtual_space.x = 0;
	store->virtual_space.y = 0;
	store->target = SDL_CreateTexture(UI_EL_REND(new), UI_EL_UI(new)->default_pixel_format,
			SDL_TEXTUREACCESS_TARGET, new->actual_dimensions.w, new->actual_dimensions.h);
	return new;
}
