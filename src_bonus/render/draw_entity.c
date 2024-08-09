/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_entity.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 13:27:54 by glaguyon          #+#    #+#             */
/*   Updated: 2024/08/09 15:16:03 by glaguyon         ###   ########.fr       */
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

void cast_ray2(t_ray *ray, t_data *data, double len)
{
	while (!(ray->hit & ENTITY) && ray->len > 0.)
	{
		ray->side = !(ray->dist.x < ray->dist.y);
		if (ray->side == XSIDE)
		{
			ray->ipos.x += ray->istep.x;
			ray->len = len - ray->dist.x;
			ray->dist.x += ray->step.x;
		}
		else
		{
			ray->ipos.y += ray->istep.y;
			ray->len = len - ray->dist.y;
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
		ray->hit = data->map.map[data->map.wid * ray->ipos.y + ray->ipos.x];
	}//opti: mettre &= et check les ennemis que si y a un truc
}

#include <math.h>
#include <stddef.h>
#include <stdint.h>
#include "data.h"
#include "map.h"
#include "ray.h"

static inline void __attribute__((always_inline))
	init_ddata(t_data *data, t_draw *ddata, double hei, double inc)
{
	const double	zoffset = data->set.planwid * data->play.az / M_PI * 4.
		+ hei * data->play.z;

	ddata->start = ((double)data->set.hei - hei * .25) * .5 + zoffset + 2.5;
	ddata->end = ((double)data->set.hei + hei) * .5 + zoffset + 2.5;
	ddata->index = 0.;
	ddata->ypx = data->px.y;
	if (ddata->start < 0.)
	{
		ddata->index = (double)-ddata->start * inc;
		ddata->start = 0.;
	}
	else if (ddata->start >= (int)data->set.hei)
		ddata->start = data->set.hei;
	if (ddata->end >= (int)data->set.hei)
		ddata->end = data->set.hei;
}

static void	drawv2(t_data *data, t_img img, unsigned int x, double hei)
{
	t_draw			ddata;
	int				i;
	const double	inc = 1. / hei * (double)img.w;

	init_ddata(data, &ddata, hei, inc);
	i = ddata.start;
	while (i < ddata.end)
	{
		if (img.px[(int)ddata.index * img.w]& 0XFF000000)
			data->mlx.px[x + i *data->set.wid] = img.px[(int)ddata.index * img.w];
		++i;
		ddata.index += inc;
	}
}

void	drawv3(t_data *data, t_ray *ray, size_t x)
{
	t_img			img;

	if (ray->side == XSIDE && ray->vec.x > 0)
	{
		img = data->tmp;
		img.px += (size_t)((ray->pos.y - floor(ray->pos.y)) * (double)img.w);
	}
	else if (ray->side == XSIDE)
	{
		img = data->tmp;
		img.px += (size_t)((1. - (ray->pos.y - floor(ray->pos.y)))
				* (double)img.w);
	}
	else if (ray->vec.y > 0)
	{
		img = data->tmp;
		img.px += (size_t)((1. - (ray->pos.x - floor(ray->pos.x)))
				* (double)img.w);
	}
	else
	{
		img = data->tmp;
		img.px += (size_t)((ray->pos.x - floor(ray->pos.x)) * (double)img.w);
	}
	drawv2(data, img, x, (data->set.planwid / ray->len));
}
