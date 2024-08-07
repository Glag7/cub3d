/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 19:04:21 by glaguyon          #+#    #+#             */
/*   Updated: 2024/08/07 12:56:06 by glaguyon         ###   ########.fr       */
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

static void	drawfps(t_mlx *mlx, int fps)
{
	static char			num[16] = "fps:    ";
	static const int	color[9] = {RED, ORE, ORA, YEL, YGR, LGR, GRE, GRE, GRE};
	int					i;

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
	
//TODO deplacer cam puis jouer
//clarfier la pipeline
int	loop(void *data_)
{
	static int				fps = 0;
	static int				oldfps = 0;
	static double				avgfps = 0.;
	static int				n = 0;;
	static struct timespec	old = {0, 0};
	struct timespec			curr;
	double					delta;
	t_data					*data;

	data = data_;
	clock_gettime(CLOCK_MONOTONIC_RAW, &curr);
	delta = curr.tv_sec - old.tv_sec + (curr.tv_nsec - old.tv_nsec) * 1.e-9;
	move_angle(data, delta, data->keys);
	move(data, delta, data->keys);
	
	data->horizon = data->set.hei / 2 + (int)(data->set.planwid * data->play.az / M_PI * 4.);
	int	yend = data->horizon + 1;
	if (yend > (int)data->set.hei)
		yend = data->set.hei;
	double yend_cur = 1. / ((double)data->set.hei / 2. + ((double)data->set.wid / (data->set.tanfov * 2.) * MAX_ANGLE / M_PI * 4.));
	data->px.x = (((-.5 * data->set.fov - data->play.a) * (.5 / M_PI) - .25) + 1.) * (double)data->map.c.w;
	data->px.y = ((double)(-data->horizon) * yend_cur + 1.) * (double)data->map.c.h;
	data->pxinc.x = (((1. / (double)data->set.wid) * data->set.fov) * (.5 / M_PI)) * (double)data->map.c.w;
	data->pxinc.y = (double)(1.) * yend_cur * (double)data->map.c.h;
	draw_floor(data);
	raycast(data);
	draw_minimap(data);
	data->mlx.px[data->set.wid * (data->set.hei + 1) / 2] = 0x00FF0000;//bad crosshair
	data->mlx.px[data->set.wid * (data->set.hei + 1) / 2 + 1] = 0x00FF0000;
	data->mlx.px[data->set.wid * (data->set.hei + 1) / 2 + data->set.wid] = 0x00FF0000;
	data->mlx.px[data->set.wid * (data->set.hei + 1) / 2 + data->set.wid + 1] = 0x00FF0000;
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->mlx.img, 0, 0);
	if (old.tv_sec < curr.tv_sec)
	{
		avgfps = (avgfps * n + fps) / (n + 1);
		++n;
		printf("fps: %d\navg: %f\nangle %f\nfov %f\nz %f\n---\n",
			fps, avgfps, data->play.az, data->set.fov_deg, data->play.z);
		oldfps = fps;
		fps = 0;
	}
	drawfps(&data->mlx, oldfps);
	++fps;
	//printf("angle:%f\n", data->play.az * 180. / 3.14);
	old = curr;
	return (0);
}
