#include "ui.h"

//Undefined behavior if percentage > 100 || percentage < 0
int	ui_get_percentage_of_int(int reference, int percentage)
{
	return reference * percentage / 100;
}

int	ui_get_