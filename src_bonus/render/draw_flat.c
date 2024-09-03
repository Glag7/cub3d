/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_flat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 18:27:08 by glaguyon          #+#    #+#             */
/*   Updated: 2024/09/03 19:22:19 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "data.h"
#include "img.h"
#include "map.h"
#include "ray.h"
#include "render.h"

static inline void __attribute__((always_inline))
	init_draw_flat(t_data *dat, t_draw *ddata, t_ray *ray, t_img *img)
{
	double	texoff;
	double	hei;
	double	zof;

	texoff = (ray->pos.y - floor(ray->pos.y));
	hei = dat->set.planwid / ray->len;
	zof = dat->set.planwid * dat->play.az / M_PI * 4. + hei * dat->play.z;
	if ((ray->side & SPEC) == DOOR)
	{
		*img = dat->map.d;
		texoff += (double)((ray->side & VALUE) >> VALUEOFF) / VALUEONE;
	}
	else if ((ray->side & SPEC) == GLASS)
		*img = dat->map.g;
	else
	{
		*img = dat->map.h;
		hei *= .5;
		zof -= hei *((double)((ray->side & VALUE) >> VALUEOFF) / VALUEONE - .5);
	}
	if (texoff > 1.)
		return ;
	img->px += (size_t)(texoff * (double)img->w);
	ddata->start = ((double)dat->set.hei - hei) * .5 + zof + 2.5;
	ddata->end = ((double)dat->set.hei + hei) * .5 + zof + 2.5;
}

void	draw_flat(t_data *data, t_ray *ray, size_t x)
{
	t_draw	ddata;
	t_img	img;

	init_draw_flat(data, &ddata, ray, &img);
	ddata.ypx = ray->len / data->set.planwid * (double)img.w;
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
