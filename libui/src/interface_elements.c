//
// Created by osc on 14/04/2021.
//
#include "ui.h"

t_ui_elem *ui_create_button(t_ui_elem *parent, t_percentage x, t_percentage y, t_percentage w,
            t_percentage h, char disp_priority, t_ui_bool sensible)
{
	t_ui_elem *new;

	new = ui_add_elem(parent, x, y, w, h, 1, ui_colorblock_2, sensible);
	ui_add_clickable_zones(, )
}
