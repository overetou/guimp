#include "ui.h"

void	ui_free_text_space_store(void *to_free)
{
	t_text_space_store *store = to_free;
	free(store->text);
	free(to_free);
}

int		starting_pos_of_visible_start(t_ui_elem *line, t_text_space_store *store)
{
	char	s[store->visible_text_start + 1];
	int		starting_pos_in_px;

	mem_copy(s, store->text, store->visible_text_start);
	s[store->visible_text_start] = '\0';
	TTF_SizeText(UI_FONT(line, store->police_font), s, &starting_pos_in_px, NULL);
	return starting_pos_in_px;
}

int		max_width_from_visible_start(t_ui_elem *line, t_text_space_store *store)
{
	int		fit_in = 0;
	int		added;
	char	*traveler = store->text + store->visible_text_start;

	while (fit_in <= store->sub_rect.w)
	{
		TTF_GlyphMetrics(UI_FONT(line, store->police_font), *traveler, NULL, NULL, NULL, NULL, &added);
		fit_in += added;
		traveler++;
	}
	store->visible_text_end = traveler - 1;
	return fit_in - added;
}

void	display_too_large_text(t_ui_elem *line, t_text_space_store *store, int height)
{
	SDL_Rect	dest_rect;
	SDL_Rect	src_rect;
	int				tmp = max_width_from_visible_start(line, store);

	src_rect.x = starting_pos_of_visible_start(line, store);
	src_rect.y = 0;
	src_rect.w = tmp;
	src_rect.h = height;
	dest_rect.x = line->actual_dimensions.x + store->sub_rect.x;
	dest_rect.y = line->actual_dimensions.y + store->sub_rect.y;
	dest_rect.w = tmp;
	dest_rect.h = height;
	SDL_RenderCopy(UI_EL_REND(line), store->text_img, &src_rect, &dest_rect);
}

void	ui_display_text_space(t_ui_elem *line)
{
	t_text_space_store	*store = line->store;
	SDL_Color						bg = {100, 100, 100, UI_ALPHA_OPAQUE};
	SDL_Color						fg = {210, 210, 210, UI_ALPHA_OPAQUE};
	SDL_Rect						cursor_rect = {0, 0, 1, line->actual_dimensions.h};
	int									tmp;
	int									height;

	ui_colorize_elem(line, UI_EXPAND_COLOR(bg));
	if (store->text_len > 0)
	{
		store->text_img = ui_text_to_texture(store->text + store->visible_text_start, store->police_font, &fg, &bg, line);
		TTF_SizeText(UI_FONT(line, store->police_font), store->text + store->visible_text_start, &tmp, &height);
		if (tmp > store->sub_rect.w)
			display_too_large_text(line, store, height);
		else
		{
			store->visible_text_end = store->text + store->text_len;
			ui_display_img_at_absolute_pos(line, store->text_img, store->sub_rect.x, store->sub_rect.y);
		}
		SDL_DestroyTexture(store->text_img);
	}
	if (store->pos >= 0)
	{
		cursor_rect.x = store->sub_rect.x + store->cursor_pixel_pos;
		ui_display_absolute_rect_relative_to_elem(line, &cursor_rect, &fg);
	}
}

void	ui_text_line_unfocus(t_ui_elem *line)
{
	t_text_space_store	*store = line->store;
	
	store->pos = -1;
	refresh_win(UI_EL_WIN(line));
}

void	find_cursor_min_overstep(t_ui_elem *line, t_text_space_store *store, int *current_pixel_pos,
		int *current_char_pos, int *tmp, int x)
{
	while (*current_pixel_pos <= x)
	{
		TTF_GlyphMetrics(UI_FONT(line, store->police_font),
				store->text[*current_char_pos], NULL, NULL, NULL, NULL, tmp);
		(*current_char_pos)++;
		(*current_pixel_pos) += *tmp;
	}
}

void	ui_text_line_put_cursor_at_new_pos_from_x(t_ui_elem *line, int x)
{
	t_text_space_store	*store = line->store;
	char								save;
	int									text_img_width, tmp, current_pixel_pos = 0;
	int									current_char_pos = store->visible_text_start;

	if (x <= store->sub_rect.x + line->actual_dimensions.x || store->text_len == 0)
	{
		store->pos = 0;
		store->cursor_pixel_pos = 0;
	}
	else
	{
		save = *(store->visible_text_end);
		*(store->visible_text_end) = '\0';
		TTF_SizeText(UI_FONT(line, store->police_font), store->text, &text_img_width, NULL);
		*(store->visible_text_end) = save;
		x -= line->actual_dimensions.x + store->sub_rect.x;
		if (x >= text_img_width)
		{
			store->pos = store->visible_text_end - store->text;
			store->cursor_pixel_pos = text_img_width;
		}
		else
		{
			find_cursor_min_overstep(line, store, &current_pixel_pos, &current_char_pos, &tmp, x);
			store->cursor_pixel_pos = current_pixel_pos - tmp;
			store->pos = current_char_pos - 1;
		}
	}
	refresh_win(UI_EL_WIN(line));
}

int		get_text_pixel_size(t_ui_elem *e, int police_index, const char *text)
{
	int	result;

	TTF_SizeText(UI_FONT(e, police_index), text, &result, NULL);
	return result;
}

