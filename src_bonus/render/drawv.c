/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawv.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 18:06:28 by glaguyon          #+#    #+#             */
/*   Updated: 2024/09/03 19:00:46 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

	ddata->start = ((double)data->set.hei - hei) * .5 + zoffset + 2.5;
	ddata->end = ((double)data->set.hei + hei) * .5 + zoffset + 2.5;
	ddata->index = 0.;
	ddata->ypx = data->px.y;
	if (ddata->start < 0)
	{
		ddata->index = (double)-ddata->start * inc;
		ddata->start = 0;
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

	i = 0;
	init_ddata(data, &ddata, hei, inc);
	while (i < ddata.start)
	{
		data->mlx.px[x + i++ *data->set.wid]
			= data->map.c.px[((int)data->px.x & (data->map.c.w - 1))
			+ ((int)ddata.ypx & (data->map.c.h - 1)) * (int)data->map.c.w];
		ddata.ypx += data->pxinc.y;
	}
	while (i < ddata.end)
	{
		data->mlx.px[x + i++ *data->set.wid] = img.px[(int)ddata.index * img.w];
		ddata.index += inc;
	}
}

void	drawv(t_data *data, t_ray *ray, size_t x)
{
	t_img			img;

	if (ray->side == XSIDE && ray->vec.x > 0)
	{
		img = data->map.e;
		img.px += (size_t)((ray->pos.y - floor(ray->pos.y)) * (double)img.w);
	}
	else if (ray->side == XSIDE)
	{
		img = data->map.w;
		img.px += (size_t)((1. - (ray->pos.y - floor(ray->pos.y)))
				* (double)img.w);
	}
	else if (ray->vec.y > 0)
	{
		img = data->map.s;
		img.px += (size_t)((1. - (ray->pos.x - floor(ray->pos.x)))
				* (double)img.w);
	}
	else
	{
		img = data->map.n;
		img.px += (size_t)((ray->pos.x - floor(ray->pos.x)) * (double)img.w);
	}
	drawv2(data, img, x, (data->set.planwid / ray->len));
}
