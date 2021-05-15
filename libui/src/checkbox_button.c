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

	SDL_RenderCopy(UI_EL_REND(e), *(store->checkbox), NULL, &dest);
	ui_display_img(e, store->text, 20, 15);
}

t_ui_elem	*ui_create_checkbox_button(t_ui_elem *parent, const char *text)
{
	t_ui_elem				*new;
	t_checkbox_button_store	*store;
	t_ui_color				fg = {200, 200, 200, UI_ALPHA_OPAQUE};
	t_ui_color				bg = {70, 70, 70, UI_ALPHA_OPAQUE};

	new = ui_add_elem(parent, 0, 0, 0, 0, 1, ui_display_checkbox_button,
	UI_TRUE, ui_free_checkbox_store, ui_resolve_keep_actual_dimensions);
	store = new->store;
	store->checkbox = ((t_ui_wincontent_store*)(((t_ui_win*)(new->win))->content->store))->error;
	new->actual_dimensions.w = ;
}