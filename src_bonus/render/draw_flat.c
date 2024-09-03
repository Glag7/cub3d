/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_flat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 18:27:08 by glaguyon          #+#    #+#             */
/*   Updated: 2024/09/03 19:07:30 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "data.h"
#include "img.h"
#include "map.h"
#include "ray.h"
#include "render.h"


static inline void __attribute__((always_inline))
	init_draw_flat(t_data *data, t_draw *ddata, t_ray *ray, t_img *img)
{
	double	hei;
	double	zoffset;

	hei = data->set.planwid / ray->len;
	zoffset = data->set.planwid * data->play.az / M_PI * 4. + hei * data->play.z;
	if ((ray->side & SPEC) == DOOR)
	{
		*img = data->map.d;
		if ((double)((ray->side & VALUE) >> VALUEOFF) / VALUEONE 
				+ ray->pos.y - floor(ray->pos.y) > 1.)
			return ;
		img->px += (int)((double)((ray->side & VALUE) >> VALUEOFF) / VALUEONE * img->w);
	}
	else if ((ray->side & SPEC) == GLASS)
		*img = data->map.g;
	else
	{
		*img = data->map.h;
		hei *= .5;
		zoffset -= hei * ((double)((ray->side & VALUE) >> VALUEOFF) / VALUEONE - .5);
	}
	img->px += (size_t)((ray->pos.y - floor(ray->pos.y)) * (double)img->w);
	ddata->ypx = (1.) / hei * (double)img->h;
	ddata->start = ((double)data->set.hei - hei) * .5 + zoffset + 2.5;
	ddata->end = ((double)data->set.hei + hei) * .5 + zoffset + 2.5;
}

void	draw_flat(t_data *data, t_ray *ray, size_t x)
{
	t_draw	ddata;
	t_img	img;

	init_draw_flat(data, &ddata, ray, &img);
	ddata.index = 0.;
	if (ddata.start < 0)
	{
		ddata.index = (double)-ddata.start * ddata.ypx;
		ddata.start = 0;
	}
	if (ddata.end >= (int)data->set.hei)
		ddata.end = data->set.hei;
	while (ddata.start < ddata.end)
	{
		if (img.px[(int)ddata.index * img.w] & 0XF0000000)
			data->mlx.px[x + ddata.start * data->set.wid]
				= img.px[(int)ddata.index * img.w];
		++ddata.start;
		ddata.index += ddata.ypx;
	}
}
