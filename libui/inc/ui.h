#ifndef UI
#define UI

#include <stdio.h>
#include <unistd.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#define FONT_NB 1

#define UI_TRUE 1
#define UI_FALSE 0

#define UI_INIT_VIDEO			SDL_INIT_VIDEO
#define UI_INIT_TIMER			SDL_INIT_TIMER
#define UI_INIT_AUDIO			SDL_INIT_AUDIO
#define UI_INIT_VIDEO			SDL_INIT_VIDEO
#define UI_INIT_JOYSTICK		SDL_INIT_JOYSTICK
#define UI_INIT_HAPTIC		  	SDL_INIT_HAPTIC
#define UI_INIT_GAMECONTROLLER  SDL_INIT_GAMECONTROLLER
#define UI_INIT_EVENTS		 	SDL_INIT_EVENTS
#define UI_INIT_EVERYTHING	 	SDL_INIT_EVERYTHING
#define UI_INIT_NOPARACHUT	 	SDL_INIT_NOPARACHUTE

#define UI_RENDERER_SOFTWARE		SDL_RENDERER_SOFTWARE
#define UI_RENDERER_ACCELERATED 	SDL_RENDERER_ACCELERATED
#define UI_RENDERER_PRESENTVSYNC	SDL_RENDERER_PRESENTVSYNC
#define UI_RENDERER_TARGETTEXTURE	SDL_RENDERER_TARGETTEXTURE

#define UI_WINDOW_FULLSCREEN			SDL_WINDOW_FULLSCREEN
#define UI_WINDOW_FULLSCREEN_DESKTOP	SDL_WINDOW_FULLSCREEN_DESKTOP
#define UI_WINDOW_OPENGL				SDL_WINDOW_OPENGL
#define UI_WINDOW_VULKAN				SDL_WINDOW_VULKAN
#define UI_WINDOW_METAL					SDL_WINDOW_METAL
#define UI_WINDOW_HIDDEN				SDL_WINDOW_HIDDEN
#define UI_WINDOW_SHOWN					SDL_WINDOW_SHOWN
#define UI_WINDOW_BORDERLESS			SDL_WINDOW_BORDERLESS
#define UI_WINDOW_RESIZABLE				SDL_WINDOW_RESIZABLE
#define UI_WINDOW_MINIMIZED				SDL_WINDOW_MINIMIZED
#define UI_WINDOW_MAXIMIZED				SDL_WINDOW_MAXIMIZED
#define UI_WINDOW_INPUT_GRABBED			SDL_WINDOW_INPUT_GRABBED
#define UI_WINDOW_ALLOW_HIGHDPI			SDL_WINDOW_ALLOW_HIGHDPI

#define UI_ALPHA_OPAQUE		 SDL_ALPHA_OPAQUE
#define UI_ALPHA_TRANSPARENT	SDL_ALPHA_TRANSPARENT

#define UI_EL_WIN(e) ((t_ui_win*)(e->win))
#define UI_EL_REND(e) UI_EL_WIN(e)->rend
#define UI_EL_UI(e) ((t_ui*)(UI_EL_WIN(e)->ui))
#define UI_WIN_UI(w) ((t_ui*)(w->ui))
#define UI_EXPAND_COLOR(x) x.r, x.g, x.b, x.a
#define UI_EXPAND_COLOR_PTR(x) x->r, x->g, x->b, x->a
#define UI_PX_FORMAT_FROM_EL(x) ((t_ui*)(((t_ui_win*)(x->win))->ui))->default_pixel_format
#define UI_FONT(e, x)  ((t_ui*)(((t_ui_win*)(e->win))->ui))->fonts[x]

#define UI_SLIDER_CURSOR_WIDTH_IN_PX 10
#define UI_SLIDER_HEIGHT_IN_PX 15

typedef int t_ui_bool;//Can be set to UI_TRUE or UI_FALSE.
typedef SDL_Texture t_ui_img;//An image that can be used by the ui.
typedef SDL_Color t_ui_color;/*A color. r = red, g = green, b = blue, a =
 * alpha (the transparency level. Higher means less transparent.). All of
 * these values are meant to go from 0 to 255. Example: opaque red: r = 255,
 * b = 0, b = 0, a = 255.*/

/*A structure that will only be used as a mean to make some
generic code.*/
typedef struct	s_link
{
	struct s_link	*next;
	struct s_link	*prev;
}				t_link;

