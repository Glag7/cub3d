/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawv.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 18:06:28 by glaguyon          #+#    #+#             */
/*   Updated: 2024/08/02 16:33:16 by glaguyon         ###   ########.fr       */
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

	zoffset = hei * data->play.z;
	azoffset = (double)data->set.wid / (data->set.tanfov * 2.) * data->play.az / M_PI * 4.;
	inc = 1. / hei * (double)img.w;
	start = ((int)data->set.hei - (int)hei) / 2 + azoffset + zoffset + 1.;
	end = ((int)data->set.hei + (int)hei) / 2 + azoffset + zoffset + 1.;
	index = 0.;
	if (start < 0.)
	{
		index = (double)-start * inc;
		start = 0.;
	}
	//else if (start >= (int)data->set.hei)
	//	start = data->set.hei;//nuh huh
	if (end >= (int)data->set.hei)
		end = data->set.hei;
	i = start;
	//while (i < start)
	//	data->mlx.px[x + i++ *data->set.wid] = data->map.ceil;
	while (i < end)
	{
		data->mlx.px[x + i++ *data->set.wid] = img.px[(int)index * img.w];
		index += inc;
	}//1 trop loin FIXME valgrind//normalement fix
	//while (i < (int)data->set.hei)
	//	data->mlx.px[x + i++ *data->set.wid] = data->map.floor;
}//FIXME barre en bas

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
	drawv2(data, img, x, (double)data->set.wid / (data->set.tanfov * 2. * ray->len), 1. / ray->len);
}//TODO:(double)data->set.wid / (data->set.tanfov * 2.) constqnte = wid cub a 1
