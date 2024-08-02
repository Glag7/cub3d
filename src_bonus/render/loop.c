/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 19:04:21 by glaguyon          #+#    #+#             */
/*   Updated: 2024/08/02 17:58:17 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "render.h"
#include "mlx.h"
#include "data.h"

#include "point.h"
#include <math.h>

//colors
# define RED 0xFFFF0000
# define ORE 0xFFFF3300
# define ORA 0xFFFF7700
# define YEL 0xFFFFFF00
# define YGR 0xFF77FF00
# define LGR 0xFF11FF00
# define GRE 0xFF00FF00
static void	drawfps(t_mlx *mlx, int fps)//move colors to header
{
	static char	num[16] = "fps:    ";
	static const int	color[9] = {RED, ORE, ORA, YEL, YGR, LGR, GRE, GRE, GRE};
	int		i;

	i = 0;
	if (fps > 999)
		num[i++] = (fps / 1000) % 10 + '0';
	if (fps > 99)
		num[i++] = (fps / 100) % 10 + '0';
	if (fps > 9)
		num[i++] = (fps / 10) % 10 + '0';
	num[i++] = fps % 10 + '0';
	num[i++] = ' ';
	*(unsigned long long *)(num + i) = 0X00737066ULL;//fps\0
	if (fps > 80)
		fps = 80;
	mlx_string_put(mlx->mlx, mlx->win, 0, 10, color[fps / 10], num);
}



double foo(t_data *data, int y)
{
	double la_constante_la = .1;//a choisir avec angle max
	int	yend = data->set.hei / 2 + (int)((double)data->set.wid / (data->set.tanfov * 2.) * data->play.az / M_PI * 4.);//horizon

	yend -= (int)data->set.hei/2;
	double mewhen = (((double)data->set.hei) / (double)data->set.hei) * la_constante_la * data->set.fov;
	return ((2. * (double)y - (double)yend * 2.) / (double)data->set.hei) * la_constante_la * data->set.fov - mewhen;
}//calculer yend a l'angle max, yend a l'angle 0, en deduire la fonction

static void	draw_sky(t_data *data)//le faire dans drawv
{
	int	yend = data->set.hei / 2 + (int)((double)data->set.wid / (data->set.tanfov * 2.) * data->play.az / M_PI * 4.);//horizon
	
	int	x, y;


	yend++;//?
	if (yend >= (int)data->set.hei)
		yend = data->set.hei - 1;
	y = 0;
	while (y <= yend)//?
	{
		double ypx;
		double skibidi2 = 1. / (M_PI);
		//disons que + = vers le haut
		//ypx = (foo(data, y)
		//* skibidi2//repassen prctage
		//+ .0)//offset pour voir le bas
		ypx = foo(data,y) * (double)data->tmp2.w;
		if (ypx < 0)
			ypx += data->tmp2.w;
		x = 0;
		while (x < data->set.wid)
		{//TODO increment plutot que mult
		 //TODO utiliser les angles precalcules a al place de x / fov
			double skibidi = .5 / M_PI;
			double xpx;

			xpx = ((((double)x / (double)data->set.wid - .5)
				* data->set.fov
			- data->play.a) * skibidi
			- .25)
			* (double)data->tmp2.w;
			if (xpx < 0)
				xpx += data->tmp2.w;
//faire des skibidi underflow avec des unsigned pour le &
//TODO faire en sorte que resize la window agrandisse la skybox juste (pas en voir plus)
			
			data->mlx.px[x + y * data->set.wid] =
				data->tmp2.px[(int)floor(xpx)
			+ (int)floor(ypx) % data->tmp2.w * (int)data->tmp2.w];
			++x;
		}
		++y;
	}
}
	
	//TODO deplqcer cqm puis joueur
//dessiner plafond et sol en meme temps ? ou alors skybox
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
