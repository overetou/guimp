#include "ui.h"

/* void	ui_free_text_space_store(void *to_free)
{
	(void)to_free;
} */

void	ui_display_text_space(t_ui_elem *e)
{
	t_text_space_store	*store = e->store;
	SDL_Color			bg = {100, 60, 60, UI_ALPHA_OPAQUE};
	SDL_Color			fg = {250, 210, 210, UI_ALPHA_OPAQUE};
	char				tmp[store->pos + 1];
	int					text_size;
	SDL_Rect			cursor_rect = {0, 0, e->actual_dimensions.h, 3};

	ui_colorize_elem(e, UI_EXPAND_COLOR(bg));
	store->text_img = ui_text_to_texture(store->text, store->police_font, &fg, &bg, e);
	ui_display_img_at_absolute_pos(e, store->text_img, store->sub_rect.x, store->sub_rect.y);
	//TODO: verifier que l'image n'est pas trop grande. Sinon n'afficher qu'une partie de l'image.
	SDL_DestroyTexture(store->text_img);
	if (store->pos >= 0)
	{
		mem_copy(tmp, store->text, store->pos);
		tmp[store->pos] = '\0';
		text_size = TTF_SizeText(UI_FONT(e, store->police_font), tmp, &text_size, NULL);
		cursor_rect.x = store->cursor_pixel_pos;
		ui_display_absolute_rect_relative_to_elem(e, &cursor_rect, &fg);
	}
}

void	ui_text_line_unfocus(t_ui_elem *line)
{
	t_text_space_store	*store = line->store;
	
	store->pos = -1;
	ui_display_text_space(line);
}

void	ui_text_line_put_cursor_at_new_pos_from_x(t_ui_elem *line, int x)
{
	t_text_space_store	*store = line->store;
	int					text_img_width;
	int					current_char_pos = 0;
	int					current_pixel_pos = 0;
	int					tmp;
	char				dummy_text[] = "x\0";

	printf("x considered to be the start of the subrect: %d. Sould be 110.\n x straight from args = %d.\n",
			line->actual_dimensions.x + store->sub_rect.x, x);
	if (x <= store->sub_rect.x + line->actual_dimensions.x)
	{
		puts("Deducted pos of the curor is 0.");
		store->pos = 0;
	}
	else
	{
		SDL_QueryTexture(store->text_img, NULL, NULL, &text_img_width, NULL);
		x -= line->actual_dimensions.x + store->sub_rect.x;
		printf("x = %d after removal of the start of the sub rect.\n", x);
		if (x >= text_img_width)
		{
			store->pos = store->text_len;
			printf("Clicked after the text. pos = %d.\n", store->pos);
		}
		else
		{
			puts("Clicked on the text. Need to calculate the pos.");
			while (current_pixel_pos <= x)
			{
				dummy_text[0] = store->text[current_char_pos];
				TTF_SizeText(UI_FONT(line, store->police_font), dummy_text, &tmp, NULL);
				current_char_pos++;
				current_pixel_pos += tmp;
			}
			store->cursor_pixel_pos = current_pixel_pos - tmp;
			store->pos = current_char_pos - 1;
			printf("Calculated pos = %d.\n", store->pos);
		}
	}
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
				ui_text_line_put_cursor_at_new_pos_from_x(ui->event_handling_store, ((SDL_MouseButtonEvent*)ev)->x);
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
//	ui_change_event_handler(((t_ui_win*)(e->win))->ui, ui_text_linefocused_event_handler);
	ui_text_line_put_cursor_at_new_pos_from_x(e, ev->x);
}

t_ui_elem	*ui_create_text_line_input(t_ui_elem *parent, char *text, int x, int y, int w, int h)
{
	t_ui_elem			*new;
	t_text_space_store	*store;

	new = ui_add_elem(parent, x, y, 0, 0, 1, ui_display_text_space, UI_TRUE,
	free, ui_resolve_keep_actual_dimensions);
	new->actual_dimensions.w = w;
	new->actual_dimensions.h = h;
	new->store = ui_secure_malloc(sizeof(t_text_space_store));
	store = new->store;
	store->text = text;
	store->text_len = ui_strlen(text);
	printf("text_len = %d\n", store->text_len);
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
	ui_add_clickable_zones(new, &(store->sensible_zone), ui_text_space_clicked, 1,
	ui_resolve_keep_fixed_dimensions);
	puts("In the end, sensible_zone and actual dimensions of sensible_zone:");//TMP
	ui_display_rect_values(&(store->sensible_zone));//TMP
	ui_display_rect_values(&(new->sensible_zones_actual_dimensions));//TMP
	return new;
}
