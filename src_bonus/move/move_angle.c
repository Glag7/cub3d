/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_angle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glag <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 13:09:07 by glag              #+#    #+#             */
/*   Updated: 2024/08/08 12:57:56 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "data.h"
#include "mlx.h"
#include "set.h"
#include "keys.h"

static void	move_mouse(t_data *data)
{
	int	posx;
	int	posy;

	mlx_mouse_get_pos(data->mlx.mlx, data->mlx.win, &posx, &posy);
	data->play.a -= ((double)posx - (double)data->oldmouse.x)
		* data->set.sensi * 0.01 * data->set.fov;
	data->play.az -= ((double)posy - (double)data->oldmouse.y)
		* data->set.sensi * 0.01 * (double)data->set.wid
		/ (double)data->set.hei * data->set.fov;
	if ((double)posx >= (double)data->set.wid * 0.9f
		|| (double)posx <= (double)data->set.wid * 0.1
		|| (double)posy >= (double)data->set.hei * 0.9
		|| (double)posy <= (double)data->set.hei * 0.1)
	{
		mlx_mouse_move(data->mlx.mlx, data->mlx.win, data->set.wid / 2,
			data->set.hei / 2);
		data->oldmouse.x = data->set.wid / 2;
		data->oldmouse.y = data->set.hei / 2;
	}
	else
	{
		data->oldmouse.x = posx;
		data->oldmouse.y = posy;
	}
}

void	move_angle(t_data *data, double delta, uint64_t keys)
{
	move_mouse(data);
	if (keys & KEY_LEFT)
		data->play.a += 1. * delta;
	if (keys & KEY_RIGHT)
		data->play.a -= 1. * delta;
	if (keys & KEY_UP)
		data->play.az += 1. * delta;
	if (keys & KEY_DOWN)
		data->play.az -= 1. * delta;
}
