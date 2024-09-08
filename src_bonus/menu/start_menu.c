/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_menu.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrave <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 11:58:59 by ttrave            #+#    #+#             */
/*   Updated: 2024/09/08 18:57:44 by ttrave           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "img.h"
#include "menu.h"
#include "set.h"
#include "popup.h"
#include "mlx.h"
#include "status.h"

void	draw_main_menu(t_data *data)
{
	draw_background(data);
	draw_string(data, (t_ulpoint){.x = part(data->set.wid, 0.5), .y = part(data->set.hei, 0.15)},
		data->menu.title);
	if (data->menu.resume == 0)
		draw_button(data, data->menu.buttons[BUT_START], IDLE);
	else
		draw_button(data, data->menu.buttons[BUT_RESUME], IDLE);
	draw_button(data, data->menu.buttons[BUT_SETTINGS], IDLE);
	draw_button(data, data->menu.buttons[BUT_EXIT], IDLE);
	data->menu.window = WIN_MAIN;
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->mlx.img, 0, 0);
}

void	draw_settings_menu(t_data *data)
{
	uint32_t	colors[2];

	colors[0] = 0x00101010;
	colors[1] = 0x00505050;
	draw_background(data);
	draw_rectangle(data, (t_ulpoint){.x = part(data->set.wid, 0.5), .y = part(data->set.hei, 0.5)},
		(t_ulpoint){.x = part(data->set.wid, 0.5), .y = part(data->set.hei, 0.8)}, colors);
	draw_button(data, data->menu.buttons[BUT_BACK], IDLE);
	;// draw options
	data->menu.window = WIN_SETTINGS;
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->mlx.img, 0, 0);
}

void	draw_exit_menu(t_data *data)
{
	uint32_t	colors[2];

	colors[0] = 0x00101010;
	colors[1] = 0x00505050;
	draw_background(data);
	draw_rectangle(data, (t_ulpoint){.x = part(data->set.wid, 0.5), .y = part(data->set.hei, 0.5)},
		(t_ulpoint){.x = part(data->set.wid, 0.2), .y = part(data->set.hei, 0.25)}, colors);
	draw_string(data, (t_ulpoint){.x = part(data->set.wid, 0.5), .y = part(data->set.hei, 0.45)},
		data->menu.confirm);
	draw_button(data, data->menu.buttons[BUT_YES], IDLE);
	draw_button(data, data->menu.buttons[BUT_NO], IDLE);
	data->menu.window = WIN_EXIT;
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->mlx.img, 0, 0);
}

void	build_menu(t_data *data)
{
	data->status |= MENU;
	mlx_mouse_show(data->mlx.mlx, data->mlx.win);
	save_background(data);
	draw_main_menu(data);
}