typedef struct			s_ui_elem
{
	struct s_ui_elem	*next;
	struct s_ui_elem	*prev;
	SDL_Rect			relative_dimensions;
	void				(*elem_dimensions_resolution_func)(struct s_ui_elem*);
	SDL_Rect			actual_dimensions;
	char				display_priority;
	void				(*display_func)(struct s_ui_elem*);
	void				*store;
	void				(*free_store_func)(void*);
	t_ui_bool			sensible;
	SDL_Rect			*sensible_zones_relative_dimensions;
	void				(*sensible_zones_resolution_func)(struct s_ui_elem*);
	SDL_Rect			sensible_zones_actual_dimensions;
	short				nb_sensible_zones;
	t_ui_bool			has_sub_hovers;
	void				(*hover_func)(struct s_ui_elem*);
	t_ui_bool			has_sub_clicks;
	void				(*click_func)(struct s_ui_elem*, SDL_MouseButtonEvent*);
	struct s_ui_elem	*sub_elems;
	struct s_ui_elem	*parent;
	void				*win;
}						t_ui_elem;

typedef struct				s_ui_event_block
{
	struct s_ui_event_block	*next;
	void					(*event_handler_func)(void *win, void *store, SDL_Event*);
	void					*store;
}							t_ui_event_block;

typedef struct			s_ui_win
{
	/*Let those as the 2 first members, in the same order, or problems there
	will be!*/
	struct s_ui_win		*next;//The next window in line.
	struct s_ui_win		*prev;/*Previous window.
	other content.*/
	void				*ui;/*Points back to its owning ui. Use this to modify
	keep_going or access your fonts. Note that elems have a win pointer.*/
	SDL_Window			*sdl_ptr;
	SDL_Renderer		*rend;
	int					width;//Not percentages but the real value in pixels.
	int					height;
	t_ui_elem			*content;/*The root elem of the window. Should be used to
	set the background color/ image.*/
	t_ui_event_block	*main_events;
	t_ui_event_block	*side_events;//A list of secondary event interception funcs.
}						t_ui_win;

typedef struct						s_permanent_func_block
{
	void							(*func)(void* store);
	void							*store;//note: you can use it as an int with a cast.
	struct s_permanent_func_block	*next;
}									t_perma_func_block;

typedef struct			s_ui
{
	t_ui_win			*wins; //This list stores all the windows you added to the ui.
	t_ui_elem			*focused;//TODO: Keep track of the currently focused element.
	t_ui_bool			keep_going;/*Goes to true when ui_handle_events is called.
	Set it to false to make the loop stop.*/
	TTF_Font			*fonts[FONT_NB];//A tab to store your font pointers.
	Uint32				default_pixel_format;
	t_perma_func_block	*perma_funcs;
	void				(*render_copy_func)(void*);
}						t_ui;

typedef struct	s_ui_wincontent_store
{
	t_ui_img	*success;
	t_ui_img	*error;
}				t_ui_wincontent_store;

typedef struct	s_ui_button_store
{
	t_ui_img	*text_img;
	SDL_Rect	sensible_zone;
}				t_ui_button_store;

typedef struct	s_radio_space_store
{
	t_ui_img	*unchecked_img;
	t_ui_img	*checked_img;
	short		current_choice;
}				t_radio_space_store;

typedef struct	s_radio_button_store
{
	SDL_Rect	sensible_zone;
	short		choice_index;
	t_ui_img	**checkbox_img;
	t_ui_img	*text;
}				t_radio_button_store;

typedef struct		s_checkbox_button_store
{
	SDL_Rect		sensible_zone;
	t_ui_img		*text;
	t_ui_img		*checkbox;//We will use this to know wether the box is checked.
}					t_checkbox_button_store;

typedef struct		s_slider_store
{
	int				max_val;
	int				current_val;
	SDL_Rect		sensible_zone;
	void			*drag_perma_func;
	void			*previous_event_handling_func;
}					t_slider_store;

typedef	struct		s_text_space_store
{
	int				police_font;
	char			*text;
	int				text_len;
	int				pos;
	t_ui_img		*text_img;
	SDL_Rect		sensible_zone;
}					t_text_space_store;

typedef struct	s_img_disp_store
{
	t_ui_img			*img_texture;
}								t_img_disp_store;

typedef struct			s_scroll_space_store
{
	SDL_Rect			sensible_zone;
	t_ui_event_block	*ev_block;
}						t_scroll_space_store;

