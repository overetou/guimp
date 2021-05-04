//
// Created by osc on 14/04/2021.
//
#include "ui.h"

void        ui_free_button_store(void *to_free)
{
	SDL_DestroyTexture(((t_ui_button_store*)(to_free))->text_img);
	free(to_free);
}

t_ui_elem   *ui_create_button(t_ui_elem *parent, t_percentage x,
							  t_percentage y, t_percentage w, t_percentage h,
							  const char *text,
							  void (*click_func)(t_ui_elem*,
							  		SDL_MouseButtonEvent*))
{
	t_ui_elem *new;
	t_ui_color fg = {200, 200, 200, UI_ALPHA_OPAQUE};
	t_ui_color bg = {50, 50, 50, UI_ALPHA_OPAQUE};

	new = ui_add_elem(
			parent,
			x, y, w, h,
			1,
			ui_display_button,
			UI_TRUE,
			ui_free_button_store);
	new->store = ui_secure_malloc(sizeof(t_ui_button_store));
	((t_ui_button_store*)(new->store))->text_img = ui_text_to_texture(
			text, 0, &fg, &bg, new);
	((t_ui_button_store*)(new->store))->sensible_zone.x = 0;
	((t_ui_button_store*)(new->store))->sensible_zone.y = 0;
	((t_ui_button_store*)(new->store))->sensible_zone.w = 100;
	((t_ui_button_store*)(new->store))->sensible_zone.h = 100;
	ui_add_clickable_zones(
			new,
			&(((t_ui_button_store*)(new->store))->sensible_zone),
			click_func,
			1);
	return new;
}

void    free_radio_store(void *store)
{
	t_radio_space_store *st = store;

	SDL_DestroyTexture(st->unchecked_img);
	SDL_DestroyTexture(st->checked_img);
	free(st);
}

t_ui_elem   *ui_create_radio_button_container(t_ui_elem *parent, t_percentage
x, t_percentage y, t_percentage w, t_percentage h)
{
	t_ui_elem *new;
	t_radio_space_store *st;

	new = ui_add_elem(parent, x, y, w, h, 1, ui_display_radio_space, UI_TRUE,
				   free_radio_store);
	new->store = ui_secure_malloc(sizeof(t_radio_space_store));
	st = new->store;
	st->current_choice = 0;
	return new;
}

void        radio_button_click_func(t_ui_elem *e, SDL_MouseButtonEvent *ev)
{
	t_radio_space_store     *parent_store = e->parent->store;
	t_radio_button_store    *store = e->store;
	t_radio_button_store    *traveler_store;
	t_ui_elem               *traveler;
	int                     i = 0;

	(void)ev;
	if (store->choice_index != parent_store->current_choice)
	{
		traveler = e->parent->sub_elems;
		while (i != parent_store->current_choice)
		{
			i++;
			traveler = traveler->next;
		}
		traveler_store = traveler->store;
		traveler_store->checkbox_img = &(parent_store->unchecked_img);
		ui_display_radio_button(traveler);
		parent_store->current_choice = store->choice_index;
		store->checkbox_img = &(parent_store->checked_img);
		ui_display_radio_button(e);
		SDL_RenderPresent(((t_ui_win*)(e->win))->rend);
	}
}

void        ui_free_radio_button_store(void *to_free)
{
	t_radio_button_store *store = to_free;

	SDL_DestroyTexture(store->text);
	free(to_free);
}

t_ui_elem   *ui_create_radio_button(t_ui_elem *parent, const char *choice_text,
                                  short choice_index)
{
	t_ui_elem               *new;
	t_radio_button_store    *store;
	t_radio_space_store     *parent_store = parent->store;
	t_ui_color              fg = {200, 200, 200, UI_ALPHA_OPAQUE};
	t_ui_color              bg = {70, 70, 70, UI_ALPHA_OPAQUE};

	(void)choice_text;
	new = ui_add_elem(
			parent,
			15, (int)(choice_index * 10 + 15), 70, 5,
			1,
			ui_display_radio_button,
			UI_TRUE,
			ui_free_radio_button_store);
	new->store = ui_secure_malloc(sizeof(t_radio_button_store));
	store = new->store;
	store->text = ui_text_to_texture(choice_text, 0, &fg, &bg, new);
	store->choice_index = choice_index;
	if (parent_store->current_choice == choice_index)
		store->checkbox_img = &(parent_store->checked_img);
	else
		store->checkbox_img = &(parent_store->unchecked_img);
	store->sensible_zone.x = 0;
	store->sensible_zone.y = 0;
	store->sensible_zone.w = 100;
	//TODO: Make the part that assigns the
	// sensible rect modular. Or just use a new elem to materialise the
	// button to press.
	store->sensible_zone.h = 100;
	ui_add_clickable_zones(
			new,
			&(store->sensible_zone),
			radio_button_click_func,
			1
			);
	return new;
}
