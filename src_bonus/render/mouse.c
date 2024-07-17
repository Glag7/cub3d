/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glag <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 13:09:07 by glag              #+#    #+#             */
/*   Updated: 2024/07/17 13:18:44 by glag             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"
#include "mlx.h"
#include "set.h"

void	move_angle(t_data *data, double delta)
{
	int	posx;
	int	posy;

	mlx_mouse_get_pos(data->mlx.mlx, data->mlx.win, &posx, &posy);
	data->play.a -= ((double)posx - (double)data->oldmouse.x) * delta
		* data->set.sensi;
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
		data->oldmouse.x = (long long)posx;
		data->oldmouse.y = (long long)posy;
	}
}
