/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 14:40:40 by glaguyon          #+#    #+#             */
/*   Updated: 2024/08/16 17:46:41 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "data.h"
#include "render.h"
#include "map.h"
#include "mlx.h"
#include "utils.h"
#include "point.h"
#include "ray.h"

void	init_ray(t_ray *ray)
{
	ray->step = (t_point){sqrt(1. + (ray->vec.y * ray->vec.y)
			/ (ray->vec.x * ray->vec.x)), sqrt(1. + (ray->vec.x
				* ray->vec.x) / (ray->vec.y * ray->vec.y))};
	if (ray->vec.x < 0.)
	{
		ray->istep.x = -1;
		ray->dist.x = (ray->pos.x - floor(ray->pos.x)) * ray->step.x;
	}
	else
	{
		ray->istep.x = 1;
		ray->dist.x = (1.0 - ray->pos.x + floor(ray->pos.x)) * ray->step.x;
	}
	if (ray->vec.y < 0.)
	{
		ray->istep.y = -1;
		ray->dist.y = (ray->pos.y - floor(ray->pos.y)) * ray->step.y;
	}
	else
	{
		ray->istep.y = 1;
		ray->dist.y = (1.0 - ray->pos.y + floor(ray->pos.y)) * ray->step.y;
	}
	ray->hit = 0;
	ray->len = 0.;
}

static inline void __attribute__((always_inline))
	cast_ray(t_ray *ray, t_data *data)
{
	while (!(ray->hit & CUBE) && ray->len < data->set.view)
	{
		ray->side = !(ray->dist.x < ray->dist.y) * YSIDE;
		if (ray->side == XSIDE)
		{
			ray->ipos.x += ray->istep.x;
			ray->len = ray->dist.x;
			ray->dist.x += ray->step.x;
		}
		else
		{
			ray->ipos.y += ray->istep.y;
			ray->len = ray->dist.y;
			ray->dist.y += ray->step.y;
		}
		if (ray->ipos.x < 0)
			ray->ipos.x += data->map.wid;
		else if (ray->ipos.x >= data->map.wid)
			ray->ipos.x -= data->map.wid;
		if (ray->ipos.y < 0)
			ray->ipos.y += data->map.hei;
		else if (ray->ipos.y >= data->map.hei)
			ray->ipos.y -= data->map.hei;
		ray->hit |= data->map.map[data->map.wid * ray->ipos.y + ray->ipos.x];
	}
}

static void	trace_ray(t_data *data, double px, double py, size_t x)
{
	t_ray	ray;

	ray.pos = (t_point){data->play.x, data->play.y};
	ray.ipos = (t_ipoint){ray.pos.x, ray.pos.y};
	ray.vec = (t_point){px, -py};
	init_ray(&ray);
	ray.hit = data->map.map[(int)data->play.x
		+ (int)data->play.y * data->map.wid] & SPEC;
	cast_ray(&ray, data);
	ray.pos.x += ray.len * ray.vec.x;
	ray.pos.y += ray.len * ray.vec.y;
	if (ray.hit & SPEC)
		draw_flat(data, &ray, x);
	else
	{
		if (ray.len > data->set.view)
			ray.len = INFINITY;
		ray.len *= data->set.coslen[x];
		drawv(data, &ray, x);
	}
}

void	raycast(t_data *data)
{
	size_t	i;
	t_point	cur;
	t_point	end;
	t_point	inc;
	t_point	vec;

	cur.x = data->play.x + data->play.cosa - data->set.tanfov * data->play.sina;
	cur.y = data->play.y + data->play.sina + data->set.tanfov * data->play.cosa;
	end.x = data->play.x + data->play.cosa + data->set.tanfov * data->play.sina;
	end.y = data->play.y + data->play.sina - data->set.tanfov * data->play.cosa;
	inc = (t_point){(end.x - cur.x) * data->set.invwid,
		(end.y - cur.y) * data->set.invwid};
	i = 0;
	while (i < data->set.wid)
	{
		vec = (t_point){(cur.x - data->play.x) * data->set.invlen[i],
			(cur.y - data->play.y) * data->set.invlen[i]};
		trace_ray(data, vec.x, vec.y, i);
		++i;
		cur.x += inc.x;
		cur.y += inc.y;
		data->px.x += data->pxinc.x;
	}
}
