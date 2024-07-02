/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawv.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 18:06:28 by glaguyon          #+#    #+#             */
/*   Updated: 2024/07/02 18:59:48 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stddef.h>
#include <stdint.h>
#include "data.h"
#include "map.h"
#include "ray.h"

static void	drawv_internal(t_data *data, t_img img, unsigned int x, double hei)
{
	double			inc;
	double			index;
	unsigned int	i;
	unsigned int	start;
	unsigned int	end;

	index = 0.;
	inc = 1. / hei * (double)img.size;
	if (hei > data->set.hei)
	{
		index = (hei - (double)data->set.hei) * inc * .5;
		hei = data->set.hei;
	}
	start = (data->set.hei - (unsigned int)hei) / 2;
	end = (data->set.hei + (unsigned int)hei) / 2;
	i = 0;
	while (i < start)
	{
		data->mlx.px[x + i * data->set.wid] = data->map.ceil;
		i++;
	}
	while (i < end)
	{
		data->mlx.px[x + i * data->set.wid] = img.px[(int)index * img.size];
		index += inc;
		i++;
	}
	while (i < data->set.hei)
	{
		data->mlx.px[x + i * data->set.wid] = data->map.floor;
		i++;
	}
}

void	drawv(t_data *data, t_ray *ray, size_t x)//si !hit appeler avec image a null
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
	drawv_internal(data, img, x, ((double)data->set.hei / ray->len));
}
