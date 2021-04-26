//
// Created by osc on 21/04/2021.
//
#include <ui.h>

int main(void)
{
	t_ui    *ui;
	t_ui_win *win;
	t_ui_elem *button;

	ui = ui_init(UI_INIT_VIDEO, IMG_INIT_JPG | IMG_INIT_PNG);
	//win = ui_add_window(ui, "Pak", 100, 100, 1300, 800, UI_WINDOW_RESIZABLE, UI_RENDERER_ACCELERATED | UI_RENDERER_PRESENTVSYNC, ui_colorblock_1);
	//button = ui_add_elem(win->content, 25, 25, 50, 50, 1, ui_colorblock_2, UI_TRUE, NULL, NULL);
	SDL_Delay(5000);
	ui_close(ui);
	puts("Finished.");
	return 0;
}

/*
étape 1: tester l'initialisation de la librairie.
*/