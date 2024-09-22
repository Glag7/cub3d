/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_menu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrave <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 11:58:59 by ttrave            #+#    #+#             */
/*   Updated: 2024/09/22 19:50:42 by ttrave           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "menu.h"
#include "img.h"
#include "parsing.h"
#include "err.h"
#include "utils.h"
#include "menu.h"

static void	init_textfields_settings(t_menu *menu, size_t w, size_t h)
{
	menu->textfields[SET_FOV] = (t_textfield){.pos = (t_ulpoint){.x = part(w, 0.3),
		.y = part(h, 0.2)}, .dim = (t_ulpoint){.x = part(w, 0.08), .y = part(h, 0.05)},
		.type = UINT, .src = &menu->sliders[SET_FOV].v_curr};
	menu->textfields[SET_VIEW] = (t_textfield){.pos = (t_ulpoint){.x = part(w, 0.3),
		.y = part(h, 0.4)}, .dim = (t_ulpoint){.x = part(w, 0.08), .y = part(h, 0.05)},
		.type = UINT, .src = &menu->sliders[SET_VIEW].v_curr};
	menu->textfields[SET_SENSI] = (t_textfield){.pos = (t_ulpoint){.x = part(w, 0.3),
		.y = part(h, 0.6)}, .dim = (t_ulpoint){.x = part(w, 0.08), .y = part(h, 0.05)},
		.type = DOUBLE, .src = &menu->sliders[SET_SENSI].v_curr};
}

static void	init_sliders_settings(t_menu *menu, t_set *set, size_t w, size_t h)
{
	menu->sliders[SET_FOV] = (t_slider){.pos = (t_ulpoint){.x = part(w, 0.5),
		.y = part(h, 0.2)}, .dim = (t_ulpoint){.x = part(w, 0.3),
		.y = part(h, 0.05)}, .state = IDLE, .type = DOUBLE, .dst = &set->fov_deg, .v_min = 1.,
		.v_max = 179., .v_curr = 90.};
	menu->sliders[SET_VIEW] = (t_slider){.pos = (t_ulpoint){.x = part(w, 0.5),
		.y = part(h, 0.4)}, .dim = (t_ulpoint){.x = part(w, 0.3),
		.y = part(h, 0.05)}, .state = IDLE, .type = DOUBLE, .dst = &set->view, .v_min = 1.,
		.v_max = 2000., .v_curr = 1000.};
	menu->sliders[SET_SENSI] = (t_slider){.pos = (t_ulpoint){.x = part(w, 0.5),
		.y = part(h, 0.6)}, .dim = (t_ulpoint){.x = part(w, 0.3),
		.y = part(h, 0.05)}, .state = IDLE, .type = DOUBLE, .dst = &set->sensi, .v_min = 0.1,
		.v_max = 1., .v_curr = 0.3};
}

static void	init_buttons_menu(t_menu *menu, size_t w, size_t h)
{
	menu->buttons[BUT_START] = (t_button){.pos = (t_ulpoint){.x = part(w, 0.5),
		.y = part(h, 0.3)}, .dim = (t_ulpoint){.x = part(w, 0.2),
		.y = part(h, 0.1)}, .state = IDLE, .color_idle[0] = 0xFF101010,
		.color_idle[1] = 0xFF505050, .color_hover[0] = 0xFF303030,
		.color_hover[1] = 0xFF707070, .window = WIN_MAIN};
	menu->buttons[BUT_SETTINGS] = (t_button){.pos = (t_ulpoint){.x = part(w, 0.5),
		.y = part(h, 0.5)}, .dim = (t_ulpoint){.x = part(w, 0.2),
		.y = part(h, 0.1)}, .state = IDLE, .color_idle[0] = 0xFF101010,
		.color_idle[1] = 0xFF505050, .color_hover[0] = 0xFF303030,
		.color_hover[1] = 0xFF707070, .window = WIN_MAIN};
	menu->buttons[BUT_BACK] = (t_button){.pos = (t_ulpoint){.x = part(w, 0.32),
		.y = part(h, 0.88)}, .dim = (t_ulpoint){.x = part(w, 0.08),
		.y = part(h, 0.08)}, .state = IDLE, .color_idle[0] = 0xFF101010,
		.color_idle[1] = 0xFF505050, .color_hover[0] = 0xFF303030,
		.color_hover[1] = 0xFF707070, .window = WIN_SETTINGS};
	menu->buttons[BUT_EXIT] = (t_button){.pos = (t_ulpoint){.x = part(w, 0.5),
		.y = part(h, 0.7)}, .dim = (t_ulpoint){.x = part(w, 0.2),
		.y = part(h, 0.1)}, .state = IDLE, .color_idle[0] = 0xFF101010,
		.color_idle[1] = 0xFF505050, .color_hover[0] = 0xFF303030,
		.color_hover[1] = 0xFF707070, .window = WIN_MAIN};
	menu->buttons[BUT_YES] = (t_button){.pos = (t_ulpoint){.x = part(w, 0.45),
		.y = part(h, 0.55)}, .dim = (t_ulpoint){.x = part(w, 0.08),
		.y = part(h, 0.08)}, .state = IDLE, .color_idle[0] = 0xFF101010,
		.color_idle[1] = 0xFFff1b1e, .color_hover[0] = 0xFF303030,
		.color_hover[1] = 0xFFff3d40, .window = WIN_EXIT};
	menu->buttons[BUT_NO] = (t_button){.pos = (t_ulpoint){.x = part(w, 0.55),
		.y = part(h, 0.55)}, .dim = (t_ulpoint){.x = part(w, 0.08),
		.y = part(h, 0.08)}, .state = IDLE, .color_idle[0] = 0xFF101010,
		.color_idle[1] = 0xFF505050, .color_hover[0] = 0xFF303030,
		.color_hover[1] = 0xFF707070, .window = WIN_EXIT};
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
	menu->characters.px = NULL;
}

static int	load_menu_images(t_mlx *mlx, t_menu *menu, size_t w, size_t h)
{
	return (load_img(mlx->mlx, "assets/core/menu/title.bmp", &menu->title,
			(t_dim){.w = part(w, 0.2), .h = part(h, 0.15)})
		|| load_img(mlx->mlx, "assets/core/menu/confirm.bmp", &menu->confirm,
			(t_dim){.w = part(w, 0.15), .h = part(h, 0.13)})
		|| load_img(mlx->mlx, "assets/core/menu/resume.bmp", &menu->resume,
			(t_dim){.w = part(w, 0.1), .h = part(h, 0.1)})
		|| load_img(mlx->mlx, "assets/core/menu/start.bmp",
			&menu->buttons[BUT_START].string,
			(t_dim){.w = part(w, 0.1), .h = part(h, 0.1)})
		|| load_img(mlx->mlx, "assets/core/menu/settings.bmp",
			&menu->buttons[BUT_SETTINGS].string,
			(t_dim){.w = part(w, 0.1), .h = part(h, 0.1)})
		|| load_img(mlx->mlx, "assets/core/menu/back.bmp",
			&menu->buttons[BUT_BACK].string,
			(t_dim){.w = part(w, 0.1), .h = part(h, 0.1)})
		|| load_img(mlx->mlx, "assets/core/menu/exit.bmp",
			&menu->buttons[BUT_EXIT].string,
			(t_dim){.w = part(w, 0.1), .h = part(h, 0.1)})
		|| load_img(mlx->mlx, "assets/core/menu/yes.bmp",
			&menu->buttons[BUT_YES].string,
			(t_dim){.w = part(w, 0.1), .h = part(h, 0.1)})
		|| load_img(mlx->mlx, "assets/core/menu/no.bmp",
				&menu->buttons[BUT_NO].string,
			(t_dim){.w = part(w, 0.1), .h = part(h, 0.1)})
		|| load_img(mlx->mlx, "assets/core/characters/characters.bmp",
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
	init_buttons_menu(menu, set->wid, set->hei);
	init_sliders_settings(menu, set, set->wid, set->hei);
	init_textfields_settings(menu, set->wid, set->hei);
	init_menu_images(menu);
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
		free(menu->characters.px);
		return (1);
	}
	menu->window = WIN_MAIN;
	menu->first_render = 1;
	menu->prev_keys = 0;
	menu->first_start = 1;
	return (0);
}
