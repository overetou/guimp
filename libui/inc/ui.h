//
// Created by osc on 13/04/2021.
//
#ifndef UI
#define UI

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

//A discrete value between 0 and 100
typedef char t_percentage;

//The values inside this struct are percentages between 0 and 100
typedef struct	s_percent_rect
{
	t_percentage x;
	t_percentage y;
	t_percentage w;
	t_percentage h;
}				t_percent_rect;

typedef struct  s_ui_master
{
	int             win_width;
	int             win_height;
	SDL_Window 		*win;
	SDL_Renderer    *renderer;
}               t_ui_master;

extern t_ui_master ui_m;

//core functions
void	ui_init(SDL_Window *win, SDL_Renderer *renderer);
void	ui_update_window_size();
void	ui_quit(void);
void 	ui_refresh(void);
void 	ui_colorize_window(SDL_Color *color);
//Interface elements
void 	ui_create_button(t_percent_rect *button_space, void(*callback)(SDL_Event *e));

#endif //UI
