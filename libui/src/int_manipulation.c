#include "ui.h"

//Undefined behavior if percentage > 100 || percentage < 0
int	ui_get_percentage_of_int(int reference, int percentage)
{
	return reference * percentage / 100;
}

//The last two arguments are meant to give a proportion: reference max / reference_subset. The functions returns that proportion applied to the actual_max.
int	ui_get_subset_proportionnal_to_proportion(int actual_max, int reference_max, int reference_subset)
{
	return actual_max * reference_subset / reference_max;
}

int	ui_calculate_start_of_center(int total_length, int length_to_center)
{
	return (total_length - length_to_center) / 2;
}

int	ui_get_proportion_in_percents(int bigger_val, int lesser_val)
{
	return bigger_val * 100 / lesser_val / 10;
}
