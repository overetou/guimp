//
// Created by osc on 29/04/2021.
//
#include "ui.h"

void ui_add_clickable_zones(t_ui_elem *e, t_percent_rect *zones,
                            void (*click_func)(t_ui_elem*,
                                               SDL_MouseButtonEvent*),
                            short nb_sensible_zones)
{
	t_ui_elem   *p = e->parent;

	e->sensible_zones_relative_dimensions = zones;
	printf("Proportions of sensible zone: %d, %d, %d, %d.\n", zones->x, zones
	->y, zones->w, zones->h);
	ui_infer_actual_size(&(e->actual_dimensions), zones, &(e->sensible_zones_actual_dimensions));
	printf("Clickable zone: %d, %d, %d, %d\n", e->sensible_zones_actual_dimensions.x,
	       e->sensible_zones_actual_dimensions.y, e->sensible_zones_actual_dimensions.w, e->sensible_zones_actual_dimensions.h);
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
