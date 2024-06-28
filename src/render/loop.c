/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 19:04:21 by glaguyon          #+#    #+#             */
/*   Updated: 2024/06/28 19:06:20 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include "render.h"
#include "mlx.h"
#include "data.h"

int	loop(void *data_)
{
	static int	fps = 0;
	static struct timeval	old = {0, 0};
	struct timeval		curr;
	double			delta;
	t_data	*data;

	data = data_;
	gettimeofday(&curr, 0);
	delta = curr.tv_sec - old.tv_sec + (curr.tv_usec - old.tv_usec) * 1.e-6;
	move(data, delta, data->keys);
	raycast(data);
	draw_minimap(data);
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->mlx.img, 0, 0);
	if (old.tv_sec < curr.tv_sec)
	{
		//printf("fps: %d\n", fps);
		fps = 0;
	}
	++fps;
	old = curr;
	return (0);
}
