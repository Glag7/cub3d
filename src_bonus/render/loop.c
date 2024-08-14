/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 19:04:21 by glaguyon          #+#    #+#             */
/*   Updated: 2024/08/14 16:59:48 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "render.h"
#include "move.h"
#include "mlx.h"
#include "data.h"
#include "fps.h"
#include "status.h"

static void	drawfps(t_mlx *mlx, int fps)
{
	static char	num[16] = "fps:    ";
	static int	color[9] = {RED, ORE, ORA, YEL, YGR, LGR, GRE, GRE, GRE};
	int			i;

	i = 0;
	if (fps > 999)
		num[i++] = (fps / 1000) % 10 + '0';
	if (fps > 99)
		num[i++] = (fps / 100) % 10 + '0';
	if (fps > 9)
		num[i++] = (fps / 10) % 10 + '0';
	num[i++] = fps % 10 + '0';
	num[i++] = ' ';
	*(unsigned long long *)(num + i) = FPS;
	if (fps > 80)
		fps = 80;
	mlx_string_put(mlx->mlx, mlx->win, 0, 10, color[fps / 10], num);
}

static void	compute_values(t_data *data)
{
	double	yend_cur;

	data->horizon = data->set.hei / 2 + (int)(data->set.planwid
			* data->play.az / M_PI * 4.);
	yend_cur = 1. / ((double)data->set.hei / 2. + ((double)data->set.wid
				/ (data->set.tanfov * 2.) * MAX_ANGLE / M_PI * 4.));
	data->px.x = (((-.5 * data->set.fov - data->play.a)
				* (.5 / M_PI) - .25) + 1.) * (double)data->map.c.w;
	data->px.y = ((double)(-data->horizon) * yend_cur + 1.)
		* (double)data->map.c.h;
	data->pxinc.x = (((1. / (double)data->set.wid) * data->set.fov)
			* (.5 / M_PI)) * (double)data->map.c.w;
	data->pxinc.y = 1. * yend_cur *(double)data->map.c.h;
}

static double	get_delta(int *newsec)
{
	static struct timespec	old = {0, 0};
	struct timespec			curr;
	double					delta;

	clock_gettime(CLOCK_MONOTONIC_RAW, &curr);
	delta = curr.tv_sec - old.tv_sec + (curr.tv_nsec - old.tv_nsec) * 1.e-9;
	if (delta > 1.)
		delta = 1.;
	*newsec = (old.tv_sec < curr.tv_sec);
	old = curr;
	return (delta);
}

static void	manage_game(t_data *data, double delta)
{
	if (data->status & INWINDOW)
	{
		move_angle(data, delta, data->keys);
		move(data, delta, data->keys);
		compute_values(data);
		draw_floor(data);
		raycast(data);
		draw_minimap(data);
		data->mlx.px[data->set.hei / 2 * data->set.wid + data->set.wid / 2] = 0xFFFF0000;
		data->mlx.px[data->set.hei / 2 * data->set.wid + data->set.wid / 2 + 1] = 0xFFFF0000;
		data->mlx.px[data->set.hei / 2 * data->set.wid + data->set.wid + data->set.wid / 2] = 0xFFFF0000;
		data->mlx.px[data->set.hei / 2 * data->set.wid + data->set.wid + data->set.wid / 2 + 1] = 0xFFFF0000;
	}
}

int	loop(void *data_)
{
	static int	fps = 0;
	static int	oldfps = 0;
	int			newsec;
	double		delta;
	t_data		*data;

	data = data_;
	delta = get_delta(&newsec);
	manage_game(data, delta);
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->mlx.img, 0, 0);
	if (newsec)
	{
		printf("fps: %d\nangle %f\nfov %f\nz %f\n---\n",
			fps, data->play.az, data->set.fov_deg, data->play.z);
		oldfps = fps;
		fps = 0;
	}
	drawfps(&data->mlx, oldfps);
	++fps;
	return (0);
}
