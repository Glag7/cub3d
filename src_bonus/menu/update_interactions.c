/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_interactions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrave <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 18:15:50 by ttrave            #+#    #+#             */
/*   Updated: 2024/09/22 15:27:02 by ttrave           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "mlx.h"
#include "data.h"
#include "menu.h"
#include "utils.h"

void	menu_unmouse_hook(int x, int y, t_data *data)
{
	(void)x;
	(void)y;
	if (data->menu.window == WIN_SETTINGS)
		save_sliders(data);
}

static void	update_settings_textfields(t_data *data, size_t x, size_t y)
{
	size_t	i;

	i = 0;
	while (i < NB_TEXTFIELDS)
	{
		if (check_hitbox(data->menu.textfields[i].pos,
				data->menu.textfields[i].dim, x, y) == 1)
		{
			data->menu.textfields[i].state = PRESS;
			ft_bzero(data->menu.textfields[i].buffer, TEXTFIELD_LEN + 1);
		}
		else if (data->menu.textfields[i].state == PRESS)
		{
			data->menu.textfields[i].state = IDLE;
			save_textfield(data, &data->menu.textfields[i]);
			if (i < NB_SLIDERS)
				draw_slider(data, data->menu.sliders[i]);
		}
		i++;
	}
}

static void	update_settings(t_data *data, int x, int y)
{
	size_t	i;

	i = 0;
	while (i < NB_SLIDERS)
	{
		if (check_hitbox(data->menu.sliders[i].pos, data->menu.sliders[i].dim,
				(size_t)x, (size_t)y) == 1)
		{
			data->menu.sliders[i].state = PRESS;
			break ;
		}
		i++;
	}
	update_settings_textfields(data, (size_t)x, (size_t)y);
}

void	menu_mouse_hook(int x, int y, t_data *data)
{
	size_t	i;

	if (data->menu.window == WIN_SETTINGS)
		update_settings(data, x, y);
	i = 0;
	while (i < NB_BUTTONS)
	{
		if (data->menu.buttons[i].window == data->menu.window
			&& check_hitbox(data->menu.buttons[i].pos,
				data->menu.buttons[i].dim, (size_t)x, (size_t)y) == 1)
		{
			if (i == BUT_START)
				close_menu(data);
			else if (i == BUT_SETTINGS)
				draw_settings_menu(data);
			else if (i == BUT_BACK || i == BUT_NO)
				draw_main_menu(data);
			else if (i == BUT_EXIT)
				draw_exit_menu(data);
			else if (i == BUT_YES)
				mlx_loop_end(data->mlx.mlx);
			break ;
		}
		i++;
	}
}
