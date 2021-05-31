#include "ui.h"

void	ui_display_slider(t_ui_elem *e)
{
	t_slider_store	*store = e->store;
	SDL_Color		line_color = {160, 120, 120, UI_ALPHA_OPAQUE};
	SDL_Color		cursor_color = {140, 100, 100, UI_ALPHA_OPAQUE};
	SDL_Rect		cursor_dimensions = {e->actual_dimensions.x +
		((e->actual_dimensions.w - UI_SLIDER_CURSOR_WIDTH_IN_PX) *
	 	store->current_val / store->max_val), e->actual_dimensions.y,
		UI_SLIDER_CURSOR_WIDTH_IN_PX, e->actual_dimensions.h};

	ui_colorize_elem(e, UI_EXPAND_COLOR(line_color));
	ui_display_absoluste_colored_rect(e, &cursor_dimensions, &cursor_color);
}

void	ui_slider_drag_event_handler(t_ui *ui, SDL_Event *ev)
{
	switch (ev->type)
	{
		case SDL_QUIT:
			ui->keep_going = UI_FALSE;
			break;
		case SDL_MOUSEBUTTONUP:
			ui_remove_permafunc(ui,
			((t_slider_store*)(ui->event_handling_store))->drag_perma_func);
			ui_change_event_handler(ui,
			((t_slider_store*)(ui->event_handling_store))->previous_event_handling_func);
			break;
	}
}

void	ui_slider_perma_func(void *store)
{
	int				x, y;
	t_ui_elem		*e = store;
	t_slider_store	*e_store = e->store;

	SDL_GetMouseState(&x, &y);
	if (x <= e->actual_dimensions.x)
		e_store->current_val = 0;
	else if (x >= e->actual_dimensions.x + e->actual_dimensions.w)
		e_store->current_val = 100;
	else
		e_store->current_val = ui_get_subset_proportionnal_to_proportion(e_store->max_val, e->actual_dimensions.w, x - e->actual_dimensions.x);
	//printf("Moved slider to val %d.\n", e_store->current_val);
	ui_display_slider(e);
	ui_display_elem(((t_ui_win*)(e->win))->content);
	SDL_RenderPresent(((t_ui_win*)(e->win))->rend);
}

void	ui_slider_clicked(t_ui_elem *e, SDL_MouseButtonEvent *ev)
{
	t_perma_func_block	*new;
	t_ui					*ui = ((t_ui_win*)(e->win))->ui;
	t_slider_store			*store = e->store;

	(void)ev;
	store->previous_event_handling_func = ui->event_handler_func;
	ui_change_event_handler(ui, ui_slider_drag_event_handler);
	new = ui_add_perma_func(ui, ui_slider_perma_func, e);
	store->drag_perma_func = new;
	ui->event_handling_store = e->store;
}

t_ui_elem	*ui_create_slider(t_ui_elem *parent, int x, int y, int w, int current_cursor_val, int max_cursor_val)
{
	t_ui_elem		*new;
	t_slider_store	*store;

	new = ui_add_elem(parent, x, y, w, 0, 1, ui_display_slider, UI_TRUE,
		free, ui_resolve_w_as_percentage_keep_actual_h);
	new->actual_dimensions.h = UI_SLIDER_HEIGHT_IN_PX;
	new->store = ui_secure_malloc(sizeof(t_slider_store));
	store = new->store;
	store->current_val = current_cursor_val;
	store->max_val = max_cursor_val;
	store->sensible_zone.x = 0;
	store->sensible_zone.y = 0;
	store->sensible_zone.w = 100;
	new->sensible_zones_actual_dimensions.h = UI_SLIDER_HEIGHT_IN_PX;
	ui_add_clickable_zones(new, &(((t_slider_store*)(new->store))->sensible_zone), ui_slider_clicked,
	1, ui_resolve_w_as_percentage_keep_actual_h);
	return new;
}
