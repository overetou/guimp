#include "ui.h"

//You have to specify the window for wich the store will be active. If you want
// to use the same image for several window, call this function several time.
//I know, this is not ideal, but that's how SDL works.
t_ui_img *ui_load_img(t_ui_win *win, const char *img_path)
{
	return IMG_LoadTexture(win->rend, img_path);
}
