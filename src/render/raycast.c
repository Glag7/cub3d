/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 14:40:40 by glaguyon          #+#    #+#             */
/*   Updated: 2024/06/28 18:56:54 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "data.h"
#include "render.h"
#include "map.h"
#include "mlx.h"
#include "utils.h"

typedef struct s_point
{
	double	x;
	double	y;
}	t_point;

typedef struct s_ipoint
{
	long long	x;
	long long	y;
}	t_ipoint;

#define XSIDE 0
#define YSIDE 1

#define CENTER .95
#define SIDE 1.05

static void	trace_ray(t_data *data, double a, size_t x)
{
	t_point	pos;//pos du rayon au debut
	t_point	vec;//direction
	t_point	step;//longueur de la diagonale quand on avance sur x ou y
	t_point	dist;//longueur du rayon en x et y
	t_ipoint	ipos;//pos dans la map
	t_ipoint	istep;//ou aller dans la map
	int		hit;//hit
	int		side;//EW/NS
	double	len;//len

	pos = (t_point){data->play.x, data->play.y};
	ipos = (t_ipoint){pos.x, pos.y};
	vec = (t_point){cos(a), -sin(a)};
	step = (t_point){sqrt(1. + (vec.y * vec.y) / (vec.x * vec.x)), sqrt(1. + (vec.x * vec.x) / (vec.y * vec.y))};

	if (vec.x < 0.)
	{
		istep.x = -1;
		dist.x = (pos.x - floor(pos.x)) * step.x;//quelle longueur le rayon aura au premier x
	}
	else
	{
		istep.x = 1;
		dist.x = (1.0 - pos.x + floor(pos.x)) * step.x;
	}
	if (vec.y < 0.)
	{
		istep.y = -1;
		dist.y = (pos.y - floor(pos.y)) * step.y;
	}
	else
	{
		istep.y = 1;
		dist.y = (1.0 - pos.y + floor(pos.y)) * step.y;
	}
	hit = 0;
	len = 0.;
	while (!hit && len < data->set.view)
	{
		if (dist.x < dist.y)
		{
			ipos.x += istep.x;
			len = dist.x;
			dist.x += step.x;
			side = XSIDE;
		}
		else
		{
			ipos.y += istep.y;
			len = dist.y;
			dist.y += step.y;
			side = YSIDE;
		}
		if (ipos.x < 0)
			ipos.x += data->map.wid;
		else if (ipos.x >= data->map.wid)
			ipos.x -= data->map.wid;
		if (ipos.y < 0)
			ipos.y += data->map.hei;
		else if (ipos.y >= data->map.hei)
			ipos.y -= data->map.hei;
		if (len < data->set.view && data->map.map[data->map.wid * ipos.y + ipos.x])
			hit = 1 ;

	}
	pos.x += len * vec.x;//y ?
	pos.y += len * vec.y;
	//len /= 1. - sin((double)x * M_PI / (double)data->set.wid) * 0.15;//a peu pres pareil
	//len /= 4. * (SIDE - CENTER) / ((double)data->set.wid * (double)data->set.wid) * ((double)x - (double)data->set.wid / 2.) * ((double)x - (double)data->set.wid / 2.) + CENTER;
	t_img		img;
	unsigned int	offset;
	if (!hit)
		len = INFINITY;
	if (side == XSIDE && vec.x > 0)
	{
		img = data->map.e;
		offset = (unsigned int)((pos.y - floor(pos.y)) * (double)img.size);
	}
	else if (side == XSIDE)
	{
		img = data->map.w;
		offset = (unsigned int)((1. - (pos.y - floor(pos.y)))* (double)img.size);
	}
	else if (vec.y > 0)
	{
		img = data->map.s;
		offset = (unsigned int)((1. - (pos.x - floor(pos.x))) * (double)img.size);
	}
	else
	{
		img = data->map.n;
		offset = (unsigned int)((pos.x - floor(pos.x)) * (double)img.size);
	}
	//si pas de hit mettre du bleu brouillard ?
	drawv(data, img, x, offset, ((double)data->set.hei / len));
}

static void	raycast(t_data *data)
{
	double	astep;
	double	a;
	size_t	i;

	i = data->set.offthread;
	astep = data->set.fov * (double)data->set.nthread / (double)data->set.wid;
	a = data->play.a + data->set.fov * 0.5;
	while (i < data->set.wid)
	{
		trace_ray(data, a, i);
		i += data->set.nthread;
		a -= astep;
	}
}

#include <sys/time.h>

int	draw(void *data_)
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
