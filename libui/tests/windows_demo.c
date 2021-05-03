//
// Created by osc on 21/04/2021.
//
#include <ui.h>

int main(void)
{
	t_ui            *ui;
	t_ui_win        *win;

	ui = ui_init(UI_INIT_VIDEO, IMG_INIT_JPG | IMG_INIT_PNG);
	win = ui_add_window(ui, "Pak", 100, 100, 500, 500,
					 UI_WINDOW_RESIZABLE,
					 UI_RENDERER_ACCELERATED | UI_RENDERER_PRESENTVSYNC,
					 ui_colorblock_1);
	ui->fonts[0] = ui_load_font("blackchancery/BLKCHCRY.TTF", 15);

	ui_create_radio_button(win->content, 15, 10, 5, 5,
								 ui_debug_say_clicked);
	ui_create_radio_button(win->content, 15, 20, 5, 5,
								 ui_debug_say_clicked);
	//ui_create_radio_button(win->content, 15, 30, 5, 5,
	//							 ui_debug_say_clicked);
	refresh_win(win);
	ui_handle_events(ui);

	ui_close_font(ui->fonts[0]);
	ui_close(ui);
	puts("Finished.");
	return 0;
}

/*
 * Petite fourberie: Si le code est plus simple que pour celui du boutton
 * précédent, il y en a plusieurs ici. Il faudra donc que l'ordre d'affichage
 * soit bien géré (et qu'il ai lieu.).
*/
