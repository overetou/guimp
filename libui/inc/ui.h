//
// Created by osc on 13/04/2021.
//
#ifndef UI
#define UI

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

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

#define UI_RENDERER_SOFTWARE        SDL_RENDERER_SOFTWARE
#define UI_RENDERER_ACCELERATED     SDL_RENDERER_ACCELERATED
#define UI_RENDERER_PRESENTVSYNC    SDL_RENDERER_PRESENTVSYNC
#define UI_RENDERER_TARGETTEXTURE   SDL_RENDERER_TARGETTEXTURE

#define UI_WINDOW_FULLSCREEN            SDL_WINDOW_FULLSCREEN
#define UI_WINDOW_FULLSCREEN_DESKTOP    SDL_WINDOW_FULLSCREEN_DESKTOP
#define UI_WINDOW_OPENGL                SDL_WINDOW_OPENGL
#define UI_WINDOW_VULKAN                SDL_WINDOW_VULKAN
#define UI_WINDOW_METAL                 SDL_WINDOW_METAL
#define UI_WINDOW_HIDDEN                SDL_WINDOW_HIDDEN
#define UI_WINDOW_SHOWN                 SDL_WINDOW_SHOWN
#define UI_WINDOW_BORDERLESS            SDL_WINDOW_BORDERLESS
#define UI_WINDOW_RESIZABLE             SDL_WINDOW_RESIZABLE
#define UI_WINDOW_MINIMIZED             SDL_WINDOW_MINIMIZED
#define UI_WINDOW_MAXIMIZED             SDL_WINDOW_MAXIMIZED
#define UI_WINDOW_INPUT_GRABBED         SDL_WINDOW_INPUT_GRABBED
#define UI_WINDOW_ALLOW_HIGHDPI         SDL_WINDOW_ALLOW_HIGHDPI

#define UI_ALPHA_OPAQUE         SDL_ALPHA_OPAQUE
#define UI_ALPHA_TRANSPARENT    SDL_ALPHA_TRANSPARENT

#define UI_EL_RENDERER(e) ((t_ui_win*)(e->win))->rend
#define UI_EXPAND_COLOR(x) x.r, x.g, x.b, x.a
#define UI_EXPAND_COLOR_PTR(x) x->r, x->g, x->b, x->a

//An image usable by the ui framework.
typedef int t_ui_bool;
typedef SDL_Texture t_ui_img;
typedef SDL_Color t_ui_color;

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

//A structure that will only be used as a mean to make some
// generic code.
typedef struct	s_link
{
	struct s_link   *next;
	struct s_link   *prev;
}				t_link;

typedef struct	s_ui_elem
{
	//Other elements in the same containing element. NULL if none.
	struct s_ui_elem *next;
	struct s_ui_elem *prev;
	//Display info
	t_percent_rect  proportions;
	SDL_Rect        actual_sizes;
	char            display_priority;
	void            (*display_func)(struct s_ui_elem*);
	void             *store;//Member at the disposition of the user.
	//Sensibility
	UI_BOOL         sensible;
	t_percent_rect  *sensible_zones;//tab
	short           nb_sensible_zones;
	//Hover
	UI_BOOL         has_sub_hovers;
	void            (*hover_func)(void*);
	//Clicks
	UI_BOOL         has_sub_clicks;
	void            (*click_func)(void*);
	//sub_elems
	struct s_ui_elem *sub_elems;
	//win ref
	void            *win;
	//parent
	struct s_ui_elem *parent;
}				t_ui_elem;

typedef struct	s_ui_win
{
	struct s_ui_win *next;
	struct s_ui_win *prev;
	SDL_Window      *sdl_ptr;
	SDL_Renderer    *rend;
	int             width;
	int             height;
	t_ui_elem       *content;
}				t_ui_win;

typedef struct  s_ui
{
	t_ui_win    *wins; //A linked list.
	t_ui_elem   *focused;
}               t_ui;

//basic stuff
void    mem_copy(char *dest, const char *src, int len);
void    add_link_to_list(t_link **list, t_link *new_link);
void    remove_link_from_list(t_link **list, t_link *to_remove);
void    free_list(t_link *list, void(*free_func)(void*));
void    init_list(t_link **list, t_link *new_link);
void    list_add_link_on_top_of_initiated(t_link **list, t_link *new_link);

//security
void    ui_sdl_critical_check(int val);
void	ui_critical_check(UI_BOOL val, const char *msg);
void    *ui_secure_malloc(size_t  len);

//calculus
void    ui_calculate_win_content_actual_size(t_ui_win *win);
void    ui_infer_elem_actual_size(t_ui_elem *e);

//core functions
t_ui    *ui_init(uint32_t ui_flags, int img_flags);
void    ui_close(t_ui *to_destroy);
void        refresh_win(t_ui_win *win);

//windows
t_ui_win *ui_add_window(t_ui *ui, const char *title, int x, int y, int w, int h,
                        uint32_t flags, uint32_t render_flags,
                        void (*display_func)(t_ui_elem *));
void ui_update_window_size(t_ui_win *win);

//elems
t_ui_img    *ui_load_img(t_ui_win *win, const char *img_path);
t_ui_elem *ui_create_virgin_elem(t_percentage x, t_percentage y, t_percentage w,
                                 t_percentage h, t_ui_win *win,
                                 char display_priority,
                                 void (*display_func)(t_ui_elem *));
void        ui_remove_elem(t_ui_elem *e);
void        ui_transfer_elem(t_ui_elem *new_parent, t_ui_elem *e,
							 char new_disp_priority);
t_ui_elem   *ui_add_elem(t_ui_elem *parent, t_percentage x, t_percentage y,
                       t_percentage w, t_percentage h,
                       char disp_priority, void(*display_func)(t_ui_elem*),
                       UI_BOOL sensible, void(*hover_func)(void*),
                       void(*click_func)(void*));
void        ui_display_elem(t_ui_elem *e);
void        display_elem(t_ui_elem *e);
void        ui_paint_elem(t_ui_elem *e, int r, int g, int b, int a);
//blocking
void    ui_colorblock_1(t_ui_elem *e);
void    ui_colorblock_2(t_ui_elem *e);

//display
void        ui_colorize_elem(t_ui_elem *e, int r, int g, int b, int a);
TTF_Font    *ui_load_font(const char *path, int size);
void        ui_close_font(TTF_Font *font);
void        ui_display_centered_text_line(t_ui_elem *e, const char *text_line,
									  t_ui_color *foreground,
									  t_ui_color *background);
//Interface elements

#endif //UI
