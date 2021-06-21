//
// Created by osc on 14/04/2021.
//
#include "ui.h"

void ui_resolve_win_content_actual_size(t_ui_win *win)
{
	win->content->actual_dimensions.x = 0;
	win->content->actual_dimensions.y = 0;
	win->content->actual_dimensions.w = win->width;
	win->content->actual_dimensions.h = win->height;
}

void	ui_set_x_and_y_from_ref(t_ui_elem *e)
{
	e->actual_dimensions.x = e->parent->actual_dimensions.x + ui_get_percentage_of_int(e->parent->actual_dimensions.w, e->relative_dimensions.x);
	e->actual_dimensions.y = e->parent->actual_dimensions.y + ui_get_percentage_of_int(e->parent->actual_dimensions.h, e->relative_dimensions.y);
}

void ui_resolve_as_percentages(t_ui_elem *e)
{
	e->actual_dimensions.w = ui_get_percentage_of_int(e->parent->actual_dimensions.w, e->relative_dimensions.w);
	e->actual_dimensions.h = ui_get_percentage_of_int(e->parent->actual_dimensions.h, e->relative_dimensions.h);;
}

void	ui_resolve_keep_actual_dimensions(t_ui_elem *e)
{
	(void)e;
}

void	ui_resolve_keep_fixed_dimensions(t_ui_elem *e)
{
	e->actual_dimensions.w = e->relative_dimensions.w;
	e->actual_dimensions.h = e->relative_dimensions.h;
}

void	ui_resolve_as_square_from_h(t_ui_elem *e)
{
	e->actual_dimensions.h = ui_get_percentage_of_int(e->parent->actual_dimensions.h, e->relative_dimensions.h);
	e->actual_dimensions.w = e->actual_dimensions.h;
}

void	ui_resolve_w_as_percentage_keep_actual_h(t_ui_elem *e)
{
	e->actual_dimensions.w = ui_get_percentage_of_int(e->parent->actual_dimensions.w, e->relative_dimensions.w);
}
