//
// Created by osc on 26/04/2021.
//
#include "ui.h"

void ui_colorblock_1(t_ui_elem *e)
{
	ui_colorize_elem(e, 70, 70, 70, UI_ALPHA_OPAQUE);
}

void ui_colorblock_2(t_ui_elem *e)
{
	SDL_Color   fg = {120, 120, 120, UI_ALPHA_OPAQUE};
	SDL_Color   bg = {50, 50, 50, UI_ALPHA_OPAQUE};

	ui_colorize_elem(e, UI_EXPAND_COLOR(bg));
	ui_display_centered_text_line(e, "Dark Souls", &fg, &bg);
}
