#include "ui.h"

/* void	ui_free_text_space_store(void *to_free)
{
	(void)to_free;
} */

void	ui_display_text_space(t_ui_elem *e)
{
	t_text_space_store	*store = e->store;
	SDL_Color	bg = {100, 60, 60, UI_ALPHA_OPAQUE};
	SDL_Color	fg = {250, 210, 210, UI_ALPHA_OPAQUE};
	char		tmp[store->pos + 1];
	int			text_size;
	SDL_Rect	cursor_rect = {0, 0, e->actual_dimensions.h, 3};

	ui_colorize_elem(e, UI_EXPAND_COLOR(bg));
	store->text_img = ui_text_to_texture(store->text, store->police_font, &fg, &bg, e);
	ui_display_img(e, store->text_img, store->sub_rect.x, store->sub_rect.y);
	//TODO: verifier que l'image n'est pas trop grande. Sinon n'afficher qu'une partie de l'image.
	if (store->pos >= 0)
	{
		mem_copy(tmp, store->text, store->pos);
		tmp[store->pos] = '\0';
		text_size = TTF_SizeText(UI_FONT(e, store->police_font), tmp, &text_size, NULL);
		cursor_rect.x = text_size;
		ui_display_absolute_rect_relative_to_elem(e, &cursor_rect, &fg);
	}
}

void	ui_text_line_unfocus(t_ui_elem *line)
{
	t_text_space_store	*store = line->store;
	
	store->pos = -1;
	ui_display_text_space(line);
}

void	ui_text_line_put_cursor_at_pos(t_ui_elem *line, int pos)
{
	t_text_space_store	*store = line->store;

	store->pos = pos;
	ui_display_text_space(line);
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
			puts(((SDL_TextInputEvent*)ev)->text);
			break;
	}
}

void	ui_text_space_clicked(t_ui_elem *e, SDL_MouseButtonEvent *ev)
{
	(void)ev;
	ui_change_event_handler(((t_ui_win*)(e->win))->ui, ui_text_linefocused_event_handler);
	ui_text_line_put_cursor_at_pos(e, ev->x);
}

t_ui_elem	*ui_create_text_line_input(t_ui_elem *parent, int x, int y, int w, int h)
{
	t_ui_elem			*new;
	t_text_space_store	*store;

	new = ui_add_elem(parent, x, y, 0, 0, 1, ui_display_text_space, UI_TRUE,
	free, ui_resolve_keep_actual_dimensions);
	new->actual_dimensions.w = w;
	new->actual_dimensions.h = h;
	new->store = ui_secure_malloc(sizeof(t_text_space_store));
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
