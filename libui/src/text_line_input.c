#include "ui.h"

void	ui_free_text_space_store(void *to_free)
{
	t_text_space_store *store = to_free;
	free(store->text);
	free(to_free);
}

int		ui_get_text_size_with_len(TTF_Font *font, char *text, int len)
{
	char	saved = text[len];
	int		result;

	text[len] = '\0';
	TTF_SizeText(font, text, &result, NULL);
	text[len] = saved;
	return result;
}

void	ui_display_text_space(t_ui_elem *line)
{
	t_text_space_store	*store = line->store;
	SDL_Color			bg = {100, 100, 100, UI_ALPHA_OPAQUE};
	SDL_Color			fg = {210, 210, 210, UI_ALPHA_OPAQUE};
	SDL_Rect			cursor_rect = {
		0,
		ui_calculate_start_of_center(line->actual_dimensions.h, TTF_FontHeight(UI_FONT(line, store->police_font))),
		1,
		TTF_FontHeight(UI_FONT(line, store->police_font))
	};

	ui_colorize_elem(line, UI_EXPAND_COLOR(bg));
	if (store->text_len > 0)
	{
		store->text_img = ui_text_to_texture(store->text, store->police_font, &fg, &bg, line);
		ui_display_img_at_absolute_pos(line, store->text_img, 0, 0);
		SDL_DestroyTexture(store->text_img);//TODO: This image could be kept and only replaced when the text itself is modified.
	}
	if (store->pos >= 0)
	{
		cursor_rect.x = ui_get_text_size_with_len(UI_FONT(line, store->police_font), store->text, store->pos);
		ui_display_absolute_rect_relative_to_elem(line, &cursor_rect, &fg);
	}
}

void		ui_text_line_input_change_cursor_pos(t_ui_elem *line, int new_pos)
{
	t_text_space_store	*store = line->store;
	int					px_pos;
	t_sub_layer_store	*sub_layer_store = line->parent->store;

	//printf("virtual_space = %d, %d, %d, %d\n", sub_layer_store->virtual_space.x, sub_layer_store->virtual_space.y, sub_layer_store->virtual_space.w, sub_layer_store->virtual_space.h);
	if (new_pos >= 0)
	{
		px_pos = ui_get_text_size_with_len(UI_FONT(line, store->police_font), store->text, new_pos);//TODO: this is recalculated in the display func.
		if (px_pos < sub_layer_store->virtual_space.x)
			sub_layer_store->virtual_space.x = px_pos;
		else if (px_pos >= sub_layer_store->virtual_space.x + sub_layer_store->virtual_space.w)
		{
			sub_layer_store->virtual_space.x = px_pos - sub_layer_store->virtual_space.w + 1;
		}
	}
	store->pos = new_pos;
}

void	ui_text_line_unfocus(t_ui_elem *line)
{
	t_text_space_store	*store = line->store;
	
	store->pos = -1;//No need to call ui_text_line_input_change_cursor_pos here.
	refresh_win(UI_EL_WIN(line));
}

void	insert_text(t_ui_elem *line, const char *to_insert)
{
	t_text_space_store	*store = line->store;
	int					to_insert_len = ui_strlen(to_insert);
	int					full_size = store->text_len + to_insert_len;
	char				*new_text = ui_secure_malloc(full_size + 1);

	mem_copy(new_text, store->text, store->pos);
	mem_copy(new_text + store->pos, to_insert, to_insert_len);
	mem_copy(new_text + store->pos + to_insert_len, store->text + store->pos, store->text_len - store->pos);
	new_text[full_size] = '\0';
	free(store->text);
	store->text = new_text;
	store->text_len = full_size;
	ui_text_line_input_change_cursor_pos(line, store->pos + to_insert_len);
	to_insert_len = ui_get_text_size_with_len(UI_FONT(line, store->police_font), new_text, full_size);
	//from here on to_insert_len represents a width.
	if (to_insert_len > line->actual_dimensions.w)
	{
		line->actual_dimensions.w = to_insert_len + 1;
		line->parent->elem_dimensions_resolution_func(line->parent);
	}
	refresh_win(UI_EL_WIN(line));
}

//Removes count chars from line text, starting from pos and going back. No checks but put a print to quickly identify the problem.
void	remove_text(t_ui_elem *line, int count)
{
	t_text_space_store	*store = line->store;
	int	new_len = store->text_len - count;
	char	*new_text = ui_secure_malloc(new_len + 1);

	if (count > store->pos)
		return;
	mem_copy(new_text, store->text, store->pos - count);
	mem_copy(new_text + store->pos - count, store->text + store->pos, store->text_len - store->pos);
	free(store->text);
	new_text[new_len] = '\0';
	store->text = new_text;
	store->text_len = new_len;
	ui_text_line_input_change_cursor_pos(line, store->pos - count);
	refresh_win(UI_EL_WIN(line));
}

