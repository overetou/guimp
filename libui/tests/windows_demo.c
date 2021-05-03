//
// Created by osc on 21/04/2021.
//
#include <ui.h>

int main(void)
{
	t_ui            *ui;
	t_ui_win        *win;
	t_ui_elem       *button;

	ui = ui_init(UI_INIT_VIDEO, IMG_INIT_JPG | IMG_INIT_PNG);
	win = ui_add_window(ui, "Pak", 100, 100, 500, 500,
					 UI_WINDOW_RESIZABLE,
					 UI_RENDERER_ACCELERATED | UI_RENDERER_PRESENTVSYNC,
					 ui_colorblock_1);
	ui->fonts[0] = ui_load_font("blackchancery/BLKCHCRY.TTF", 15);

	button = ui_create_button(win->content, 25, 25, 50, 50, "Salut",
						  ui_debug_say_clicked);

	refresh_win(win);
	ui_handle_events(ui);

	ui_close_font(ui->fonts[0]);
	ui_close(ui);
	puts("Finished.");
	return 0;
}

/*
 * Scan de la logique: tout se concentre dans ui_create_button.
 *
*/
