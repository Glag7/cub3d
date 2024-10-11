/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_menu.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrave <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 11:58:59 by ttrave            #+#    #+#             */
/*   Updated: 2024/09/21 19:02:48 by ttrave           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "data.h"
#include "menu.h"
#include "status.h"

void	close_menu(t_data *data)
{
	if (data->menu.window == WIN_SETTINGS)
	{
		save_sliders(data);
		save_textfields(data);
	}
	mlx_mouse_hide(data->mlx.mlx, data->mlx.win);
	mlx_mouse_move(data->mlx.mlx, data->mlx.win,
		data->menu.save_mouse.x, data->menu.save_mouse.y);
	if (data->menu.first_start == 1)
	{
		data->menu.buttons[BUT_START].string.str = "Resume";
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