void	line_move_cursor(t_ui_elem *line, int movement)
{
	t_text_space_store	*store = line->store;

	if (store->pos + movement < 0)
		ui_text_line_input_change_cursor_pos(line, 0);
	else if (store->pos + movement > store->text_len)
		ui_text_line_input_change_cursor_pos(line, store->text_len);
	else
		ui_text_line_input_change_cursor_pos(line, store->pos + movement);
	refresh_win(UI_EL_WIN(line));
}

void	ui_text_line_put_cursor_at_new_pos_from_x(t_ui_elem *line, int x)
{
	t_text_space_store	*store = line->store;
	int									char_pos = 0;
	int									px_pos = 0;
	int									tmp;

	tmp = ui_get_text_size_with_len(UI_FONT(line, store->police_font), store->text, store->text_len);
	//printf("x to overcome = %d, initial px_pos = %d, max_len = %d\n", x, px_pos, px_pos + tmp);
	if (x > px_pos + tmp)
		char_pos = store->text_len;
	else
	{
		while (px_pos <= x)
		{
			TTF_GlyphMetrics(UI_FONT(line, store->police_font), store->text[char_pos], NULL, NULL, NULL, NULL, &tmp);
			px_pos += tmp;
			char_pos++;
		}
		char_pos--;
	}
	ui_text_line_input_change_cursor_pos(line, char_pos);
	//printf("Found char pos: %d.\n", store->pos);
	refresh_win(UI_EL_WIN(line));
}

void	ui_text_linefocused_event_handler(t_ui *ui, SDL_Event *ev)
{
	switch (ev->type)
	{
		case SDL_QUIT:
			ui->keep_going = UI_FALSE;
			break;
		case SDL_MOUSEBUTTONDOWN:
			if (ui_is_point_in_rect(ev->button.x, ev->button.y,
						&(((t_ui_elem*)(ui->event_handling_store))->actual_dimensions)))
				ui_text_line_put_cursor_at_new_pos_from_x(ui->event_handling_store, ev->button.x);
			else
			{
				ui_text_line_unfocus(ui->event_handling_store);
				ui_change_event_handler(ui, ui_default_event_handler);
				ui->event_handler_func(ui, ev);
			}				
			break;
		case SDL_KEYDOWN:
			switch (ev->key.keysym.sym)
			{
				case SDLK_BACKSPACE:
					remove_text(ui->event_handling_store, 1);
					break;
				case SDLK_LEFT:
					line_move_cursor(ui->event_handling_store, -1);
					break;
				case SDLK_RIGHT:
					line_move_cursor(ui->event_handling_store, 1);
					break;
			}
			break;
		case SDL_TEXTINPUT:
			insert_text(ui->event_handling_store, ev->text.text);
			break;
	}
}

void	ui_text_space_clicked(t_ui_elem *e, SDL_MouseButtonEvent *ev)
{
	t_ui	*ui = ((t_ui_win*)(e->win))->ui;

	ui->event_handling_store = e;
	ui_change_event_handler(ui, ui_text_linefocused_event_handler);
	ui_text_line_put_cursor_at_new_pos_from_x(e, ev->x);
}

//w and h will be treated as percentages.
t_ui_elem	*ui_create_text_line_input(t_ui_elem *parent, char *text, int x, int y, int w, int h)
{
	t_ui_elem			*scroll_space;
	t_ui_elem			*new;
	t_text_space_store	*store;

	scroll_space = ui_create_scroll_space(parent, x, y, w, h, ui_get_percentage_of_int(parent->actual_dimensions.w, w), ui_get_percentage_of_int(parent->actual_dimensions.h, h));
	printf("scroll_space dims: %d, %d, %d, %d\n", scroll_space->actual_dimensions.x, scroll_space->actual_dimensions.y, scroll_space->actual_dimensions.w, scroll_space->actual_dimensions.h);
	//printf("sub_layer dims: %d, %d, %d, %d\n", scroll_space->sub_elems->actual_dimensions.x, scroll_space->sub_elems->actual_dimensions.y, scroll_space->sub_elems->actual_dimensions.w, scroll_space->sub_elems->actual_dimensions.h);
	new = ui_add_elem(scroll_space->sub_elems, 0, 0, 100, 100, 1, ui_display_text_space, UI_TRUE,
	ui_free_text_space_store, ui_resolve_as_percentages);
	//printf("text_line dims: %d, %d, %d, %d\n", new->actual_dimensions.x, new->actual_dimensions.y, new->actual_dimensions.w, new->actual_dimensions.h);
	new->store = ui_secure_malloc(sizeof(t_text_space_store));
	store = new->store;
	store->text = text;
	store->text_len = ui_strlen(text);
	store->pos = -1;
	store->police_font = 0;
	store->sensible_zone.x = 0;
	store->sensible_zone.y = 0;
	store->sensible_zone.w = 100;
	store->sensible_zone.h = 100;
	ui_add_clickable_zones(new, &(store->sensible_zone), ui_text_space_clicked, 1,
	ui_resolve_clickable_zone_as_percentage);
	return new;
}