typedef struct	s_sub_layer_store
{
	t_ui_img	*target;
	SDL_Rect	virtual_space;//x and y indicate the position of the visualizer.
	//w and h are the dimensions of the virtual space.
}				t_sub_layer_store;

//basic stuff
void								mem_copy(char *dest, const char *src, int len);
void								add_link_to_list(t_link **list, t_link *new_link);
void								remove_link_from_list(t_link **list, t_link *to_remove);
void								free_list(t_link *list, void(*free_func)(void*));
void								init_list(t_link **list, t_link *new_link);
void								list_add_link_at_start(t_link **list, t_link *new_link);
void								list_add_link_at_end(t_link *last_link, t_link *new_link);
void								list_add_link_in_the_middle(t_link *next_link_to_be, t_link *new_link);
t_perma_func_block					*ui_add_perma_func(t_ui *ui, void (*func)(void*), void *store);
void								ui_remove_permafunc(t_ui *ui, t_perma_func_block *to_delete);
void								ui_insert_str_in_str(char *to_modify, int tm_len, const char *to_insert, int ti_len, int pos);
int									ui_strlen(const char *s);

//Int manipulation
int	ui_get_percentage_of_int(int reference, int percentage);
int	ui_get_subset_proportionnal_to_proportion(int actual_max, int reference_max, int reference_subset);
int	ui_get_proportion_in_percents(int bigger_val, int lesser_val);
int	ui_calculate_start_of_center(int total_length, int length_to_center);

//security
void	ui_sdl_critical_check(int val);
void	ui_critical_check(t_ui_bool val, const char *msg);
void	*ui_secure_malloc(size_t  len);
void	ui_secure_realloc(void **to_realloc, size_t len);

//dimensions resolution
void	ui_resolve_win_content_actual_size(t_ui_win *win);
void	ui_resolve_as_percentages(t_ui_elem *e);
void	ui_resolve_keep_actual_dimensions(t_ui_elem *e);
void	ui_resolve_keep_fixed_dimensions(t_ui_elem *e);
void	ui_resolve_as_square_from_h(t_ui_elem *e);
void	ui_set_x_and_y_from_ref(t_ui_elem *e);
void	ui_resolve_w_as_percentage_keep_actual_h(t_ui_elem *e);
void	ui_resolve_clickable_zone_as_percentage(t_ui_elem *e);
void	ui_resolve_clickable_zone_keep_actual_dimensions(t_ui_elem *e);
void	ui_resolve_clickable_zone_w_as_percentage_keep_actual_h(t_ui_elem *e);
void	ui_resolve_clickable_zone_as_square_from_h(t_ui_elem *e);

//core functions
t_ui	*ui_init(uint32_t ui_flags, int img_flags);
void	ui_close(t_ui *to_destroy);
void	refresh_win(t_ui_win *win);

//windows
t_ui_win	*ui_add_window(t_ui *ui, const char *title, int x, int y, int 		w, int h, uint32_t flags, uint32_t render_flags, void (*display_func)(t_ui_elem *));
void		ui_update_window_size(t_ui_win *win);

//elems
t_ui_img	*ui_load_img(t_ui_win *win, const char *img_path);
t_ui_elem	*ui_create_virgin_elem(int x, int y, int w,
									int h, t_ui_win *win,
									char display_priority,
									void (*display_func)(t_ui_elem *));
void		ui_remove_elem(t_ui_elem *e);
void		ui_transfer_elem(t_ui_elem *new_parent, t_ui_elem *e,
								char new_disp_priority);
t_ui_elem *
ui_add_elem(t_ui_elem *parent, int x, int y, int w,
			int h, char disp_priority,
			void (*display_func)(t_ui_elem *), t_ui_bool sensible,
			void (*store_free_func)(void *), void
			(*elem_dimensions_resolution_func)(t_ui_elem*));
void		ui_display_elem(t_ui_elem *e);
void		ui_paint_elem(t_ui_elem *e, int r, int g, int b, int a);
void		incorporate_sub_elem(t_ui_elem **list, t_ui_elem *to_incorporate);
void		ui_redimension_elem_and_its_content(t_ui_elem *e);

//blocking
void	ui_free_wincontent_store(void *to_free);
void	ui_colorblock_1(t_ui_elem *e);
void	ui_display_button(t_ui_elem *e);
void	ui_display_radio_space(t_ui_elem *e);
void	ui_display_radio_button(t_ui_elem *e);

