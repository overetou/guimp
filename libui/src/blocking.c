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
	SDL_Surface *text;

	ui_colorize_elem(e, 50, 50, 50, UI_ALPHA_OPAQUE);
	text = TTF_RenderUNICODE_Shaded(e->store, "Dark Souls", fg, bg);
	ui_sdl_critical_check(text != NULL);

}