//TODO: Make sure that we can never get here with a negative pos.
void	update_visible_start(t_ui_elem *line, t_text_space_store *store)
{
	//calculer la taille du texte jusqu'a pos. Tant que cette taille est superieure a sub_rect->width, incrementer visible_text_start.
	char	saved = store->text[store->pos];
	store->text[store->pos] = '\0';

	while (get_text_pixel_size(line, store->police_font, store->text + store->visible_text_start) > store->sub_rect.w)
		(store->visible_text_start)++;
	store->text[store->pos] = saved;
}

void		update_cursor_px_pos_from_chr_pos(t_ui_elem *line)
{
	t_text_space_store	*store = line->store;
	char saved = store->text[store->pos];
	store->text[store->pos]	= '\0';
	TTF_SizeText(UI_FONT(line, store->police_font), store->text + store->visible_text_start,
			&(store->cursor_pixel_pos), NULL);
	store->text[store->pos]	= saved;
}

void	insert_text(t_ui_elem *line, const char *to_insert)
{
	t_text_space_store	*store = line->store;
	int									to_insert_len = ui_strlen(to_insert);
	//printf("to_insert_len = %d\n", to_insert_len);
	int									full_size = store->text_len + to_insert_len;
	//printf("full_size = %d\n", full_size);
	char								*new_text = ui_secure_malloc(full_size + 1);

	mem_copy(new_text, store->text, store->pos);
	mem_copy(new_text + store->pos, to_insert, to_insert_len);
	mem_copy(new_text + store->pos + to_insert_len, store->text + store->pos, store->text_len - store->pos);
	new_text[full_size] = '\0';
	free(store->text);
	store->text = new_text;
	store->text_len = full_size;
	store->pos += to_insert_len;
	update_visible_start(line, store);
	update_cursor_px_pos_from_chr_pos(line);
	refresh_win(UI_EL_WIN(line));
}

//Removes count chars from line text, starting from pos and going back. No checks but put a print to quickly identify the problem.
void	remove_text(t_ui_elem *line, int count)
{
	t_text_space_store	*store = line->store;

	if (count > store->pos)
		return;
	if (store->pos == store->visible_text_start + 1)
	{
		if (store->visible_text_start != 0)
			(store->visible_text_start)--;
		(store->visible_text_end)--;
	}
	int	new_len = store->text_len - count;
	//printf("new_len = %d\n", new_len);
	char	*new_text = ui_secure_malloc(new_len + 1);
	mem_copy(new_text, store->text, store->pos - count);
	//printf("Copied %d first letters from %s\n", store->pos - count, store->text);
	mem_copy(new_text + store->pos - count, store->text + store->pos, store->text_len - store->pos);
	//printf("Copied %d first letters from %s\n", store->text_len - store->pos, store->text + store->pos);
	free(store->text);
	new_text[new_len] = '\0';
	store->text = new_text;
	store->text_len = new_len;
	store->pos -= count;
	if (store->visible_text_start > store->text_len)
		store->visible_text_start = store->text_len;
	update_cursor_px_pos_from_chr_pos(line);
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
			if (ev->key.keysym.sym == SDLK_BACKSPACE)
				remove_text(ui->event_handling_store, 1);
			break;
		case SDL_TEXTINPUT:
			insert_text(ui->event_handling_store, ev->text.text);
			break;
	}
}

void	ui_text_space_clicked(t_ui_elem *e, SDL_MouseButtonEvent *ev)
{
	t_ui	*ui = ((t_ui_win*)(e->win))->ui;

	(void)ev;
	//((t_slider_store*)(ui->event_handling_store))->previous_event_handling_func = ui->event_handler_func;
	ui->event_handling_store = e;
	ui_change_event_handler(ui, ui_text_linefocused_event_handler);
	ui_text_line_put_cursor_at_new_pos_from_x(e, ev->x);
}

t_ui_elem	*ui_create_text_line_input(t_ui_elem *parent, char *text, int x, int y, int w, int h)
{
	t_ui_elem			*new;
	t_text_space_store	*store;

	new = ui_add_elem(parent, x, y, 0, 0, 1, ui_display_text_space, UI_TRUE,
	ui_free_text_space_store, ui_resolve_keep_actual_dimensions);
	new->actual_dimensions.w = w;
	new->actual_dimensions.h = h;
	new->store = ui_secure_malloc(sizeof(t_text_space_store));
	store = new->store;
	store->text = text;
	store->text_len = ui_strlen(text);
	store->pos = -1;
	store->police_font = 0;
	store->sub_rect.x = ui_get_percentage_of_int(new->actual_dimensions.w, 10);
	store->sub_rect.y = ui_get_percentage_of_int(new->actual_dimensions.h, 10);
	store->sub_rect.w = ui_get_percentage_of_int(new->actual_dimensions.w, 80);
	store->sub_rect.h = ui_get_percentage_of_int(new->actual_dimensions.h, 80);
	store->sensible_zone.x = 0;
	store->sensible_zone.y = 0;
	store->sensible_zone.w = w;
	store->sensible_zone.h = h;
	store->visible_text_start = 0;
	ui_add_clickable_zones(new, &(store->sensible_zone), ui_text_space_clicked, 1,
	ui_resolve_keep_fixed_dimensions);
	return new;
}
