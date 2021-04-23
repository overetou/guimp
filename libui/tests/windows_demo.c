//
// Created by osc on 21/04/2021.
//
#include <ui.h>

int main(void)
{
	t_ui    *ui;

	ui = ui_init(UI_INIT_VIDEO, IMG_INIT_JPG | IMG_INIT_PNG);
	ui_add_window(ui, "Pak", 100, 100, 1300, 800, UI_WINDOW_RESIZABLE, UI_RENDERER_ACCELERATED | UI_RENDERER_PRESENTVSYNC);
	ui_close(ui);
	return 0;
}
