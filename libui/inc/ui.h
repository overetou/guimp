//
// Created by osc on 13/04/2021.
//
#ifndef UI
#define UI

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#define FONT_NB 1

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

#define UI_EL_WIN(e) ((t_ui_win*)(e->win))
#define UI_EL_REND(e) UI_EL_WIN(e)->rend
#define UI_EL_UI(e) ((t_ui*)(UI_EL_WIN(e)->ui))
#define UI_EXPAND_COLOR(x) x.r, x.g, x.b, x.a
#define UI_EXPAND_COLOR_PTR(x) x->r, x->g, x->b, x->a

typedef int t_ui_bool;//Can be set to UI_TRUE or UI_FALSE.
typedef SDL_Texture t_ui_img;//An image that can be used by the ui.
typedef SDL_Color t_ui_color;/*A color. r = red, g = green, b = blue, a =
 * alpha (the transparency level. Higher means less transparent.). All of
 * these values are meant to go from 0 to 255. Example: opaque red: r = 255,
 * b = 0, b = 0, a = 255.*/

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

/*A structure that will only be used as a mean to make some
generic code.*/
typedef struct	s_link
{
	struct s_link   *next;
	struct s_link   *prev;
}				t_link;

typedef struct	s_ui_elem
{
	/*Other elements in the same containing element. NULL if none. Don't
	change the order of these two or put something before them.*/
	struct s_ui_elem    *next;
	struct s_ui_elem    *prev;
	//Display info
	SDL_Rect            relative_dimensions;/*Size of the element in percentages
	relative to its parent actual size.*/
	void                (*elem_dimensions_resolution_func)(SDL_Rect *reference,
							SDL_Rect *values, SDL_Rect *to_fill);
	SDL_Rect            actual_dimensions;/*The actual estate of the elem on the
 * screen, in pixels.*/
	char                display_priority;/*0 for invisible elem. Must be
	positive otherwise. Smaller will be displayed on top of bigger
	display_priority.*/
	void                (*display_func)(struct s_ui_elem*);/*A pointer to the
	function that will be called when the ui prompts the elem to display
	itself. See such callback examples in src/blocking.c.
	storing*/
	void                *store;/*Pointer the disposition of the user. Use it
	however you like!*/
	void                (*free_store_func)(void*);/*This func will be called
 * at the destruction of the element. It is meant to destroy the content of
 * the 'store' member of the elem ('store' will be passed as argument). If you
 * stored nothing, pass ui_do_nothing to it. Not NULL because the function
 * will be called without checking anything.*/
	//Sensibility
	t_ui_bool           sensible;/*If set to false, none of the user events
 * will be transmitted to or through this element.*/
	t_percent_rect      *sensible_zones_relative_dimensions;/*A table of percent rects that
	represent the sensible zones of the elem.*/
	void                (*sensible_zones_resolution_func)(SDL_Rect *reference,
							SDL_Rect *values, SDL_Rect *to_fill);
	SDL_Rect            sensible_zones_actual_dimensions;/*Sensible zones resolved by the ui into
	actual pixel values. You are not expected to modify this value
	but you may access it anytime.*/
	short               nb_sensible_zones;//Number of sensible zones.
	//Hover
	t_ui_bool           has_sub_hovers;/*True if somewhere in the
 * sub-hierarchie of this element, one has hover_func set to a callback.*/
	void                (*hover_func)(struct s_ui_elem*);/*Called when one
 * of the element's sensible zones is hovered.*/
	//Clicks
	t_ui_bool           has_sub_clicks;/*Same as before but applied to clicks
 * . Note that it concerns right click, left click and the middle button upon
 * their button-down event.TODO: transmit button-up events as well.*/
	void                (*click_func)(struct s_ui_elem*,
			SDL_MouseButtonEvent*);/*Called when any sensible zone of the
 * elem is clicked.*/
	//sub_elems
	struct s_ui_elem    *sub_elems;/*Elements contained inside this one.*/
	//parent
	struct s_ui_elem    *parent;/*The element that contains this one.*/
	//win ref
	void                *win;/*The window that contains this element.*/
}				t_ui_elem;

typedef struct	s_ui_win
{
	/*Let those as the 2 first members, in the same order, or problems there
	will be!*/
	struct s_ui_win *next;//The next window in line.
	struct s_ui_win *prev;/*Previous window.
	other content.*/
	void            *ui;/*Points back to its owning ui. Use this to modify
	keep_going or access your fonts. Note that elems have a win pointer.*/
	SDL_Window      *sdl_ptr;
	SDL_Renderer    *rend;
	int             width;//Not percentages but the real value in pixels.
	int             height;
	t_ui_elem       *content;/*The root elem of the window. Should be used to
	set the background color/ image.*/
}				t_ui_win;

