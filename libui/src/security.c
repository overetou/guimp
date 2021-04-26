//
// Created by osc on 14/04/2021.
//
#include "ui.h"

void    ui_sdl_critical_check(int val)
{
	if (val)
		return;
	printf("Critical SDL operation failure: %s\n", SDL_GetError());
	exit(0);
}

//If the given value == UI_FALSE, print the given message, a report of the sys
//-tem and exit the application.
void	ui_critical_check(UI_BOOL val, const char *msg)
{
	if (val)
		return;
	perror(msg);
	exit(0);
}

void *ui_secure_malloc(size_t  len)
{
	void *tmp = malloc(len);

	ui_critical_check(tmp != NULL, "Memory allocation failed.");
	return tmp;
}
