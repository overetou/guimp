#include "ui.h"

void	free_scroll_space_store(void *to_delete)
{
	t_scroll_space_store	*store = to_delete;

	SDL_DestroyTexture(store->target);
	free(to_delete);
}

void	ui_display_scroll_space(t_ui_elem *e)
{
	t_scroll_space_store	*store = scroll_space->store;

	SDL_SetRenderTarget(UI_EL_REND(e), store->target);
	ui_display_elem(e->sub_elems);
	SDL_SetRenderTarget(UI_EL_REND(e), NULL);
	ui_display_img_at_absolute_pos(e, store->target, 0, 0);
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
//be good to go. Call it again every time you change the dimensions of the scroll child.
void			ui_lock_scrollable_elem(t_ui_elem *scroll_space)
{
	t_ui_elem							*child = scroll_space->sub_elems;
	t_scroll_space_store	*store = scroll_space->store;

	child->display_priority = 0;
	store->target = SDL_CreateTexture(UI_EL_REND(scroll_space),
			UI_EL_UI(scroll_space)->default_pixel_format, SDL_TEXTUREACCESS_TARGET,
			child->actual_dimensions.w,
			child->actual_dimensions.h);
}

//Don't forget to call ui_lock_scrollable_elem after you added an elem in the scroll
//	space!
t_ui_elem	*ui_create_scroll_space(t_ui_elem *parent, int x, int y, int w, int h)
{
	t_ui_elem							*new;
	t_scroll_space_store	*store;

	new = ui_add_elem(parent, x, y, w, h, 1, ui_display_scroll_space, UI_TRUE,
			free_scroll_space_store, ui_resolve_as_percentages);
	new->store = ui_secure_malloc(sizeof(t_scroll_space_store));
	store = new->store;
	store->virtual_space.x = 0;
	store->virtual_space.y = 0;
	return new;
}
