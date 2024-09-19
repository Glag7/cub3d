/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_flat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 18:27:08 by glaguyon          #+#    #+#             */
/*   Updated: 2024/09/18 14:58:31 by glaguyon         ###   ########.fr       */
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

static inline int __attribute__((always_inline))
	mix_pixels(t_data *data, t_img img, t_draw *ddata, size_t x)
{
	uint32_t	imgcol;
	uint32_t	screencol;
	uint32_t	alpha;
	uint32_t	ialpha;

	screencol = data->mlx.px[x + ddata->start * data->set.wid];
	imgcol = img.px[(int)ddata->index * img.w];
	alpha = (imgcol & ALPHA) >> 24;
	ialpha = 255 - alpha;
	if (!alpha)
		return (0);
	if (alpha != 255)
		imgcol = ((((imgcol & RED) * alpha + (screencol & RED) * ialpha)
					>> 8) & RED)
			| ((((imgcol & GREEN) * alpha + (screencol & GREEN) * ialpha)
					>> 8) & GREEN)
			| ((((imgcol & BLUE) * alpha + (screencol & BLUE) * ialpha)
					>> 8) & BLUE);
	data->mlx.px[x + ddata->start * data->set.wid]
		= imgcol;
	return (1);
}

void	draw_flat(t_data *data, t_ray *ray, size_t x)
{
	t_draw		ddata;
	t_img		img;

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
		if (mix_pixels(data, img, &ddata, x) && x == data->set.wid / 2
			&& ddata.start == (int)data->set.hei / 2)
		{
			data->cross = data->map.map + ray->ipos.x
				+ ray->ipos.y * data->map.wid;
			data->cross_dist = ray->len;
		}
		++ddata.start;
		ddata.index += ddata.ypx;
	}
}
