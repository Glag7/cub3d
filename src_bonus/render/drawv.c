/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawv.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 18:06:28 by glaguyon          #+#    #+#             */
/*   Updated: 2024/07/14 19:30:54 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stddef.h>
#include <stdint.h>
#include "data.h"
#include "map.h"
#include "ray.h"

static void	drawv2(t_data *data, t_img img, unsigned int x, double hei)
{
	double			inc;
	double			index;
	int	i;
	int	start;
	int	end;

	inc = 1. / hei * (double)img.size;
	index = 0.;
	start = (data->set.hei - (unsigned int)hei) / 2 + data->play.az * 1000.;
	end = (data->set.hei + (unsigned int)hei) / 2 + data->play.az * 1000.;
	if (hei > (double)data->set.hei)
	{
		index = (hei - (double)data->set.hei) * inc * .5;
		hei = (double)data->set.hei;
	}
	if (start < 0)
		start = 0;
	if (start >= data->set.hei)
		start = data->set.hei - 1;
	if (end < 0)
		end = 0;
	if (end >= data->set.hei)
		end = data->set.hei - 1;
	i = 0;
	while (i < start)
		data->mlx.px[x + i++ *data->set.wid] = data->map.ceil;
	while (i < end)
	{
		data->mlx.px[x + i++ *data->set.wid] = img.px[(int)index * img.size];
		index += inc;
	}
	while (i < data->set.hei)
		data->mlx.px[x + i++ *data->set.wid] = data->map.floor;
}

void	drawv(t_data *data, t_ray *ray, size_t x)
{
	t_img			img;

	if (ray->side == XSIDE && ray->vec.x > 0)
	{
		img = data->map.e;
		img.px += (size_t)((ray->pos.y - floor(ray->pos.y)) * (double)img.size);
	}
	else if (ray->side == XSIDE)
	{
		img = data->map.w;
		img.px += (size_t)((1. - (ray->pos.y - floor(ray->pos.y)))
				* (double)img.size);
	}
	else if (ray->vec.y > 0)
	{
		img = data->map.s;
		img.px += (size_t)((1. - (ray->pos.x - floor(ray->pos.x)))
				* (double)img.size);
	}
	else
	{
		img = data->map.n;
		img.px += (size_t)((ray->pos.x - floor(ray->pos.x)) * (double)img.size);
	}
	drawv2(data, img, x, (double)data->set.wid / (data->set.tanfov * 2. * ray->len));
}
