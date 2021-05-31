#include "ui.h"

/* void	ui_free_text_space_store(void *to_free)
{
	(void)to_free;
} */

//TODO
void	ui_display_text_space(t_ui_elem *e)
{
	t_text_space_store	*store = e->store;
	SDL_Color	bg = {100, 60, 60, UI_ALPHA_OPAQUE};
	SDL_Color	fg = {250, 210, 210, UI_ALPHA_OPAQUE};

	ui_colorize_elem(e, UI_EXPAND_COLOR(bg));
	store->text_img = TTF_RenderText_Shaded(((t_ui*)(((t_ui_win*)(e->win))->ui))->fonts[store->police_font],
	store->text, fg, bg);
}

//TODO
void	ui_text_line_unfocus(t_ui_elem *line)
{
	(void)line;
}

//TODO
void	ui_text_line_put_cursor_at_pos(t_ui_elem *line, int x)
{
	(void)line;
	(void)x;
}

void	ui_text_linefocused_event_handler(t_ui *ui, SDL_Event *ev)
{
	switch (ev->type)
	{
		case SDL_QUIT:
			ui->keep_going = UI_FALSE;
			break;
		case SDL_MOUSEBUTTONDOWN:
			if (ui_is_point_in_rect(((SDL_MouseButtonEvent*)ev)->x, ((SDL_MouseButtonEvent*)ev)->y,
				&(((t_ui_elem*)(ui->event_handling_store))->actual_dimensions)))
				ui_text_line_put_cursor_at_pos(ui->event_handling_store, ((SDL_MouseButtonEvent*)ev)->x);
			else
			{
				ui_text_line_unfocus(ui->event_handling_store);
				ui_change_event_handler(ui,
				((t_slider_store*)(ui->event_handling_store))->previous_event_handling_func);
				ui_default_event_handler(ui, ev);
			}				
			break;
		case SDL_TEXTINPUT:
			break;
	}
}

void	ui_text_space_clicked(t_ui_elem *e, SDL_MouseButtonEvent *ev)
{
	(void)ev;
	ui_change_event_handler(((t_ui_win*)(e->win))->ui, ui_text_linefocused_event_handler);
	ui_text_line_put_cursor_at_pos(e, ev->x);
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
	store->sub_rect.x = ui_get_percentage_of_int(new->actual_dimensions.x, 10);
	store->sub_rect.y = ui_get_percentage_of_int(new->actual_dimensions.y, 10);
	store->sub_rect.w = ui_get_percentage_of_int(new->actual_dimensions.w, 80);
	store->sub_rect.h = ui_get_percentage_of_int(new->actual_dimensions.h, 80);
	store->sensible_zone.x = 0;
	store->sensible_zone.y = 0;
	store->sensible_zone.w = w;
	store->sensible_zone.h = h;
	ui_add_clickable_zones(new, &(store->sensible_zone), ui_text_space_clicked, 1,
	ui_resolve_keep_actual_dimensions);
	return new;
}
