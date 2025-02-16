/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 19:04:21 by glaguyon          #+#    #+#             */
/*   Updated: 2024/09/21 18:59:37 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include "render.h"
#include "move.h"
#include "mlx.h"
#include "data.h"
#include "fps.h"
#include "status.h"
#include "menu.h"
#include "keys.h"

static void	drawdata(t_mlx *mlx, t_play *play, int fps)
{
	static char	speed[4096];
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
	sprintf(speed, "%.3f m/s", sqrt(play->vx * play->vx + play->vy * play->vy));
	mlx_string_put(mlx->mlx, mlx->win, 0, 10, color[fps / 10], num);
	mlx_string_put(mlx->mlx, mlx->win, 0, 20, color[fps / 10], speed);
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
	if (!(data->status & INWINDOW))
		return ;
	manage_menu_hooks(data);
	if ((data->status & MENU) != 0)
	{
		compute_values(data);
		manage_menu(data);
		return ;
	}
	move_angle(data, delta, data->keys);
	move(data, delta, data->keys);
	open_door(data, delta);
	shoot(data, delta);
	data->cross = NULL;
	open_doors(data, delta);
	compute_values(data);
	draw_floor(data);
	raycast(data);
	draw_minimap(data);
	draw_hud(data);
	data->lastshot += delta;
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
		oldfps = fps;
		fps = 0;
	}
	drawdata(&data->mlx, &data->play, oldfps);
	++fps;
	return (0);
}
