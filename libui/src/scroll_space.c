#include "ui.h"

void	free_sub_layer_store(void *to_delete)
{
	t_sub_layer_store	*store = to_delete;

	SDL_DestroyTexture(store->target);
	free(to_delete);
}

//This function must be called on the sub_layer of a scroll space. x and y will
//be added, to the existing pos, and will be automatically limited to max and min values.
void	ui_move_sub_layer_vision(t_ui_elem *sub_layer, int x, int y)
{
	t_sub_layer_store	*store = sub_layer->store;

	if (store->virtual_space.x + x < 0)
		store->virtual_space.x = 0;
	else if (store->virtual_space.x + x > store->virtual_space.w - 
			sub_layer->actual_dimensions.w)
		store->virtual_space.x = store->virtual_space.w -
			sub_layer->actual_dimensions.w;
}

void			ui_resolve_sublayer_dimensions(t_ui_elem *sub_layer)
{
	t_ui_elem					*child = sub_layer->sub_elems;
	t_sub_layer_store	*store = sub_layer->store;

	SDL_DestroyTexture(store->target);
	store->target = SDL_CreateTexture(UI_EL_REND(scroll_space),
			UI_EL_UI(scroll_space)->default_pixel_format, SDL_TEXTUREACCESS_TARGET,
			child->actual_dimensions.w, child->actual_dimensions.h);
	//TODO (bonus): find the most extreme dimensions + placement of each children and
	//resize the sub_layer accordingly
	sub_layer->actual_dimensions.w = child->actual_dimensions.w;
	sub_layer->actual_dimensions.h = child->actual_dimensions.h;
}

void			ui_add_sub_layer(t_ui_elem *parent, int w, int h)
{
	t_ui_elem *new = ui_secure_malloc(sizeof(t_ui_elem));
	t_sub_layer_store	*store;

	new->parent = parent;
	new->win = parent->win;
	new->display_priority = 0;
	new->sensible = UI_TRUE;
	new->nb_sensible_zones = 1;
	new->has_sub_hovers = UI_FALSE;
	new->has_sub_clicks = UI_FALSE;
	new->click_func = NULL;
	new->sub_elems = NULL;
	incorporate_sub_elem(&(parent->sub_elems), new);
	new->elem_dimensions_resolution_func = ui_resolve_sublayer_dimensions;
	new->actual_dimensions.x = 0;
	new->actual_dimensions.y = 0;
	new->actual_dimensions.w = w;
	new->actual_dimensions.h = h;
	new->store = ui_secure_malloc(sizeof(t_sub_layer_store));
	store = new->store;
	store->virtual_space.x = 0;
	store->virtual_space.y = 0;
	store->target = SDL_CreateTexture(UI_EL_REND(parent),
			UI_EL_UI(parent)->default_pixel_format, SDL_TEXTUREACCESS_TARGET, w, h);
	new->free_store_func = free_sub_layer_store;
}

void	ui_display_scroll_space(t_ui_elem *e)
{
	t_sub_layer_store	*store = scroll_space->store;

	SDL_SetRenderTarget(UI_EL_REND(e), store->target);
	ui_display_elem(e->sub_elems);
	SDL_SetRenderTarget(UI_EL_REND(e), NULL);
	ui_display_img_at_absolute_pos(e, store->target, 0, 0);
}

void	ui_scroll_space_clicked(t_ui_elem *e, SDL_MouseButtonEvent *ev)
{
	//On va appeller la fonction de retransmission de clic sur le sub_layer. Mais avant
	//ca, on modifie les valeur de x et de y du SDL_MouseButtonEvent pour qu'il soit
	//correctement positionne au sein de l'espace virtuel.
	t_ui_elem	*sub_layer = e->sub_elems;
	t_sub_layer_store	*store = sub_layer->store;

	ev->x += store->virtual_space.x - e->actual_dimensions.x;
	ev->y += store->virtual_space.y - e->actual_dimensions.y;
	ui_transmit_click_event(sub_layer);
}

t_ui_elem	*ui_get_scroll_space_sub_layer(t_ui_elem *e)
{
	return e->sub_elems;
}

//Do not use this elem as a parent. Use his sub_elem instead. ex: scrollpace->sub_elems
//To retrieve the childrens of scroll space, use ui_scroll_space_get_sub_elems.
t_ui_elem	*ui_create_scroll_space(t_ui_elem *parent, int x, int y, int visible_w,
		int visible_h, int virtual_w, int virtual_h)
{
	t_ui_elem	*new;
	SDL_Rect	*sensible_zone;

	new = ui_add_elem(parent, x, y, visible_w, visible_h, 1, ui_display_scroll_space,
			UI_TRUE, free, ui_resolve_as_percentages);
	new->store = ui_secure_malloc(sizeof(SDL_Rect));
	sensible_zone = new->store;
	sensible_zone->x = 0;
	sensible_zone->y = 0;
	sensible_zone->w = 100;
	sensible_zone->h = 100;
	ui_add_sub_layer(new, virtual_w, virtual_h);
	ui_add_clickable_zones(new, sensible_zone, ui_scroll_space_clicked, 1,
			ui_resolve_as_percentages);
	return new;
}