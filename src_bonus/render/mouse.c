/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glag <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 13:09:07 by glag              #+#    #+#             */
/*   Updated: 2024/08/03 16:42:58 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"
#include "mlx.h"
#include "set.h"

//utiliser rqtio ecrqn ici
void	move_angle(t_data *data, double delta)
{
	int	posx;
	int	posy;

	mlx_mouse_get_pos(data->mlx.mlx, data->mlx.win, &posx, &posy);
	//printf("%d %d\n", posx, posy);
	data->play.a -= ((double)posx - (double)data->oldmouse.x)
		* data->set.sensi * 0.01 * data->set.fov;
	data->play.az -= ((double)posy - (double)data->oldmouse.y)
		* data->set.sensi * 0.01 * (double)data->set.wid/(double)data->set.hei * data->set.fov;
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
