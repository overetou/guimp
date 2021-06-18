#include "ui.h"

void	ui_display_img_display(t_ui_elem *e)
{
	ui_display_img_with_absolute_dimensions(e, e->store, e->actual_dimensions.w,
			e->actual_dimensions.h);
}

t_ui_elem	*ui_create_img_display(t_ui_elem *parent, int x, int y, int w, int h,
		const char *img_path)
{
	t_ui_elem	*new;

	new = ui_add_elem(parent, x, y, w, h, 1, ui_display_img_display, UI_FALSE,
			(void (*)(void *))SDL_DestroyTexture, ui_resolve_keep_fixed_dimensions);
	new->store = ui_load_img(new->win, img_path);
	return new;
}
