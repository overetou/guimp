#include "ui.h"

void	ui_display_slider(t_ui_elem *e)
{
	t_slider_store	*store = e->store;
	SDL_Color		line_color = {160, 120, 120, UI_ALPHA_OPAQUE};
	SDL_Color		cursor_color = {70, 70, 70, UI_ALPHA_OPAQUE};
	SDL_Rect		cursor_dimensions = {e->actual_dimensions.x + (e->actual_dimensions.w * store->current_val / store->max_val) - (UI_SLIDER_CURSOR_WIDTH_IN_PX / 2), e->actual_dimensions.y, UI_SLIDER_CURSOR_WIDTH_IN_PX, e->actual_dimensions.h};

	//display that background rect.
	ui_colorize_elem(e, UI_EXPAND_COLOR(line_color));
	//create another rect with absolute size for the cursor and display it.
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
			ui_change_event_handler(ui, ui_default_event_handler);
			break;
	}
}

void	ui_slider_clicked(t_ui_elem *e, SDL_MouseButtonEvent *ev)
{
	(void)ev;
	ui_change_event_handler(((t_ui_win*)(e->win))->ui, ui_slider_drag_event_handler);
	//insert permanent function pointer.
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
