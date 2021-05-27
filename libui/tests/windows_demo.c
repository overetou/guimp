//
// Created by osc on 21/04/2021.
//
#include <ui.h>

void	catch_mouse_held_down_demo(void)
{
	int			go = 1;
	SDL_Event	ev;

	while (go)
	{
		SDL_WaitEvent(&ev);
		switch (ev.type)
		{
		case SDL_QUIT:
			go = 0;
			break;
		case SDL_MOUSEBUTTONDOWN:
		printf("down on %d, %d.\n",
		((SDL_MouseButtonEvent*)(&ev))->x, ((SDL_MouseButtonEvent*)(&ev))->y);
		break;
		case SDL_MOUSEBUTTONUP:
		printf("Mouse up on %d, %d.\n", 
		((SDL_MouseButtonEvent*)(&ev))->x, ((SDL_MouseButtonEvent*)(&ev))->y);
		break;
		}
	}
	
}

int main(void)
{
	t_ui					*ui;
	t_ui_win				*win;
	t_ui_wincontent_store 	*wincontent_store;

	ui = ui_init(UI_INIT_VIDEO, IMG_INIT_JPG | IMG_INIT_PNG);
	win = ui_add_window(ui, "Pak", 100, 100, 1000, 1000,
					 UI_WINDOW_RESIZABLE,
					 UI_RENDERER_ACCELERATED | UI_RENDERER_PRESENTVSYNC,
					 ui_colorblock_1);

	ui->fonts[0] = ui_load_font("blackchancery/BLKCHCRY.TTF", 15);//TODO: pass the font tank inside the wincontent_store?
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

	t_ui_elem *slider = ui_create_slider(win->content, 10, 10, 50, 50, 100);
	ui_create_slider(win->content, 10, 15, 50, 50, 100);

	refresh_win(win);
	ui_handle_events(ui);

	printf("Slider value = %d.\n", ((t_slider_store*)(slider->store))->current_val);

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
