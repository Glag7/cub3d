/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 14:40:40 by glaguyon          #+#    #+#             */
/*   Updated: 2024/07/02 18:07:35 by glaguyon         ###   ########.fr       */
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

static void	trace_ray(t_data *data, double a, size_t x)
{
	t_ray	ray;

	ray.pos = (t_point){data->play.x, data->play.y};
	ray.ipos = (t_ipoint){ray.pos.x, ray.pos.y};
	ray.vec = (t_point){cos(a), -sin(a)};
	init_ray(&ray);
	cast_ray(&ray, data);
	ray.pos.x += ray.len * ray.vec.x;
	ray.pos.y += ray.len * ray.vec.y;
	if (ray.len > data->set.view)
	{
		ray.len = data->set.view;
		ray.hit = 0;
	}
	drawv(data, &ray, x);
}

void	raycast(t_data *data)
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
