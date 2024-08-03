/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 19:04:21 by glaguyon          #+#    #+#             */
/*   Updated: 2024/08/03 18:41:13 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "render.h"
#include "mlx.h"
#include "data.h"
#include "fps.h"

#include "point.h"
#include <math.h>

double foo(t_data *data, int y)
{
	/*int	yend = data->set.hei / 2 + (int)((double)data->set.wid / (data->set.tanfov * 2.) * data->play.az / M_PI * 4.);//horizon

	yend -= (int)data->set.hei/2;
	
	
	double mid = (((double)data->set.hei - (double)yend * 2.) / (double)data->set.hei);
	double res = ((2. * (double)y - (double)yend * 2.) / (double)data->set.hei);
	if (y == 0)
		printf("%f\n", mid);
	return  mid + (res - mid) * data->set.fov;*/

/*	
	static double max_az = M_PI * .5 + 150. * M_PI / 180. * .5;//max fov / 2
	return (-data->play.az / max_az //milieu
		+ ((double)y /(double)data->set.hei - .5) //pourcentage fov
		* data->set.fov / max_az);*/
/*
	static double max_az = M_PI * .5;
	static double max_fov = 150. * M_PI / 180.;
	static double min_fov = 10. * M_PI / 180.;
	double yend_max = (double)data->set.hei / 2. + ((double)data->set.wid / (tan(max_fov * .5) * 2.) * max_az / M_PI * 4.);
	double yend_min = (double)data->set.hei / 2. + ((double)data->set.wid / (tan(min_fov * .5) * 2.) * max_az / M_PI * 4.);
	double yend_cur = (double)data->set.hei / 2. + ((double)data->set.wid / (data->set.tanfov * 2.) * max_az / M_PI * 4.);
	double yend = (double)data->set.hei / 2. + ((double)data->set.wid / (data->set.tanfov * 2.) * data->play.az / M_PI * 4.);

	//printf("%d %f\n", yend, yend_max);
	//printf("%f %f\n", max_fov, max_az);//il faut soustraire la diff avec le fov max
	return ((y - yend) / yend_cur);*/
}

static void	draw_sky(t_data *data)//le faire dans drawv
{
	int	yend = data->set.hei / 2 + (int)((double)data->set.wid / (data->set.tanfov * 2.) * data->play.az / M_PI * 4.);//horizon
	
	int	x, y;


	yend++;//?
	if (yend > (int)data->set.hei)
		yend = data->set.hei;
	y = 0;
	while (y < yend)
	{
			double skibidi = .5 / M_PI;
		double ypx;
		//disons que + = vers le haut
		//ypx = (foo(data, y)
		//* skibidi2//repassen prctage
		//+ .0)//offset pour voir le bas
		//ypx = foo(data,y) * (double)data->tmp2.w;
			ypx = ((((double)y / (double)data->set.hei - .5)
				* data->set.fov * (double)data->set.hei/(double)data->set.wid
			- data->play.az) * skibidi
			- .25)
			* (double)data->tmp2.w;
		x = 0;
		while (x < data->set.wid)
		{//TODO increment plutot que mult
		 //TODO utiliser les angles precalcules a al place de x / fov
			double xpx;

			xpx = ((((double)x / (double)data->set.wid - .5)
				* data->set.fov
			- data->play.a) * skibidi
			- .25)
			* (double)data->tmp2.w;
//faire des skibidi underflow avec des unsigned pour le &
//TODO faire en sorte que resize la window agrandisse la skybox juste (pas en voir plus)
			
			data->mlx.px[x + y * data->set.wid] =
				data->tmp2.px[((int)floor(xpx) & (data->tmp2.w - 1))
			+ ((int)floor(ypx) & (data->tmp2.h - 1)) * (int)data->tmp2.w];
			++x;
		}
		++y;
	}
}

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
	static struct timespec	old = {0, 0};
	struct timespec			curr;
	double					delta;
	t_data					*data;

	data = data_;
	clock_gettime(CLOCK_MONOTONIC_RAW, &curr);
	delta = curr.tv_sec - old.tv_sec + (curr.tv_nsec - old.tv_nsec) * 1.e-9;
	move_angle(data, delta);
	move(data, delta, data->keys);
	data->horizon = data->set.hei / 2 + (int)(data->set.planwid * data->play.az / M_PI * 4.);
	draw_floor(data);
	draw_sky(data);
	raycast(data);
	draw_minimap(data);
	data->mlx.px[data->set.wid * (data->set.hei + 1) / 2] = 0x00FF0000;//bad crosshair
	data->mlx.px[data->set.wid * (data->set.hei + 1) / 2 + 1] = 0x00FF0000;
	data->mlx.px[data->set.wid * (data->set.hei + 1) / 2 + data->set.wid] = 0x00FF0000;
	data->mlx.px[data->set.wid * (data->set.hei + 1) / 2 + data->set.wid + 1] = 0x00FF0000;
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->mlx.img, 0, 0);
	if (old.tv_sec < curr.tv_sec)
	{
		printf("fps: %d\nangle %f\nfov %f\nz %f\n---\n",
			fps, data->play.az, data->set.fov_deg, data->play.z);
		oldfps = fps;
		fps = 0;
	}
	drawfps(&data->mlx, oldfps);
	++fps;
	//printf("angle:%f\n", data->play.az * 180. / 3.14);
	old = curr;
	return (0);
}
