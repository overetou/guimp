//
// Created by osc on 13/04/2021.
//
#ifndef UI
#define UI

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define UI_BOOL int
#define UI_TRUE 1
#define UI_FALSE 0

#define UI_INIT_VIDEO           SDL_INIT_VIDEO
#define UI_INIT_TIMER           SDL_INIT_TIMER
#define UI_INIT_AUDIO           SDL_INIT_AUDIO
#define UI_INIT_VIDEO           SDL_INIT_VIDEO
#define UI_INIT_JOYSTICK        SDL_INIT_JOYSTICK
#define UI_INIT_HAPTIC          SDL_INIT_HAPTIC
#define UI_INIT_GAMECONTROLLER  SDL_INIT_GAMECONTROLLER
#define UI_INIT_EVENTS          SDL_INIT_EVENTS
#define UI_INIT_EVERYTHING      SDL_INIT_EVERYTHING
#define UI_INIT_NOPARACHUT      SDL_INIT_NOPARACHUTE

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

typedef struct  s_ui
{
	int             win_width;
	int             win_height;
	SDL_Window 		*win;
	SDL_Renderer    *renderer;
}               t_ui;

//security
void	ui_critical_check(UI_BOOL val, const char *msg);
void    *ui_secure_malloc(size_t  len);

//calculus
void win_percent_rect_to_sdl_rect(t_ui *ui, t_percent_rect *p_rect,
                                  SDL_Rect *sdl_rect);

//core functions
t_ui    *ui_init(uint32_t ui_flags, int img_flags);
void    ui_close(t_ui *to_destroy);
void 	ui_refresh(t_ui *ui);
void 	ui_colorize_window(t_ui *ui, SDL_Color *color);

//windows
void    ui_create_window(t_ui *ui, const char *title, int x, int y, int w,
						 int h, uint32_t flags, uint32_t render_flags);
void	ui_update_window_size(t_ui *ui, SDL_Window *win);

//Interface elements
void 	ui_create_button(t_ui *ui, t_percent_rect *button_space, void(*callback)
		(SDL_Event *e));

#endif //UI
