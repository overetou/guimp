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

void	ui_set_x_and_y_from_ref(SDL_Rect *reference_rect, SDL_Rect *relative_dimensions, SDL_Rect
*to_fill)
{
	to_fill->x = reference_rect->x + ui_get_percentage_of_int(reference_rect->w, relative_dimensions->x);
	to_fill->y = reference_rect->y + ui_get_percentage_of_int(reference_rect->h, relative_dimensions->y);
}

void ui_resolve_as_percentages(SDL_Rect *reference_rect, SDL_Rect *relative_dimensions, SDL_Rect
*to_fill)
{
	to_fill->w = ui_get_percentage_of_int(reference_rect->w, relative_dimensions->w);
	to_fill->h = ui_get_percentage_of_int(reference_rect->h, relative_dimensions->h);;
}

void	ui_resolve_keep_actual_dimensions(SDL_Rect *reference_rect, SDL_Rect *relative_dimensions, SDL_Rect
*to_fill)
{
	(void)reference_rect;
	(void)relative_dimensions;
	(void)to_fill;
}

void	ui_resolve_keep_fixed_dimensions(SDL_Rect *reference_rect, SDL_Rect *relative_dimensions, SDL_Rect *to_fill)
{
	(void)reference_rect;
	to_fill->w = relative_dimensions->w;
	to_fill->h = relative_dimensions->h;
}

void	ui_resolve_as_square_from_h(SDL_Rect *reference_rect, SDL_Rect *relative_dimensions, SDL_Rect
*to_fill)
{
	to_fill->h = ui_get_percentage_of_int(reference_rect->h, relative_dimensions->h);
	to_fill->w = to_fill->h;
}

void	ui_resolve_w_as_percentage_keep_actual_h(SDL_Rect *reference_rect, SDL_Rect *relative_dimensions, SDL_Rect
*to_fill)
{
	to_fill->w = ui_get_percentage_of_int(reference_rect->w, relative_dimensions->w);
}
