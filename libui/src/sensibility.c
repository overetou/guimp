//
// Created by osc on 29/04/2021.
//
#include "ui.h"

void	ui_resolve_clickable_zone_x_and_y(t_ui_elem *e)
{
	e->sensible_zones_actual_dimensions.x = e->actual_dimensions.x +
		ui_get_percentage_of_int(e->actual_dimensions.w,
		e->sensible_zones_relative_dimensions->x);
	//printf("Calculated sensible_zones_actual_dimensions.x = %d.\n", e->sensible_zones_actual_dimensions.x);
	e->sensible_zones_actual_dimensions.y = e->actual_dimensions.y +
		ui_get_percentage_of_int(e->actual_dimensions.h,
		e->sensible_zones_relative_dimensions->y);
	//printf("Calculated sensible_zones_actual_dimensions.y = %d.\n", e->sensible_zones_actual_dimensions.y);
}

void	ui_resolve_clickable_zone_w_as_percentage_keep_actual_h(t_ui_elem *e)
{
	e->sensible_zones_actual_dimensions.w = ui_get_percentage_of_int(
			e->actual_dimensions.w, e->sensible_zones_relative_dimensions->w);
}

void	ui_resolve_clickable_zone_as_square_from_h(t_ui_elem *e)
{
	e->sensible_zones_actual_dimensions.h = ui_get_percentage_of_int(
			e->actual_dimensions.h, e->sensible_zones_relative_dimensions->h);
	e->sensible_zones_actual_dimensions.w = e->sensible_zones_actual_dimensions.h;
}

void	ui_resolve_clickable_zone_as_percentage(t_ui_elem *e)
{
	e->sensible_zones_actual_dimensions.w = ui_get_percentage_of_int(e->actual_dimensions.w,
		e->sensible_zones_relative_dimensions->w);
	e->sensible_zones_actual_dimensions.h = ui_get_percentage_of_int(e->actual_dimensions.h,
		e->sensible_zones_relative_dimensions->h);
}

void	ui_resolve_clickable_zone_keep_actual_dimensions(t_ui_elem *e)
{
	(void)e;
}

void	ui_add_clickable_zones(t_ui_elem *e, SDL_Rect *relative_sensible_zones,
	void (*click_func)(t_ui_elem*, SDL_MouseButtonEvent*),
	short nb_sensible_zones,
	void (*sensible_zones_resolution_func)(t_ui_elem*))
{
	t_ui_elem   *p = e->parent;

	e->sensible_zones_relative_dimensions = relative_sensible_zones;
	e->sensible_zones_resolution_func = sensible_zones_resolution_func;
	ui_resolve_clickable_zone_x_and_y(e);
	sensible_zones_resolution_func(e);
	//printf("sensible_zones_actual_dimensions.w = %d, .h = %d.\n", e->sensible_zones_actual_dimensions.w, e->sensible_zones_actual_dimensions.h);
	//TODO: Malloc the appropriate number of sensible rects here, store them
	// in the elem and create a loop to assign them correctly.
	e->nb_sensible_zones = nb_sensible_zones;
	e->click_func = click_func;
	while (p && p->has_sub_clicks == UI_FALSE)
	{
		p->has_sub_clicks = UI_TRUE;
		p = p->parent;
	}
}