typedef struct  s_ui
{
	t_ui_win    *wins; //This list stores all the windows you added to the ui.
	t_ui_elem   *focused;//TODO: Keep track of the currently focused element.
	t_ui_bool   keep_going;/*Goes to true when ui_handle_events is called.
	Set it to false to make the loop stop.*/
	TTF_Font    *fonts[FONT_NB];//A tab to store your font pointers.
}               t_ui;

typedef struct  s_ui_button_store
{
	t_ui_img        *text_img;
	t_percent_rect  sensible_zone;
}               t_ui_button_store;

typedef struct  s_radio_space_store
{
	t_ui_img    *unchecked_img;
	t_ui_img    *checked_img;
	short       current_choice;
}               t_radio_space_store;

typedef struct      s_radio_button_store
{
	t_percent_rect  sensible_zone;
	short           choice_index;
	t_ui_img        **checkbox_img;
	t_ui_img        *text;
}                   t_radio_button_store;

//basic stuff
void    mem_copy(char *dest, const char *src, int len);
void    add_link_to_list(t_link **list, t_link *new_link);
void    remove_link_from_list(t_link **list, t_link *to_remove);
void    free_list(t_link *list, void(*free_func)(void*));
void    init_list(t_link **list, t_link *new_link);
void    list_add_link_at_start(t_link **list, t_link *new_link);
void    list_add_link_at_end(t_link *last_link, t_link *new_link);
void    list_add_link_in_the_middle(t_link *next_link_to_be, t_link *new_link);

//security
void    ui_sdl_critical_check(int val);
void	ui_critical_check(t_ui_bool val, const char *msg);
void    *ui_secure_malloc(size_t  len);

//calculus
void    ui_calculate_win_content_actual_size(t_ui_win *win);
void    ui_infer_elem_actual_size(t_ui_elem *e);
void    ui_infer_actual_size(SDL_Rect *reference_rect, t_percent_rect *proportions, SDL_Rect
								*to_fill);

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
t_ui_elem *
ui_add_elem(t_ui_elem *parent, t_percentage x, t_percentage y, t_percentage w,
            t_percentage h, char disp_priority,
            void (*display_func)(t_ui_elem *), t_ui_bool sensible,
            void (*store_free_func)(void *));
void        ui_display_elem(t_ui_elem *e);
void        display_elem(t_ui_elem *e);
void        ui_paint_elem(t_ui_elem *e, int r, int g, int b, int a);
//blocking
void    ui_colorblock_1(t_ui_elem *e);
void    ui_display_button(t_ui_elem *e);
void    ui_display_radio_space(t_ui_elem *e);
void    ui_display_radio_button(t_ui_elem *e);

//display
void        ui_colorize_elem(t_ui_elem *e, int r, int g, int b, int a);
TTF_Font    *ui_load_font(const char *path, int size);
void        ui_close_font(TTF_Font *font);
t_ui_img    *ui_text_to_texture(const char *text, int font_index, t_ui_color
	*foreground, t_ui_color *background, t_ui_elem *e);
void        ui_display_img_at_center_of_elem(t_ui_elem *e, t_ui_img *img);
void        ui_display_img(t_ui_elem *e, t_ui_img *img, t_percentage x,
						   t_percentage y);
t_ui_img    *ui_create_colored_texture(t_ui_win *win, int w, int h, t_ui_color
*color);
//Interface elements
t_ui_elem   *ui_create_button(t_ui_elem *parent, t_percentage x,
							  t_percentage y, t_percentage w, t_percentage h,
							  const char *text,
							  void (*click_func)(t_ui_elem*,
							  		SDL_MouseButtonEvent*));
t_ui_elem   *ui_create_radio_button_container(t_ui_elem *parent, t_percentage
x, t_percentage y, t_percentage w, t_percentage h);
t_ui_elem *ui_create_radio_button(t_ui_elem *parent, const char *choice_text,
                                  short choice_index);

//Sensibility
void ui_add_clickable_zones(t_ui_elem *e, t_percent_rect *zones,
                            void (*click_func)(t_ui_elem *,
                                               SDL_MouseButtonEvent*),
                            short nb_sensible_zones);

//events
void    ui_handle_events(t_ui *ui);

//Pre-made callbacks
void    ui_stop_event_handling(t_ui_elem *e, SDL_MouseButtonEvent *ev);/*Uses
 * the element to set 'keep_going' to false.(In its containing ui.)*/
void    ui_debug_say_clicked(t_ui_elem *e, SDL_MouseButtonEvent *ev);
void    ui_free_nothing(void *unused);
void    ui_display_nothing(t_ui_elem *e);

#endif //UI
