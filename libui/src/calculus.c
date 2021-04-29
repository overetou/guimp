//
// Created by osc on 14/04/2021.
//
#include "ui.h"

void ui_calculate_win_content_actual_size(t_ui_win *win)
{
	win->content->actual_sizes.x = 0;
	win->content->actual_sizes.y = 0;
	win->content->actual_sizes.w = win->width;
	win->content->actual_sizes.h = win->height;
}

void ui_infer_actual_size(t_ui_elem *e, SDL_Rect *proportions, SDL_Rect *target)
{
	target->x = e->parent->actual_sizes.x + e->parent->actual_sizes.w
			* e->proportions.x / 100;
	target->y = e->parent->actual_sizes.y + e->parent->actual_sizes.h
			* e->proportions.y / 100;
	target->w = e->parent->actual_sizes.w * e->proportions.w / 100;
	target->h = e->parent->actual_sizes.h * e->proportions.h / 100;
}

void ui_infer_elem_actual_size(t_ui_elem *e)
{
	e->actual_sizes.x = e->parent->actual_sizes.x + e->parent->actual_sizes.w
			* e->proportions.x / 100;
	e->actual_sizes.y = e->parent->actual_sizes.y + e->parent->actual_sizes.h
			* e->proportions.y / 100;
	e->actual_sizes.w = e->parent->actual_sizes.w * e->proportions.w / 100;
	e->actual_sizes.h = e->parent->actual_sizes.h * e->proportions.h / 100;
}
