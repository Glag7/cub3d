/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 18:15:50 by glaguyon          #+#    #+#             */
/*   Updated: 2024/09/08 18:37:38 by ttrave           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "data.h"
#include "menu.h"
#include "popup.h"
#include "status.h"

# define LEFT 1
# define MIDDLE 2
# define RIGHT 3

static void	update_menu(t_data *data, size_t i)
{
	if (i == BUT_START || i == BUT_RESUME)
	{
		mlx_mouse_hide(data->mlx.mlx, data->mlx.win);
		mlx_mouse_move(data->mlx.mlx, data->mlx.win, data->set.wid / 2, data->set.hei / 2);
		;// mettre mouse pos dans structure au milieu ?
		data->menu.resume = 1;
		data->status &= ~MENU;
	}
	else if (i == BUT_SETTINGS)
		draw_settings_menu(data);
	else if (i == BUT_BACK || i == BUT_NO)
		draw_main_menu(data);
	else if (i == BUT_EXIT)
		draw_exit_menu(data);
	else if (i == BUT_YES)
		mlx_loop_end(data->mlx.mlx);
}

static void	menu_mouse_hook(int click, int x, int y, t_data *data)
{
	size_t		i;

	if (click != LEFT)
		return ;
	i = 0;
	while (i < 7)
	{
		if (data->menu.buttons[i].window == data->menu.window
			&& check_button_hitbox(data->menu.buttons[i], (size_t)x, (size_t)y) == 1)
		{
			update_menu(data, i);
			break ;
		}
		i++;
	}
}

int	mouse_hook(int click, int x, int y, void *data_)
{
	t_data	*data;

	data = data_;
	if (data->status == MENU)
	{
		menu_mouse_hook(click, x, y, data);
		return (0);
	}
	if (click == LEFT)
	{
		data->lastshot = 0.;
		data->shooting = 1;
	}
	return (0);
}
