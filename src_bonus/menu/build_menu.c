/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_menu.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrave <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 11:58:59 by ttrave            #+#    #+#             */
/*   Updated: 2024/09/18 16:47:54 by ttrave           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "mlx.h"
#include "data.h"
#include "menu.h"
#include "status.h"
#include "popup.h"

static void	save_settings(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < NB_SETTINGS)
	{
		if (data->menu.sliders[i].state == PRESS)
		{
			if (data->menu.sliders[i].type == UINT)
				*(uint32_t *)data->menu.sliders[i].dst = (uint32_t)data->menu.sliders[i].v_curr;
			else if (data->menu.sliders[i].type == DOUBLE)
				*(double *)data->menu.sliders[i].dst = data->menu.sliders[i].v_curr;
			data->menu.sliders[i].state = IDLE;
			break ;
		}
		i++;
	}
	i = 0;
	while (i < NB_SETTINGS)
	{
		data->menu.sliders[i].state = IDLE;
		i++;
	}
}

void	close_menu(t_data *data)
{
	if (data->menu.window == WIN_SETTINGS)
		save_settings(data);
	mlx_mouse_hide(data->mlx.mlx, data->mlx.win);
	mlx_mouse_move(data->mlx.mlx, data->mlx.win,
		data->menu.save_mouse.x, data->menu.save_mouse.y);
	if (data->menu.first_start == 1)
	{
		free(data->menu.buttons[BUT_START].string.px);
		data->menu.buttons[BUT_START].string = data->menu.resume;
		data->menu.first_start = 0;
	}
	data->status &= ~MENU;
}

void	build_menu(t_data *data)
{
	int	x;
	int	y;

	data->status |= MENU;
	mlx_mouse_get_pos(data->mlx.mlx, data->mlx.win, &x, &y);
	data->menu.save_mouse.x = x;
	data->menu.save_mouse.y = y;
	mlx_mouse_move(data->mlx.mlx, data->mlx.win,
		data->set.wid / 2, data->set.hei / 2);
	mlx_mouse_show(data->mlx.mlx, data->mlx.win);
	save_background(data);
	draw_main_menu(data);
}
