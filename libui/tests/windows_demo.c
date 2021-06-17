#include <ui.h>

int main(void)
{
	t_ui					*ui;
	t_ui_win				*win;
	t_ui_wincontent_store 	*wincontent_store;
	
	ui = ui_init(UI_INIT_VIDEO, IMG_INIT_JPG | IMG_INIT_PNG);
	win = ui_add_window(ui, "Pak", 800, 200, 1000, 1000,
					 UI_WINDOW_RESIZABLE,
					 UI_RENDERER_ACCELERATED | UI_RENDERER_PRESENTVSYNC,
					 ui_colorblock_1);
	ui->fonts[0] = ui_load_font("open-sans/OpenSans-Semibold.ttf", 13);//TODO: pass the font tank inside the wincontent_store?
	win->content->store = malloc(sizeof(t_ui_wincontent_store));
	win->content->free_store_func = ui_free_wincontent_store;
	wincontent_store = win->content->store;
	wincontent_store->success = ui_load_img(win, "assets/checked.png");
	wincontent_store->error = ui_load_img(win, "assets/unchecked.png");
	if (wincontent_store->success == NULL || wincontent_store->error == NULL)
	{
		puts("Loading the image failed.");
		exit(0);
	}
	
	char	*text = ui_secure_malloc(3);
	mem_copy(text, "yo\0", 3);
	ui_create_text_line_input(win->content, text, 10, 10, 200, 25);
	ui_create_slider(win->content, 10, 20, 40, 50, 100);
	//ui_create_button(win->content, 10, 10, 50, 50, "42_puts", ui_debug_say_clicked);

	refresh_win(win);
	ui_handle_events(ui);
	
	ui_close_font(ui->fonts[0]);
	ui_close(ui);
	puts("Finished.");
	return 0;
}
