//
// Created by osc on 14/04/2021.
//
#include "ui.h"

void ui_calculate_win_content_actual_size(t_ui_win *win)
{
	win->content->actual_dimensions.x = 0;
	win->content->actual_dimensions.y = 0;
	win->content->actual_dimensions.w = win->width;
	win->content->actual_dimensions.h = win->height;
}

void ui_infer_actual_size(SDL_Rect *reference_rect, t_percent_rect *proportions, SDL_Rect
*to_fill)
{
	to_fill->x = reference_rect->x + reference_rect->w
	                                 * proportions->x / 100;
	to_fill->y = reference_rect->y + reference_rect->h
	                                 * proportions->y / 100;
	to_fill->w = reference_rect->w * proportions->w / 100;
	to_fill->h = reference_rect->h * proportions->h / 100;
}

void ui_infer_elem_actual_size(t_ui_elem *e)
{
	ui_infer_actual_size(&(e->parent->actual_dimensions), &(e->relative_dimensions), &(e->actual_dimensions));
}
