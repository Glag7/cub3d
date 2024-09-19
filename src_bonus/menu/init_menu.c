/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_menu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrave <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 11:58:59 by ttrave            #+#    #+#             */
/*   Updated: 2024/09/19 16:38:44 by ttrave           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "menu.h"
#include "img.h"
#include "parsing.h"
#include "err.h"
#include "utils.h"
#include "menu.h"

static int	load_digits(t_mlx *mlx, t_menu *menu)
{
	return (load_img(mlx->mlx, "assets/core/digits/zero.bmp",
			&menu->digits[0], (t_dim){.w = 100, .h = 100})
		|| load_img(mlx->mlx, "assets/core/digits/one.bmp",
			&menu->digits[1], (t_dim){.w = 100, .h = 100})
		|| load_img(mlx->mlx, "assets/core/digits/two.bmp",
			&menu->digits[2], (t_dim){.w = 100, .h = 100})
		|| load_img(mlx->mlx, "assets/core/digits/three.bmp",
			&menu->digits[3], (t_dim){.w = 100, .h = 100})
		|| load_img(mlx->mlx, "assets/core/digits/four.bmp",
			&menu->digits[4], (t_dim){.w = 100, .h = 100})
		|| load_img(mlx->mlx, "assets/core/digits/five.bmp",
			&menu->digits[5], (t_dim){.w = 100, .h = 100})
		|| load_img(mlx->mlx, "assets/core/digits/six.bmp",
			&menu->digits[6], (t_dim){.w = 100, .h = 100})
		|| load_img(mlx->mlx, "assets/core/digits/seven.bmp",
			&menu->digits[7], (t_dim){.w = 100, .h = 100})
		|| load_img(mlx->mlx, "assets/core/digits/eight.bmp",
			&menu->digits[8], (t_dim){.w = 100, .h = 100})
		|| load_img(mlx->mlx, "assets/core/digits/nine.bmp",
			&menu->digits[9], (t_dim){.w = 100, .h = 100})
		|| load_img(mlx->mlx, "assets/core/digits/minus.bmp",
			&menu->digits[10], (t_dim){.w = 100, .h = 100})
		|| load_img(mlx->mlx, "assets/core/digits/dot.bmp",
			&menu->digits[11], (t_dim){.w = 100, .h = 100}));
}

static void	init_textfields_settings(t_menu *menu, size_t w, size_t h)
{
	menu->textfields[SET_FOV] = (t_textfield){.pos = (t_ulpoint){.x = part(w, 0.3),
		.y = part(h, 0.2)}, .dim = (t_ulpoint){.x = part(w, 0.05), .y = part(h, 0.05)},
		.type = DOUBLE, .src = &menu->sliders[SET_FOV].v_curr};
	menu->textfields[SET_VIEW] = (t_textfield){.pos = (t_ulpoint){.x = part(w, 0.3),
		.y = part(h, 0.4)}, .dim = (t_ulpoint){.x = part(w, 0.05), .y = part(h, 0.05)},
		.type = UINT, .src = &menu->sliders[SET_VIEW].v_curr};
	menu->textfields[SET_SENSI] = (t_textfield){.pos = (t_ulpoint){.x = part(w, 0.3),
		.y = part(h, 0.6)}, .dim = (t_ulpoint){.x = part(w, 0.05), .y = part(h, 0.05)},
		.type = DOUBLE, .src = &menu->sliders[SET_SENSI].v_curr};
}

static void	init_sliders_settings(t_menu *menu, t_set *set, size_t w, size_t h)
{
	menu->sliders[SET_FOV] = (t_slider){.pos = (t_ulpoint){.x = part(w, 0.5),
		.y = part(h, 0.2)}, .dim = (t_ulpoint){.x = part(w, 0.3),
		.y = part(h, 0.05)}, .state = IDLE, .type = DOUBLE, .dst = &set->fov_deg, .v_min = 10.,
		.v_max = 170., .v_curr = 90.};
	menu->sliders[SET_VIEW] = (t_slider){.pos = (t_ulpoint){.x = part(w, 0.5),
		.y = part(h, 0.4)}, .dim = (t_ulpoint){.x = part(w, 0.3),
		.y = part(h, 0.05)}, .state = IDLE, .type = UINT, .dst = &set->view, .v_min = 1,
		.v_max = 2000, .v_curr = 1000};
	menu->sliders[SET_SENSI] = (t_slider){.pos = (t_ulpoint){.x = part(w, 0.5),
		.y = part(h, 0.6)}, .dim = (t_ulpoint){.x = part(w, 0.3),
		.y = part(h, 0.05)}, .state = IDLE, .type = DOUBLE, .dst = &set->sensi, .v_min = 0.,
		.v_max = 5., .v_curr = 1.};
}

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
	menu->buttons[BUT_BACK] = (t_button){.pos = (t_ulpoint){.x = part(w, 0.32),
		.y = part(h, 0.88)}, .dim = (t_ulpoint){.x = part(w, 0.08),
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
	menu->digits[0].px = NULL;
	menu->digits[1].px = NULL;
	menu->digits[2].px = NULL;
	menu->digits[3].px = NULL;
	menu->digits[4].px = NULL;
	menu->digits[5].px = NULL;
	menu->digits[6].px = NULL;
	menu->digits[7].px = NULL;
	menu->digits[8].px = NULL;
	menu->digits[9].px = NULL;
	menu->digits[10].px = NULL;
	menu->digits[11].px = NULL;
}

static int	load_menu_images(t_mlx *mlx, t_menu *menu, size_t w, size_t h)
{
	return (load_img(mlx->mlx, "assets/core/title.bmp", &menu->title,
			(t_dim){.w = part(w, 0.1), .h = part(h, 0.1)})
		|| load_img(mlx->mlx, "assets/core/confirm.bmp", &menu->confirm,
			(t_dim){.w = part(w, 0.1), .h = part(h, 0.1)})
		|| load_img(mlx->mlx, "assets/core/resume.bmp", &menu->resume,
			(t_dim){.w = part(w, 0.1), .h = part(h, 0.1)})
		|| load_img(mlx->mlx, "assets/core/start.bmp",
			&menu->buttons[BUT_START].string,
			(t_dim){.w = part(w, 0.1), .h = part(h, 0.1)})
		|| load_img(mlx->mlx, "assets/core/settings.bmp",
			&menu->buttons[BUT_SETTINGS].string,
			(t_dim){.w = part(w, 0.1), .h = part(h, 0.1)})
		|| load_img(mlx->mlx, "assets/core/back.bmp",
			&menu->buttons[BUT_BACK].string,
			(t_dim){.w = part(w, 0.1), .h = part(h, 0.1)})
		|| load_img(mlx->mlx, "assets/core/exit.bmp",
			&menu->buttons[BUT_EXIT].string,
			(t_dim){.w = part(w, 0.1), .h = part(h, 0.1)})
		|| load_img(mlx->mlx, "assets/core/yes.bmp",
			&menu->buttons[BUT_YES].string,
			(t_dim){.w = part(w, 0.1), .h = part(h, 0.1)})
		|| load_img(mlx->mlx, "assets/core/no.bmp",
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
	init_sliders_settings(menu, set, set->wid, set->hei);
	init_textfields_settings(menu, set->wid, set->hei);
	init_menu_images(menu);
	if (load_digits(mlx, menu) == 1)
	{
		free(menu->digits[0].px);
		free(menu->digits[1].px);
		free(menu->digits[2].px);
		free(menu->digits[3].px);
		free(menu->digits[4].px);
		free(menu->digits[5].px);
		free(menu->digits[6].px);
		free(menu->digits[7].px);
		free(menu->digits[8].px);
		free(menu->digits[9].px);
		free(menu->digits[10].px);
		free(menu->digits[11].px);
	}
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
		free(menu->digits[0].px);
		free(menu->digits[1].px);
		free(menu->digits[2].px);
		free(menu->digits[3].px);
		free(menu->digits[4].px);
		free(menu->digits[5].px);
		free(menu->digits[6].px);
		free(menu->digits[7].px);
		free(menu->digits[8].px);
		free(menu->digits[9].px);
		free(menu->digits[10].px);
		free(menu->digits[11].px);
		return (1);
	}
	menu->window = WIN_MAIN;
	menu->first_render = 1;
	menu->prev_keys = 0;
	menu->first_start = 1;
	return (0);
}
