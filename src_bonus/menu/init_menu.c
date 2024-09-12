/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_menu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrave <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 11:58:59 by ttrave            #+#    #+#             */
/*   Updated: 2024/09/12 16:36:23 by ttrave           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "menu.h"
#include "img.h"
#include "parsing.h"
#include "err.h"
#include "utils.h"
#include "menu.h"

static void	init_buttons_menu(t_menu *menu, size_t w, size_t h)
{
	menu->buttons[BUT_START] = (t_button){.pos = (t_ulpoint){.x = part(w, 0.5),
		.y = part(h, 0.3)}, .dim = (t_ulpoint){.x = part(w, 0.2),
		.y = part(h, 0.1)}, .state = IDLE, .color_idle[0] = 0x00101010,
		.color_idle[1] = 0x00505050, .color_hover[0] = 0x00303030,
		.color_hover[1] = 0x00707070, .window = WIN_MAIN};
	menu->buttons[BUT_SETTINGS] = (t_button){.pos = (t_ulpoint){.x = part(w, 0.5),
		.y = part(h, 0.5)}, .dim = (t_ulpoint){.x = part(w, 0.2),
		.y = part(h, 0.1)}, .state = IDLE, .color_idle[0] = 0x00101010,
		.color_idle[1] = 0x00505050, .color_hover[0] = 0x00303030,
		.color_hover[1] = 0x00707070, .window = WIN_MAIN};
	menu->buttons[BUT_BACK] = (t_button){.pos = (t_ulpoint){.x = part(w, 0.35),
		.y = part(h, 0.8)}, .dim = (t_ulpoint){.x = part(w, 0.08),
		.y = part(h, 0.08)}, .state = IDLE, .color_idle[0] = 0x00101010,
		.color_idle[1] = 0x00505050, .color_hover[0] = 0x00303030,
		.color_hover[1] = 0x00707070, .window = WIN_SETTINGS};
	menu->buttons[BUT_EXIT] = (t_button){.pos = (t_ulpoint){.x = part(w, 0.5),
		.y = part(h, 0.7)}, .dim = (t_ulpoint){.x = part(w, 0.2),
		.y = part(h, 0.1)}, .state = IDLE, .color_idle[0] = 0x00101010,
		.color_idle[1] = 0x00505050, .color_hover[0] = 0x00303030,
		.color_hover[1] = 0x00707070, .window = WIN_MAIN};
	menu->buttons[BUT_YES] = (t_button){.pos = (t_ulpoint){.x = part(w, 0.45),
		.y = part(h, 0.55)}, .dim = (t_ulpoint){.x = part(w, 0.08),
		.y = part(h, 0.08)}, .state = IDLE, .color_idle[0] = 0x00101010,
		.color_idle[1] = 0x00ff1b1e, .color_hover[0] = 0x00303030,
		.color_hover[1] = 0x00ff3d40, .window = WIN_EXIT};
	menu->buttons[BUT_NO] = (t_button){.pos = (t_ulpoint){.x = part(w, 0.55),
		.y = part(h, 0.55)}, .dim = (t_ulpoint){.x = part(w, 0.08),
		.y = part(h, 0.08)}, .state = IDLE, .color_idle[0] = 0x00101010,
		.color_idle[1] = 0x00505050, .color_hover[0] = 0x00303030,
		.color_hover[1] = 0x00707070, .window = WIN_EXIT};
}

inline static void	init_menu_images(t_menu *menu)
{
	menu->title.px = NULL;
	menu->confirm.px = NULL;
	menu->resume.px = NULL;
	menu->buttons[BUT_START].string.px = NULL;
	menu->buttons[BUT_SETTINGS].string.px = NULL;
	menu->buttons[BUT_BACK].string.px = NULL;
	menu->buttons[BUT_EXIT].string.px = NULL;
	menu->buttons[BUT_YES].string.px = NULL;
	menu->buttons[BUT_NO].string.px = NULL;
}

static int	load_menu_images(t_mlx *mlx, t_menu *menu, size_t w, size_t h)
{
	init_menu_images(menu);
	return (load_img(mlx->mlx, "./assets/core/title.bmp", &menu->title,
			(t_dim){.w = part(w, 0.1), .h = part(h, 0.1)})
		|| load_img(mlx->mlx, "./assets/core/confirm.bmp", &menu->confirm,
			(t_dim){.w = part(w, 0.1), .h = part(h, 0.1)})
		|| load_img(mlx->mlx, "./assets/core/resume.bmp", &menu->resume,
			(t_dim){.w = part(w, 0.1), .h = part(h, 0.1)})
		|| load_img(mlx->mlx, "./assets/core/start.bmp",
			&menu->buttons[BUT_START].string,
			(t_dim){.w = part(w, 0.1), .h = part(h, 0.1)})
		|| load_img(mlx->mlx, "./assets/core/settings.bmp",
			&menu->buttons[BUT_SETTINGS].string,
			(t_dim){.w = part(w, 0.1), .h = part(h, 0.1)})
		|| load_img(mlx->mlx, "./assets/core/back.bmp",
			&menu->buttons[BUT_BACK].string,
			(t_dim){.w = part(w, 0.1), .h = part(h, 0.1)})
		|| load_img(mlx->mlx, "./assets/core/exit.bmp",
			&menu->buttons[BUT_EXIT].string,
			(t_dim){.w = part(w, 0.1), .h = part(h, 0.1)})
		|| load_img(mlx->mlx, "./assets/core/yes.bmp",
			&menu->buttons[BUT_YES].string,
			(t_dim){.w = part(w, 0.1), .h = part(h, 0.1)})
		|| load_img(mlx->mlx, "./assets/core/no.bmp",
				&menu->buttons[BUT_NO].string,
			(t_dim){.w = part(w, 0.1), .h = part(h, 0.1)}));
}

int	init_menu(t_mlx *mlx, t_menu *menu, t_set *set)
{
	menu->background = malloc(set->wid * set->hei * sizeof(uint32_t));
	if (menu->background == NULL)
	{
		ft_perror(ERR_MALLOC);
		return (1);
	}
	init_buttons_menu(menu, set->wid, set->hei);
	if (load_menu_images(mlx, menu, set->wid, set->hei) == 1)
	{
		free(menu->title.px);
		free(menu->confirm.px);
		free(menu->resume.px);
		free(menu->buttons[BUT_START].string.px);
		free(menu->buttons[BUT_SETTINGS].string.px);
		free(menu->buttons[BUT_BACK].string.px);
		free(menu->buttons[BUT_EXIT].string.px);
		free(menu->buttons[BUT_YES].string.px);
		free(menu->buttons[BUT_NO].string.px);
		free(menu->background);
		return (1);
	}
	menu->window = WIN_MAIN;
	menu->first_render = 1;
	menu->prev_keys = 0;
	menu->first_start = 1;
	return (0);
}
