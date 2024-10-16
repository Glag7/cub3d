/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_menu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrave <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 11:58:59 by ttrave            #+#    #+#             */
/*   Updated: 2024/10/16 18:31:11 by ttrave           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include "menu.h"
#include "img.h"
#include "parsing.h"
#include "err.h"
#include "utils.h"
#include "menu.h"

static void	init_sliders_settings_movements(t_menu *menu, t_set *set, size_t w,
	size_t h)
{
	menu->sliders[SET_SPEEDMAX] = (t_slider){.pos = (t_ulpoint){.x = part(w,
			0.36), .y = part(h, 0.73)}, .dim = (t_ulpoint){.x = part(w, 0.25),
		.y = part(h, 0.05)}, .state = IDLE, .type = DOUBLE,
		.dst = &set->speedmax, .v_min = MIN_SPEEDMAX, .v_max = MAX_SPEEDMAX};
	menu->sliders[SET_ACCEL] = (t_slider){.pos = (t_ulpoint){.x = part(w, 0.76),
		.y = part(h, 0.31)}, .dim = (t_ulpoint){.x = part(w, 0.25),
		.y = part(h, 0.05)}, .state = IDLE, .type = DOUBLE,
		.dst = &set->accel, .v_min = MIN_ACCEL, .v_max = MAX_ACCEL};
	menu->sliders[SET_ACCELDIFF] = (t_slider){.pos = (t_ulpoint){.x = part(w,
			0.76), .y = part(h, 0.45)}, .dim = (t_ulpoint){.x = part(w, 0.25),
		.y = part(h, 0.05)}, .state = IDLE, .type = DOUBLE,
		.dst = &set->acceldiff, .v_min = MIN_ACCELDIFF, .v_max = MAX_ACCELDIFF};
	menu->sliders[SET_SLOWER] = (t_slider){.pos = (t_ulpoint){.x = part(w,
			0.76), .y = part(h, 0.59)}, .dim = (t_ulpoint){.x = part(w, 0.25),
		.y = part(h, 0.05)}, .state = IDLE, .type = DOUBLE,
		.dst = &set->slower, .v_min = MIN_SLOWER, .v_max = MAX_SLOWER};
}

static void	init_sliders_settings(t_menu *menu, t_set *set, size_t w, size_t h)
{
	menu->sliders[SET_FOV] = (t_slider){.pos = (t_ulpoint){.x = part(w, 0.36),
		.y = part(h, 0.31)}, .dim = (t_ulpoint){.x = part(w, 0.25),
		.y = part(h, 0.05)}, .state = IDLE, .type = DOUBLE,
		.dst = &set->fov_deg, .v_min = MIN_FOV, .v_max = MAX_FOV};
	menu->sliders[SET_VIEW] = (t_slider){.pos = (t_ulpoint){.x = part(w, 0.36),
		.y = part(h, 0.45)}, .dim = (t_ulpoint){.x = part(w, 0.25),
		.y = part(h, 0.05)}, .state = IDLE, .type = DOUBLE,
		.dst = &set->view, .v_min = MIN_VIEW, .v_max = MAX_VIEW};
	menu->sliders[SET_SENSI] = (t_slider){.pos = (t_ulpoint){.x = part(w, 0.36),
		.y = part(h, 0.59)}, .dim = (t_ulpoint){.x = part(w, 0.25),
		.y = part(h, 0.05)}, .state = IDLE, .type = DOUBLE,
		.dst = &set->sensi, .v_min = MIN_SENSI, .v_max = MAX_SENSI};
}

static int	load_menu(t_mlx *mlx, t_set *set, t_menu *menu)
{
	menu->characters.px = NULL;
	menu->background = malloc(set->wid * set->hei * sizeof(uint32_t));
	if (menu->background == NULL)
	{
		ft_perror(ERR_MALLOC);
		return (1);
	}
	return (load_img(mlx->mlx, "assets/core/characters/characters.bmp",
			&menu->characters,
			(t_dim){.w = WIDTH_CHAR_IMG, .h = HEIGHT_CHAR_IMG}));
}

int	init_menu(t_mlx *mlx, t_menu *menu, t_set *set)
{
	if (load_menu(mlx, set, menu) == 1)
		return (1);
	init_buttons_main(menu, set->wid, set->hei);
	init_buttons_settings(menu, set->wid, set->hei);
	init_buttons_exit(menu, set->wid, set->hei);
	init_sliders_settings(menu, set, set->wid, set->hei);
	init_sliders_settings_movements(menu, set, set->wid, set->hei);
	init_textfields_settings(set, menu, set->wid, set->hei);
	init_textfields_settings_movements(set, menu, set->wid, set->hei);
	menu->window = WIN_MAIN;
	menu->first_render = 1;
	menu->prev_keys = 0;
	menu->first_start = 1;
	return (0);
}
