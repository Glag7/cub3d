/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_menu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrave <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 11:58:59 by ttrave            #+#    #+#             */
/*   Updated: 2024/09/06 19:20:16 by ttrave           ###   ########.fr       */
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
	menu->buttons[0] = (t_button){.pos = (t_ulpoint){.x = part(w, 0.5),
			.y = part(h, 0.3)}, .dim = (t_ulpoint){.x = part(w, 0.2),
			.y = part(h, 0.1)}, .state = IDLE, .color_idle[0] = 0x00101010,
			.color_idle[1] = 0x00505050, .color_hover[0] = 0x00303030,
			.color_hover[1] = 0x00707070};
	menu->buttons[1] = (t_button){.pos = (t_ulpoint){.x = part(w, 0.5),
			.y = part(h, 0.3)}, .dim = (t_ulpoint){.x = part(w, 0.2),
			.y = part(h, 0.1)}, .state = IDLE, .color_idle[0] = 0x00101010,
			.color_idle[1] = 0x00505050, .color_hover[0] = 0x00303030,
			.color_hover[1] = 0x00707070};
	menu->buttons[2] = (t_button){.pos = (t_ulpoint){.x = part(w, 0.5),
			.y = part(h, 0.5)}, .dim = (t_ulpoint){.x = part(w, 0.2),
			.y = part(h, 0.1)}, .state = IDLE, .color_idle[0] = 0x00101010,
			.color_idle[1] = 0x00505050, .color_hover[0] = 0x00303030,
			.color_hover[1] = 0x00707070};
	menu->buttons[3] = (t_button){.pos = (t_ulpoint){.x = part(w, 0.4),
			.y = part(h, 0.7)}, .dim = (t_ulpoint){.x = part(w, 0.08),
			.y = part(h, 0.08)}, .state = IDLE, .color_idle[0] = 0x00101010,
			.color_idle[1] = 0x00505050, .color_hover[0] = 0x00303030,
			.color_hover[1] = 0x00707070};
	menu->buttons[4] = (t_button){.pos = (t_ulpoint){.x = part(w, 0.5),
			.y = part(h, 0.7)}, .dim = (t_ulpoint){.x = part(w, 0.2),
			.y = part(h, 0.1)}, .state = IDLE, .color_idle[0] = 0x00101010,
			.color_idle[1] = 0x00505050, .color_hover[0] = 0x00303030,
			.color_hover[1] = 0x00707070};
	menu->buttons[5] = (t_button){.pos = (t_ulpoint){.x = part(w, 0.4),
			.y = part(h, 0.6)}, .dim = (t_ulpoint){.x = part(w, 0.08),
			.y = part(h, 0.08)}, .state = IDLE, .color_idle[0] = 0x00101010,
			.color_idle[1] = 0x00ff1b1e, .color_hover[0] = 0x00303030,
			.color_hover[1] = 0x00ff3d40};
	menu->buttons[6] = (t_button){.pos = (t_ulpoint){.x = part(w, 0.6),
			.y = part(h, 0.6)}, .dim = (t_ulpoint){.x = part(w, 0.08),
			.y = part(h, 0.08)}, .state = IDLE, .color_idle[0] = 0x00101010,
			.color_idle[1] = 0x00505050, .color_hover[0] = 0x00303030,
			.color_hover[1] = 0x00707070};
}

inline static void	init_menu_images(t_menu *menu)
{
	menu->buttons[0].string.px = NULL;
	menu->buttons[1].string.px = NULL;
	menu->buttons[2].string.px = NULL;
	menu->buttons[3].string.px = NULL;
	menu->buttons[4].string.px = NULL;
	menu->buttons[5].string.px = NULL;
	menu->buttons[6].string.px = NULL;
}

#include <stdio.h>
static int	load_menu_images(t_mlx *mlx, t_menu *menu, size_t w, size_t h)
{
	return (load_img(mlx->mlx, "./assets/core/title.bmp", &menu->title, (t_dim){.w = part(w, 0.1), .h = part(h, 0.1)}) || !printf("0\n")
		|| load_img(mlx->mlx, "./assets/core/start.bmp", &menu->buttons[0].string, (t_dim){.w = part(w, 0.1), .h = part(h, 0.1)}) || !printf("1\n")
		|| load_img(mlx->mlx, "./assets/core/resume.bmp", &menu->buttons[1].string, (t_dim){.w = part(w, 0.1), .h = part(h, 0.1)}) || !printf("2\n")
		|| load_img(mlx->mlx, "./assets/core/settings.bmp", &menu->buttons[2].string, (t_dim){.w = part(w, 0.1), .h = part(h, 0.1)}) || !printf("3\n")
		|| load_img(mlx->mlx, "./assets/core/back.bmp", &menu->buttons[3].string, (t_dim){.w = part(w, 0.1), .h = part(h, 0.1)}) || !printf("4\n")
		|| load_img(mlx->mlx, "./assets/core/exit.bmp", &menu->buttons[4].string, (t_dim){.w = part(w, 0.1), .h = part(h, 0.1)}) || !printf("5\n")
		|| load_img(mlx->mlx, "./assets/core/yes.bmp", &menu->buttons[5].string, (t_dim){.w = part(w, 0.1), .h = part(h, 0.1)}) || !printf("6\n")
		|| load_img(mlx->mlx, "./assets/core/no.bmp", &menu->buttons[6].string, (t_dim){.w = part(w, 0.1), .h = part(h, 0.1)})) || !printf("7\n");
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
	init_menu_images(menu);
	if (load_menu_images(mlx, menu, set->wid, set->hei) == 1)
	{
		free(menu->title.px);
		free(menu->buttons[0].string.px);
		free(menu->buttons[1].string.px);
		free(menu->buttons[2].string.px);
		free(menu->buttons[3].string.px);
		free(menu->buttons[4].string.px);
		free(menu->buttons[5].string.px);
		free(menu->buttons[6].string.px);
		free(menu->background);
		return (1);
	}
	menu->window = MAIN;
	menu->resume = 0;
	return (0);
}
