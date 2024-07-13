/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 14:40:40 by glaguyon          #+#    #+#             */
/*   Updated: 2024/07/13 16:50:15 by glaguyon         ###   ########.fr       */
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

void	raycast(t_data *data)
{
	size_t	i;
	double	tanfov;
	t_point	start;
	t_point	end;
	t_point inc;
	t_point curr;
	t_point vec;

	tanfov = tan(data->set.fov * .5);
	start = (t_point){data->play.x + data->play.cosa - tanfov * data->play.sina,
		data->play.y + data->play.sina + tanfov * data->play.cosa};
	end = (t_point){data->play.x + data->play.cosa + tanfov * data->play.sina,
		data->play.y + data->play.sina - tanfov * data->play.cosa};
	inc = (t_point){(end.x - start.x) / (double)data->set.wid,
		(end.y - start.y) / (double)data->set.wid};
	curr = (t_point){start.x + inc.x * (double)data->set.offthread,
		start.y + inc.y * (double)data->set.offthread};
	i = data->set.offthread;
	//printf("play %f,%f\tstart %f,%f\tend %f,%f\n", data->play.x, data->play.y, start.x, start.y, end.x, end.y);
	//printf("inc %f,%f\n", inc.x, inc.y);
	//printf("curr %f,%f\n", curr.x, curr.y);
	while (i < data->set.wid)
	{
		double	invlen;
		vec = (t_point){curr.x - data->play.x, curr.y - data->play.y};
		invlen = 1. / sqrt(vec.x * vec.x + vec.y * vec.y);
		vec.x *= invlen;
		vec.y *= invlen;
		//printf("vec %f,%f\n", vec.x, vec.y);
		trace_ray(data, vec.x, vec.y, i);
		i += data->set.nthread;
		curr.x += inc.x * (double)data->set.nthread;
		curr.y += inc.y * (double)data->set.nthread;
	}
}
