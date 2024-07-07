/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 14:40:40 by glaguyon          #+#    #+#             */
/*   Updated: 2024/07/07 23:08:55 by glag             ###   ########.fr       */
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

static void	init_ray(t_ray *ray)
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
	while (!ray->hit && ray->len < data->set.view)
	{
		ray->side = !(ray->dist.x < ray->dist.y);
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
		ray->hit = (data->map.map[data->map.wid * ray->ipos.y + ray->ipos.x]);
	}
}

static void	trace_ray(t_data *data, double px, double py, size_t x)
{
	t_ray	ray;

	ray.pos = (t_point){data->play.x, data->play.y};
	ray.ipos = (t_ipoint){ray.pos.x, ray.pos.y};
	ray.vec = (t_point){px, -py};
	init_ray(&ray);
	cast_ray(&ray, data);
	ray.pos.x += ray.len * ray.vec.x;
	ray.pos.y += ray.len * ray.vec.y;
	if (ray.len > data->set.view)
	{
		ray.len = INFINITY;
		ray.hit = 0;
	}
	drawv(data, &ray, x);
}

//todo: fov + planewid + realfov;
//multithread !!
void	raycast(t_data *data)
{
	t_point	start;
	t_point	end;
	t_point	inc;
	size_t	i;

	i = data->set.offthread;
	start.x = data->play.x + data->play.cosa * tan(data->play.a * .5);
	start.y = data->play.y + data->play.sina * tan(data->play.a * .5);
	end.x = data->play.x + data->play.cosa * tan(data->play.a * .5);
	end.y = data->play.y + data->play.sina * tan(data->play.a * .5);
	inc.x = (end.x - start.x) / (double)data->set.wid * (double)data->set.nthread;
	inc.y = (end.y - start.y) / (double)data->set.wid * (double)data->set.nthread;
	while (i < data->set.wid)
	{
		trace_ray(data, start.x - data->play.x, start.y - data->play.y, i);
		i += data->set.nthread;
		start.x += inc.x;
		start.y += inc.y;
	}
}
