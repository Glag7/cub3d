/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 19:04:21 by glaguyon          #+#    #+#             */
/*   Updated: 2024/08/02 16:27:13 by glaguyon         ###   ########.fr       */
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

//(double)data->set.wid / (data->set.tanfov * 2.) constqnte = wid cub a 1
static void	draw_floor(t_data *data)
{
	int	y;
	int	ystart = data->set.hei / 2 + (int)((double)data->set.wid / (data->set.tanfov * 2.) * data->play.az / M_PI * 4.);//horizon
	double	camheipx = (data->play.z + .5) * (double)data->set.wid / (data->set.tanfov * 2.);

	t_point	start;//ystart
	t_point	end;//end point
	t_point	inc;

	//bords du plan
	start.x = data->play.cosa - data->set.tanfov * data->play.sina;
	start.y = data->play.sina + data->set.tanfov * data->play.cosa;//sus;
	end.x = data->play.cosa + data->set.tanfov * data->play.sina;
	end.y = data->play.sina - data->set.tanfov * data->play.cosa;
	y = ystart;
	if (y < 0)
		y = 0;

	t_point	cur;
	t_point	baseinc;
	baseinc = (t_point){(end.x - start.x) / (double)(data->set.wid - 1),
			(end.y - start.y) / (double)(data->set.wid - 1)};
	while (y < (int)data->set.hei)
	{
		double	dist;

		dist = camheipx / (double)(y - ystart);
		inc = baseinc;
		inc.x *= dist * (double)data->tmp.size;
		inc.y *= -dist * (double)data->tmp.size;
		cur.x = (data->play.x + dist * start.x) * (double)data->tmp.size;
		cur.y = (data->play.y - dist * start.y) * (double)data->tmp.size;
		for (int x = 0; x < data->set.wid; ++x)
		{
			t_ipoint	tex;
			
			tex.x = (int)cur.x % data->tmp.size;
			tex.y = (int)cur.y % data->tmp.size;
			cur.x += inc.x;
			cur.y += inc.y;
			data->mlx.px[x + y * data->set.wid] =
				data->tmp.px[tex.x + tex.y * data->tmp.size];
		}
		++y;
	}
}//probleme passage negatif a verifier apres opti et underflow
//TODO: tout resize a 256 pour pouvoir faire un & au lieu d'un %


double foo(t_data *data, int y)
{
	double la_constante_la = .1;//a choisir avec angle max
	int	yend = data->set.hei / 2 + (int)((double)data->set.wid / (data->set.tanfov * 2.) * data->play.az / M_PI * 4.);//horizon

	yend -= (int)data->set.hei/2;
	double mewhen = (((double)data->set.hei) / (double)data->set.hei) * la_constante_la * data->set.fov;
	return ((2. * (double)y - (double)yend * 2.) / (double)data->set.hei) * la_constante_la * data->set.fov - mewhen;
}//calculer yend a l'angle max, yend a l'angle 0, en deduire la fonction

static void	draw_sky(t_data *data)
{
	int	yend = data->set.hei / 2 + (int)((double)data->set.wid / (data->set.tanfov * 2.) * data->play.az / M_PI * 4.);//horizon
	
	int	x, y;


	yend++;//?
	if (yend >= (int)data->set.hei)
		yend = data->set.hei - 1;
	y = 0;
	while (y < yend)
	{
		double ypx;
		double skibidi2 = 1. / (M_PI);
		//disons que + = vers le haut
		//ypx = (foo(data, y)
		//* skibidi2//repassen prctage
		//+ .0)//offset pour voir le bas
		ypx = foo(data,y) * (double)data->tmp2.size;
		if (ypx < 0)
			ypx += data->tmp2.size;
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
			* (double)data->tmp2.size;
			if (xpx < 0)
				xpx += data->tmp2.size;
//faire des skibidi underflow avec des unsigned pour le &
//TODO faire en sorte que resize la window agrandisse la skybox juste (pas en voir plus)
			
			data->mlx.px[x + y * data->set.wid] =
				data->tmp2.px[(int)floor(xpx)
			+ (int)floor(ypx) % data->tmp2.size * (int)data->tmp2.size];
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
