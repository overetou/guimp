//
// Created by osc on 21/04/2021.
//
#include <ui.h>

int main(void)
{
	t_ui    *ui;

	ui = ui_init(UI_WINDOW_RESIZABLE, IMG_INIT_JPG | IMG_INIT_PNG);
	ui_close(ui);
	return 0;
}
