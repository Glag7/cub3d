/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 18:15:50 by glaguyon          #+#    #+#             */
/*   Updated: 2024/09/18 15:16:07 by ttrave           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "mlx.h"
#include "data.h"
#include "menu.h"
#include "popup.h"
#include "status.h"

# define LEFT 1
# define MIDDLE 2
# define RIGHT 3

// pb : si slider presse quand menu ferme avec tab, slider reste quand le menu se reouvre !!
// pb pour les sliders uint qui doivent save dans des doubles (cf fov_deg)
static void	save_new_value(t_slider slider)
{
	double	value;

	value = slider.i_curr * (double)(slider.v_max - slider.v_min) + (double)slider.v_min;
	if (slider.type == UINT)
		*(uint32_t *)slider.dst = (uint32_t)value;
	else if (slider.type == DOUBLE)
		*(double *)slider.dst = value;
}

static void	menu_unmouse_hook(int click, int x, int y, t_data *data)
{
	size_t	i;

	(void)x;
	(void)y;
	if (click != LEFT)
		return ;
	i = 0;
	while (i < NB_SLIDERS)
	{
		if (data->menu.sliders[i].state == PRESS)
		{
			save_new_value(data->menu.sliders[i]);
			data->menu.sliders[i].state = IDLE;
		}
		i++;
	}
}

int	unmouse_hook(int click, int x, int y, void *data_)
{
	t_data	*data;

	data = (t_data *)data_;
	if ((data->status & MENU) != 0)
	{
		menu_unmouse_hook(click, x, y, data);
		return (0);
	}
	return (0);
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
}

static void	update_menu(t_data *data, size_t i)
{
	if (i == BUT_START)
	{
		mlx_mouse_hide(data->mlx.mlx, data->mlx.win);
		mlx_mouse_move(data->mlx.mlx, data->mlx.win, data->set.wid / 2, data->set.hei / 2);
		;// pb angles
		if (data->menu.first_start == 1)
		{
			free(data->menu.buttons[BUT_START].string.px);
			data->menu.buttons[BUT_START].string = data->menu.resume;
		}
		data->menu.first_start = 0;
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
	if (data->menu.window == WIN_SETTINGS)
		update_settings(data, x, y);
	i = 0;
	while (i < NB_BUTTONS)
	{
		if (data->menu.buttons[i].window == data->menu.window
			&& check_hitbox(data->menu.buttons[i].pos,
				data->menu.buttons[i].dim, (size_t)x, (size_t)y) == 1)
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
	if ((data->status & MENU) != 0)
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
