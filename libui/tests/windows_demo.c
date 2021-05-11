//
// Created by osc on 21/04/2021.
//
#include <ui.h>

int main(void)
{
	t_ui            *ui;
	t_ui_win        *win;
	t_ui_elem       *radio_space;

	ui = ui_init(UI_INIT_VIDEO, IMG_INIT_JPG | IMG_INIT_PNG);
	win = ui_add_window(ui, "Pak", 100, 100, 1000, 1000,
					 UI_WINDOW_RESIZABLE,
					 UI_RENDERER_ACCELERATED | UI_RENDERER_PRESENTVSYNC,
					 ui_colorblock_1);
	ui->fonts[0] = ui_load_font("blackchancery/BLKCHCRY.TTF", 15);

	radio_space = ui_create_radio_button_container(win->content, 0, 0, 50, 100);
	ui_create_radio_button(radio_space, "Vim", 0);
	ui_create_radio_button(radio_space, "Emacs", 1);
	ui_create_radio_button(radio_space, "VSCode", 2);
	ui_create_radio_button(radio_space, "CLion", 3);

	refresh_win(win);
	ui_handle_events(ui);

	t_radio_space_store *store = radio_space->store;
	const char *editor_tab[] = {"Vim", "Emacs", "VSCode", "CLion"};
	printf("Your editor is %s.\n", editor_tab[store->current_choice]);

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
