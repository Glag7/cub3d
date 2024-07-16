/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawv.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 18:06:28 by glaguyon          #+#    #+#             */
/*   Updated: 2024/07/16 18:32:22 by glag             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stddef.h>
#include <stdint.h>
#include "data.h"
#include "map.h"
#include "ray.h"

static void	drawv2(t_data *data, t_img img, unsigned int x, double hei, double test)
{
	double			inc;
	double			index;
	int	i;
	int	start;
	int	end;
	int	azoffset;
	int	zoffset;

	zoffset = (double)data->set.wid / (data->set.tanfov * 2.) * data->play.z / M_PI * 4. * test;//pas sur
	azoffset = (double)data->set.wid / (data->set.tanfov * 2.) * data->play.az / M_PI * 4.;//pas sur
	inc = 1. / hei * (double)img.size;
	start = ((int)data->set.hei - (int)hei) / 2 + azoffset + zoffset;
	end = ((int)data->set.hei + (int)hei) / 2 + azoffset + zoffset;
	index = 0.;
	//printf("%d %d\n", start, end);
	if (start < 0.)
	{
		index = (double)-start * inc;
		start = 0.;
	}
	else if (start >= (int)data->set.hei)
		start = data->set.hei - 1;
	if (end >= (int)data->set.hei)
		end = data->set.hei - 1;
	//printf("%d %d\n", start, end);
	i = 0;
	while (i < start)
		data->mlx.px[x + i++ *data->set.wid] = data->map.ceil;
	while (i < end)
	{
		data->mlx.px[x + i++ *data->set.wid] = img.px[(int)index * img.size];
		index += inc;
	}
	while (i < (int)data->set.hei)
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
	drawv2(data, img, x, (double)data->set.wid / (data->set.tanfov * 2. * ray->len), 1. / ray->len);
}//TODO:(double)data->set.wid / (data->set.tanfov * 2.) constqnte = wid cub a 1
