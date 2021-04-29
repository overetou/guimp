//
// Created by osc on 29/04/2021.
//
#include "ui.h"

void ui_stop_event_handling_from_elem(t_ui_elem *e)
{
	UI_EL_UI(e)->keep_going = UI_FALSE;
}
