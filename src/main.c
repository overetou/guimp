#include "guimp.h"

void play_around(SDL_Window *p_window, SDL_Renderer *p_renderer);

int	main(void)
{
	SDL_Window		*win;
	SDL_Renderer	*renderer;

	SDL_Init(SDL_INIT_VIDEO);
	IMG_Init(IMG_INIT_PNG);
	win = SDL_CreateWindow("Demo",
	                       SDL_WINDOWPOS_UNDEFINED,
	                       SDL_WINDOWPOS_UNDEFINED,
	                       500,
	                       500,
	                       SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
	play_around(win, renderer);
	ui_quit();
	IMG_Quit();
	SDL_Quit();
	return 0;
}

void play_around(SDL_Window *p_window, SDL_Renderer *p_renderer)
{
	ui_init(p_window, p_renderer);
	SDL_Color back_color = {100, 50, 30, SDL_ALPHA_OPAQUE};
	ui_colorize_window(&back_color);
	ui_refresh();
	sleep(3);
	ui_refresh();
}