//display
void		ui_colorize_elem(t_ui_elem *e, int r, int g, int b, int a);
TTF_Font	*ui_load_font(const char *path, int size);
void		ui_close_font(TTF_Font *font);
t_ui_img	*ui_text_to_texture(const char *text, int font_index, t_ui_color
	*foreground, t_ui_color *background, t_ui_elem *e);
void		ui_display_img_at_center_of_elem(t_ui_elem *e, t_ui_img *img);
void		ui_display_img(t_ui_elem *e, t_ui_img *img, int x,
							int y);
void		ui_display_img_at_absolute_pos(t_ui_elem *e, t_ui_img *img, int x, int y);
void		ui_display_img_with_absolute_dimensions(t_ui_elem *e, t_ui_img *img, int w, int h);
t_ui_img	*ui_create_colored_texture(t_ui_win *win, int w, int h, t_ui_color *color);
void		ui_draw_fullcircle(t_ui_img *img, int w, int h, int size,
								t_ui_win *win);
void		ui_display_absolute_colored_rect(t_ui_elem *e, SDL_Rect *r, SDL_Color *c);
void		ui_display_absolute_rect_relative_to_elem(t_ui_elem *e, SDL_Rect *r, SDL_Color *c);

//Interface elements
t_ui_elem	*ui_create_button(t_ui_elem *parent, int x,
							  int y, int w, int h,
							  const char *text,
							  void (*click_func)(t_ui_elem*,
							  		SDL_MouseButtonEvent*));
t_ui_elem	*ui_create_radio_button_container(t_ui_elem *parent, int
x, int y, int w, int h);
t_ui_elem	*ui_create_radio_button(t_ui_elem *parent, const char *choice_text,
short choice_index);
t_ui_elem	*ui_create_checkbox_button(t_ui_elem *parent, const char *text, int x, int y);
t_ui_elem	*ui_create_slider(t_ui_elem *parent, int x, int y, int w, int current_cursor_val, int max_cursor_val);
t_ui_elem	*ui_create_text_line_input(t_ui_elem *parent, char *text, int x, int y, int w, int h);
t_ui_elem	*ui_create_img_display(t_ui_elem *parent, int x, int y, int w, int h,
		const char *img_path);
t_ui_elem	*ui_create_scroll_space(t_ui_elem *parent, int x, int y, int visible_w,
		int visible_h, int virtual_w, int virtual_h);

//Sensibility
void ui_add_clickable_zones(t_ui_elem *e, SDL_Rect *zones,
	void (*click_func)(t_ui_elem*, SDL_MouseButtonEvent*),
	short nb_sensible_zones, void (*sensible_zones_resolution_func) (t_ui_elem*));

//event blocks
t_ui_event_block	*ui_add_main_event(t_ui_win *win, void (*event_handler_func)(void *win, void *store, SDL_Event*), void *store);
t_ui_event_block	*ui_add_side_event(t_ui_win *win, void (*event_handler_func)(void *win, void *store, SDL_Event*), void *store);
t_ui_event_block	*ui_add_exclusive_side_event(t_ui_win *win, void (*event_handler_func)(void*, SDL_Event*), void *store);
void				ui_close_current_main_event(t_ui_win *win);
void				ui_remove_event(t_ui_event_block **list, t_ui_event_block *to_remove);

//events
t_ui_bool	ui_is_point_in_rect(Sint32 x, Sint32 y, SDL_Rect *rect);
void		ui_handle_events(t_ui *ui);
void		ui_transmit_click_event(t_ui_elem *e, SDL_MouseButtonEvent *ev);
void		ui_close_current_main_event(t_ui_win *win);

//Pre-made callbacks
void	ui_stop_event_handling(t_ui_elem *e, SDL_MouseButtonEvent *ev);/*Uses
 * the element to set 'keep_going' to false.(In its containing ui.)*/
void	ui_debug_say_clicked(t_ui_elem *e, SDL_MouseButtonEvent *ev);
void	ui_free_nothing(void *unused);
void	ui_display_nothing(t_ui_elem *e);
void	ui_default_event_handler(t_ui_win *win, SDL_Event *ev);

//Data printing
void	ui_display_rect_values(SDL_Rect *rect);

//scroll functions
void			ui_move_sub_layer_vision(t_ui_elem *sub_layer, int x, int y);
t_ui_elem	*ui_get_scroll_space_sub_layer(t_ui_elem *e);

#endif //UI
