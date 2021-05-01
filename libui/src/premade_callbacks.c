//
// Created by osc on 29/04/2021.
//
#include "ui.h"

void ui_do_nothing(void *unused)
{
	(void)unused;
}

void ui_debug_say_clicked(t_ui_elem *e, SDL_MouseButtonEvent *ev)
{
	(void)ev;
	(void)e;
	puts("Clicked");
}

void ui_stop_event_handling(t_ui_elem *e, SDL_MouseButtonEvent *ev)
{
	(void)ev;
	UI_EL_UI(e)->keep_going = UI_FALSE;
}
