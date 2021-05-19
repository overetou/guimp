#include "ui.h"

void		ui_free_wincontent_store(void *to_free)
{
	t_ui_wincontent_store *store = to_free;

	SDL_DestroyTexture(store->success);
	SDL_DestroyTexture(store->error);
	free(to_free);
}

void		ui_free_checkbox_store(void *to_free)
{
	t_checkbox_button_store *store = to_free;

	SDL_DestroyTexture(store->text);
	free(to_free);
}

void		ui_display_checkbox_button(t_ui_elem *e)
{
	t_checkbox_button_store *store = e->store;
	SDL_Rect dest = {e->actual_dimensions.x, e->actual_dimensions.y, e->actual_dimensions.h,
	e->actual_dimensions.h};

	SDL_RenderCopy(UI_EL_REND(e), store->checkbox, NULL, &dest);
	ui_display_img(e, store->text, 33, 20);
}

void		ui_checkbox_clicked(t_ui_elem *e, SDL_MouseButtonEvent *ev)
{
	t_checkbox_button_store	*store = e->store;

	(void)ev;
	if (store->checkbox == ((t_ui_wincontent_store*)(((t_ui_win*)(e->win))->content->store))->success)
		store->checkbox = ((t_ui_wincontent_store*)(((t_ui_win*)(e->win))->content->store))->error;
	else
		store->checkbox = ((t_ui_wincontent_store*)(((t_ui_win*)(e->win))->content->store))->success;
	ui_display_elem(((t_ui_win*)(e->win))->content);
	SDL_RenderPresent(((t_ui_win*)(e->win))->rend);
}

t_ui_elem	*ui_create_checkbox_button(t_ui_elem *parent, const char *text, int x, int y)
{
	t_ui_elem				*new;
	t_checkbox_button_store	*store;
	t_ui_color				fg = {200, 200, 200, UI_ALPHA_OPAQUE};
	t_ui_color				bg = {70, 70, 70, UI_ALPHA_OPAQUE};

	new = ui_add_elem(parent, x, y, 0, 0, 1, ui_display_checkbox_button,
	UI_TRUE, ui_free_checkbox_store, ui_resolve_keep_actual_dimensions);
	new->store = malloc(sizeof(t_checkbox_button_store));
	store = new->store;
	store->checkbox = ((t_ui_wincontent_store*)(((t_ui_win*)(new->win))->content->store))->error;
	new->actual_dimensions.h = 30;
	store->text = ui_text_to_texture(text, 0, &fg, &bg, new);
	SDL_QueryTexture(store->text, NULL, NULL, &(new->actual_dimensions.w), NULL);
	new->actual_dimensions.w += 30 + 3;
	store->sensible_zone.x = 0;
	store->sensible_zone.y = 0;
	new->sensible_zones_actual_dimensions.w = 30;
	new->sensible_zones_actual_dimensions.h = 30;
	ui_add_clickable_zones(new, &(store->sensible_zone), ui_checkbox_clicked, 1,
		ui_resolve_keep_actual_dimensions);
	return new;
}
