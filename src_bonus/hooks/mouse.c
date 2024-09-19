/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 18:15:50 by glaguyon          #+#    #+#             */
/*   Updated: 2024/09/18 19:33:02 by ttrave           ###   ########.fr       */
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

// pb : si slider presse quand menu ferme avec tab, slider reste quand le menu se reouvre !!
// -> morceler cette fonction pour appeler save_sliders quand window == SETTINGS et le menu se ferme ?
// pb pour les sliders uint qui doivent save dans des doubles (cf fov_deg)
static void	menu_unmouse_hook(int click, int x, int y, t_data *data)
{
	size_t	i;

	(void)x;
	(void)y;
	if (click != LEFT)
		return ;
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
	while (i < NB_SETTINGS)
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
		close_menu(data);
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
