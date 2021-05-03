//
// Created by osc on 26/04/2021.
//
#include "ui.h"

void ui_colorblock_1(t_ui_elem *e)
{
	ui_colorize_elem(e, 70, 70, 70, UI_ALPHA_OPAQUE);
}

void ui_display_button(t_ui_elem *e)
{
	SDL_Color   bg = {50, 50, 50, UI_ALPHA_OPAQUE};

	ui_colorize_elem(e, UI_EXPAND_COLOR(bg));
	ui_display_img_at_center_of_elem(
			e,
			((t_ui_button_store*)(e->store))->text_img);
}
