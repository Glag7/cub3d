/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 14:40:40 by glaguyon          #+#    #+#             */
/*   Updated: 2024/06/20 19:59:32 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "data.h"
#include "mlx.h"
#include "utils.h"

typedef struct s_point
{
	double	x;
	double	y;
}	t_point;

#define MAXLEN 2.
#define XSIDE 0
#define YSIDE 1
static void	trace_ray(t_map *map, t_mlx *mlx, double a, size_t x)
{
	t_point	pos;
	t_point	vec;
	t_point	dist;
	int		hit;
	int		side;
	double	len;

	hit = 0;
	len = 0.;
	vec = (t_point){cos(a), -sin(a)};
	pos = (t_point){map->player.x, map->player.y};
	if (vec.x < 0)
		dist.x = (pos.x - floor(pos.x)) / -vec.x;
	else
		dist.x = (1.0 - pos.x + floor(pos.x)) / vec.x;
	if (vec.y < 0)
		dist.y = (pos.y - floor(pos.y)) / -vec.y;
	else
		dist.y = (1.0 - pos.y + floor(pos.y)) / vec.y;
	//printf("x: %f\ny: %f\n", vec.x, vec.y);
	//printf("xin: %f\nyin: %f\n", dist.x, dist.y);
	while (!hit && len < MAXLEN)
	{
		if (dist.x < dist.y)
		{
			pos.x += vec.x;
			dist.x += fabs(vec.x);
			side = XSIDE;
		}
		else
		{
			pos.y += vec.y;
			dist.y += fabs(vec.y);
			side = YSIDE;
		}
		if (map->map[map->wid * (size_t)pos.y + (size_t)pos.x])
		{
			mlx->px[x + 2 * DEF_WID] = 0x0000FF00;
			hit = 1 ;
		}
		len = sqrt(pow(pos.x - map->player.x, 2.) + pow(pos.y - map->player.y, 2));
	}
}

static void	raycast(t_map *map, t_mlx *mlx)
{
	double	astep;
	double	a;
	size_t	i;

	i = 0;
	astep = map->player.fov / (double)mlx->wid;
	a = map->player.a - map->player.a * 0.5;
	//trace_ray(map, mlx, map->player.a, 1);/*
	while (i < mlx->wid)
	{
		trace_ray(map, mlx, a, i);
		i++;
		a += astep;
	}
}

int	draw(void *data_)
{
	t_data	*data;

	data = data_;
	//ft_bzero(data->mlx.px, data->mlx.wid * data->mlx.hei);
	raycast(&data->map, &data->mlx);
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->mlx.img, 0, 0);
	return (0);
}
