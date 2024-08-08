/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   win.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 17:04:47 by glaguyon          #+#    #+#             */
/*   Updated: 2024/08/08 17:17:52 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "data.h"
#include "img.h"
#include "status.h"

int	win_hook(void *data_)
{
	t_data	*data;

	data = data_;
	mlx_loop_end(data->mlx.mlx);
	return (0);
}

int	in_hook(void *data_)
{
	t_data	*data;

	data = data_;
	data->status |= INWINDOW;
	mlx_mouse_hide(data->mlx.mlx, data->mlx.win);
	mlx_mouse_move(data->mlx.mlx, data->mlx.win, data->set.wid / 2,
		data->set.hei / 2);
	data->oldmouse.x = data->set.wid / 2;
	data->oldmouse.y = data->set.hei / 2;
	return (0);
}

int	out_hook(void *data_)
{
	t_data	*data;

	data = data_;
	mlx_mouse_show(data->mlx.mlx, data->mlx.win);
	data->status &= ~INWINDOW;
	return (0);
}
