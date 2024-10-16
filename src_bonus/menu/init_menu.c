/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_menu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrave <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 11:58:59 by ttrave            #+#    #+#             */
/*   Updated: 2024/10/16 16:41:29 by ttrave           ###   ########.fr       */
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

static void	init_textfields_settings(t_set *set, t_menu *menu, size_t w,
	size_t h)
{
	menu->textfields[SET_FOV] = (t_textfield){.pos = (t_ulpoint){part(w, 0.33),
		part(h, 0.15)}, .dim = (t_ulpoint){part(w, 0.12), part(h, 0.06)},
		.precision = 0, .v_min = MIN_FOV, .v_max = MAX_FOV,
		.dst = &set->fov_deg, .state = IDLE, .len = 0, .type = DOUBLE};
	menu->textfields[SET_VIEW] = (t_textfield){.pos = (t_ulpoint){part(w, 0.33),
		part(h, 0.27)}, .dim = (t_ulpoint){part(w, 0.12), part(h, 0.06)},
		.precision = 0, .v_min = MIN_VIEW, .v_max = MAX_VIEW,
		.dst = &set->view, .state = IDLE, .len = 0, .type = DOUBLE};
	menu->textfields[SET_SENSI] = (t_textfield){.pos = (t_ulpoint){part(w,
			0.33), part(h, 0.39)}, .dim = (t_ulpoint){part(w, 0.12), part(h,
			0.06)}, .precision = 2, .v_min = MIN_SENSI, .v_max = MAX_SENSI,
		.dst = &set->sensi, .state = IDLE, .len = 0, .type = DOUBLE};
	menu->textfields[SET_SPEEDMAX] = (t_textfield){.pos = (t_ulpoint){part(w,
			0.33), part(h, 0.51)}, .dim = (t_ulpoint){part(w, 0.12), part(h,
			0.06)}, .precision = 2, .v_min = MIN_SPEEDMAX, .v_max = MAX_SPEEDMAX,
		.dst = &set->speedmax, .state = IDLE, .len = 0, .type = DOUBLE};
	menu->textfields[SET_ACCEL] = (t_textfield){.pos = (t_ulpoint){part(w,
			0.33), part(h, 0.63)}, .dim = (t_ulpoint){part(w, 0.12), part(h,
			0.06)}, .precision = 2, .v_min = MIN_ACCEL, .v_max = MAX_ACCEL,
		.dst = &set->accel, .state = IDLE, .len = 0, .type = DOUBLE};
	menu->textfields[SET_WID] = (t_textfield){.pos = (t_ulpoint){part(w, 0.50),
		part(h, 0.88)}, .dim = (t_ulpoint){part(w, 0.12), part(h, 0.06)},
		.precision = 0, .v_min = (double)MIN_WID, .v_max = (double)MAX_WID,
		.dst = &set->saved_w, .state = IDLE, .len = 0, .type = UINT};
	menu->textfields[SET_HEI] = (t_textfield){.pos = (t_ulpoint){part(w, 0.64),
		part(h, 0.88)}, .dim = (t_ulpoint){part(w, 0.12), part(h, 0.06)},
		.precision = 0, .v_min = (double)MIN_WID, .v_max = (double)MAX_WID,
		.dst = &set->saved_h, .state = IDLE, .len = 0, .type = UINT};
}

static void	init_sliders_settings(t_menu *menu, t_set *set, size_t w, size_t h)
{
	menu->sliders[SET_FOV] = (t_slider){.pos = (t_ulpoint){.x = part(w, 0.55),
		.y = part(h, 0.15)}, .dim = (t_ulpoint){.x = part(w, 0.3),
		.y = part(h, 0.05)}, .state = IDLE, .type = DOUBLE,
		.dst = &set->fov_deg, .v_min = MIN_FOV, .v_max = MAX_FOV};
	menu->sliders[SET_VIEW] = (t_slider){.pos = (t_ulpoint){.x = part(w, 0.55),
		.y = part(h, 0.27)}, .dim = (t_ulpoint){.x = part(w, 0.3),
		.y = part(h, 0.05)}, .state = IDLE, .type = DOUBLE,
		.dst = &set->view, .v_min = MIN_VIEW, .v_max = MAX_VIEW};
	menu->sliders[SET_SENSI] = (t_slider){.pos = (t_ulpoint){.x = part(w, 0.55),
		.y = part(h, 0.39)}, .dim = (t_ulpoint){.x = part(w, 0.3),
		.y = part(h, 0.05)}, .state = IDLE, .type = DOUBLE,
		.dst = &set->sensi, .v_min = MIN_SENSI, .v_max = MAX_SENSI};
	menu->sliders[SET_SPEEDMAX] = (t_slider){.pos = (t_ulpoint){.x = part(w, 0.55),
		.y = part(h, 0.51)}, .dim = (t_ulpoint){.x = part(w, 0.3),
		.y = part(h, 0.05)}, .state = IDLE, .type = DOUBLE,
		.dst = &set->speedmax, .v_min = MIN_SPEEDMAX, .v_max = MAX_SPEEDMAX};
	menu->sliders[SET_ACCEL] = (t_slider){.pos = (t_ulpoint){.x = part(w, 0.55),
		.y = part(h, 0.63)}, .dim = (t_ulpoint){.x = part(w, 0.3),
		.y = part(h, 0.05)}, .state = IDLE, .type = DOUBLE,
		.dst = &set->accel, .v_min = MIN_ACCEL, .v_max = MAX_ACCEL};
}

static int	load_menu_images(t_mlx *mlx, t_menu *menu)
{
	return (load_img(mlx->mlx, "assets/core/characters/characters.bmp",
				&menu->characters,
			(t_dim){.w = WIDTH_CHAR_IMG, .h = HEIGHT_CHAR_IMG}));
}

int	init_menu(t_mlx *mlx, t_menu *menu, t_set *set)
{
	menu->background = malloc(set->wid * set->hei * sizeof(uint32_t));
	if (menu->background == NULL)
	{
		ft_perror(ERR_MALLOC);
		return (1);
	}
	init_buttons_main(menu, set->wid, set->hei);
	init_buttons_settings(menu, set->wid, set->hei);
	init_buttons_exit(menu, set->wid, set->hei);
	init_sliders_settings(menu, set, set->wid, set->hei);
	init_textfields_settings(set, menu, set->wid, set->hei);
	menu->characters.px = NULL;
	if (load_menu_images(mlx, menu) == 1)
	{
		free(menu->background);
		free(menu->characters.px);
		return (1);
	}
	menu->window = WIN_MAIN;
	menu->first_render = 1;
	menu->prev_keys = 0;
	menu->first_start = 1;
	return (0);
}
