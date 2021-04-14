//
// Created by osc on 14/04/2021.
//
#include "ui.h"

void win_percent_rect_to_sdl_rect(t_ui *ui, t_percent_rect *p_rect,
                                  SDL_Rect *sdl_rect)
{
	sdl_rect->x = ui->win_width * p_rect->x / 100;
	sdl_rect->y = ui->win_height * p_rect->y / 100;
	sdl_rect->w = ui->win_width * p_rect->w / 100;
	sdl_rect->h = ui->win_height * p_rect->h / 100;
}
