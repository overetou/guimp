//
// Created by osc on 14/04/2021.
//
#include "ui.h"

void ui_win_percent_rect_to_sdl_rect(t_ui_win *win, t_percent_rect *percent_rect,
                                     SDL_Rect *sdl_rect)
{
	sdl_rect->x = 0;
	sdl_rect->y = 0;
	sdl_rect->w = win->width * percent_rect->w / 100;
	sdl_rect->h = win->height * percent_rect->h / 100;
}

void ui_infer_elem_actual_size(t_ui_elem *e)
{
	e->actual_sizes.x = e->parent->actual_sizes.x * e->proportions.x / 100;
	e->actual_sizes.y = e->parent->actual_sizes.y * e->proportions.y / 100;
	e->actual_sizes.w = e->parent->actual_sizes.w * e->proportions.w / 100;
	e->actual_sizes.h = e->parent->actual_sizes.h * e->proportions.h / 100;
}
