//
// Created by osc on 29/04/2021.
//
#include "ui.h"

void ui_add_clickable_zones(t_ui_elem *e, t_percent_rect *zones,
                            void(*click_func)(t_ui_elem*))
{
	t_ui_elem   *p = e->parent;

	e->sensible_zones = zones;
	e->click_func = click_func;
	while (p && p->has_sub_clicks == UI_FALSE)
	{
		p->has_sub_clicks = UI_TRUE;
		p = p->parent;
	}
}
