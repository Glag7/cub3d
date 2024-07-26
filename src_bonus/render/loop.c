/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 19:04:21 by glaguyon          #+#    #+#             */
/*   Updated: 2024/07/26 18:42:13 by glag             ###   ########.fr       */
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
	static int	color[9] = {RED, ORE, ORA, YEL, YGR, LGR, GRE, GRE, GRE};
	int		i;

	i = 0;
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

//fusionner a raycast
static void	draw_floor(t_data *data)
{
	int	y;
	int	ystart = data->set.hei / 2 + (int)((double)data->set.wid / (data->set.tanfov * 2.) * data->play.az / M_PI * 4.);//horizon
	double	camheipx = (int)(data->play.z + .5) * data->set.hei;

	t_point	start;//ystart
	t_point	end;//end point
	t_point	inc;

	start.x = data->play.cosa - data->set.tanfov * data->play.sina;
	start.y = data->play.sina + data->set.tanfov * data->play.cosa;
	end.x = data->play.cosa + data->set.tanfov * data->play.sina;
	end.y = data->play.sina - data->set.tanfov * data->play.cosa;
	//si y < 0 ajouter un offset qq part ?
	if (ystart < 0)
		ystart = 0;
	y = ystart;

	t_point	cur;

	while (y < (int)data->set.hei)
	{
		double	dist;

		dist = camheipx / (double)(y - ystart);
		inc = (t_point){(end.x - start.x) / (double)(data->set.wid - 1),
			(end.y - start.y) / (double)(data->set.wid - 1)};
		inc.x *= dist;
		inc.y *= dist;
		cur.x = data->play.x + dist * inc.x;
		cur.y = data->play.y + dist * inc.y;
		for (int x = 0; x < data->set.wid; ++x)
		{
			t_point	tex;

			tex.x = data->tmp.size * (cur.x - floor(cur.x));
			tex.y = data->tmp.size * (cur.y - floor(cur.y));
			cur.x += inc.x;
			cur.y += inc.y;
			data->mlx.px[x + y * data->set.wid] =
				data->tmp.px[(int)floor(tex.x) + (int)(floor(tex.y) * data->tmp.size)];
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
