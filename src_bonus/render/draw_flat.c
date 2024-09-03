/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_flat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 18:27:08 by glaguyon          #+#    #+#             */
/*   Updated: 2024/09/03 18:00:20 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "data.h"
#include "img.h"
#include "map.h"
#include "ray.h"
#include "render.h"

static void	drawv2(t_data *data, t_img img, unsigned int x, double hei, uint32_t mdata)
{
	t_draw			ddata;
	int				i;
	const double	inc = (1.) / hei * (double)img.h;
	const double	zoffset = data->set.planwid * data->play.az / M_PI * 4.
		+ hei * data->play.z
		- ((mdata & SPEC) == FENCE) * hei * ((double)((mdata & VALUE) >> VALUEOFF) / VALUEONE - .5);

	ddata.start = ((double)data->set.hei - hei) * .5 + zoffset + 2.5;
	ddata.end = ((double)data->set.hei + hei) * .5 + zoffset + 2.5;
	ddata.index = 0.;
	ddata.ypx = data->px.y;
	if (ddata.start < 0.)
	{
		ddata.index = (double)-ddata.start * inc;
		ddata.start = 0.;
	}
	else if (ddata.start >= (int)data->set.hei)
		ddata.start = data->set.hei;
	if (ddata.end >= (int)data->set.hei)
		ddata.end = data->set.hei;
	i = ddata.start;
	while (i < ddata.end)
	{
		if (img.px[(int)ddata.index * img.w]& 0XF0000000)//
			data->mlx.px[x + i *data->set.wid] = img.px[(int)ddata.index * img.w];
		++i;
		ddata.index += inc;
	}
}

void	draw_flat(t_data *data, t_ray *ray, size_t x)
{
	t_img			img;

	if ((ray->side & SPEC) == DOOR)
		img = data->map.d;
	else if ((ray->side & SPEC) == GLASS)
		img = data->map.g;
	else
		img = data->map.h;
	img.px += (size_t)((ray->pos.y - floor(ray->pos.y)) * (double)img.w);
	drawv2(data, img, x,( data->set.planwid / ray->len) * img.h / img.w, ray->side);
}
