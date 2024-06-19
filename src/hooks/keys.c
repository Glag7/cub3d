/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 15:19:12 by glaguyon          #+#    #+#             */
/*   Updated: 2024/06/19 17:29:54 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <X11/Xutil.h>
#include <math.h>
#include "mlx.h"
#include "data.h"
#include "img.h"

int	key_hook(int key, void *data_)
{
	t_data	*data;

	data = data_;
	if (key == XK_Escape)
		mlx_loop_end(data->mlx.mlx);
	else if (key == XK_w)
	{
		data->map.player.y -= cos(data->map.player.a);
		data->map.player.x -= sin(data->map.player.a);
	}
	else if (key == XK_s)
	{
		data->map.player.y += cos(data->map.player.a);
		data->map.player.x += sin(data->map.player.a);
	}
	else if (key == XK_a)
	{
		data->map.player.y -= sin(data->map.player.a);
		data->map.player.x -= cos(data->map.player.a);
	}
	else if (key == XK_d)
	{
		data->map.player.y += sin(data->map.player.a);
		data->map.player.x += cos(data->map.player.a);
	}
	else if (key == XK_Left)
		data->map.player.a += .1;
	else if (key == XK_Right)
		data->map.player.a -= .1;
	return (0);
}
