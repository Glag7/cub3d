/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_hud.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 17:25:45 by glaguyon          #+#    #+#             */
/*   Updated: 2024/09/04 18:45:24 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"
#include "set.h"
#include "render.h"

static void	draw_gun(t_data *data, t_img img)
{
	const t_ipoint	start = {3 * data->set.wid / 8, 3 * data->set.hei / 4};
	const t_ipoint	end = {5 * data->set.wid / 8, data->set.hei};
	const t_point	inc = {(double)img.w / (double)(end.x - start.x),
		(double)img.h / (double)(end.y - start.y)};
	t_ipoint		pos;
	t_point			tex;

	tex = (t_point){0., 0.};
	pos.x = start.x;
	while (pos.x < end.x)
	{
		pos.y = start.y;
		tex.y = 0.;
		while (pos.y < end.y)
		{
			if (img.px[(int)tex.x + (int)tex.y * img.w] & 0xF0000000)
				data->mlx.px[pos.x + data->set.wid * pos.y]
					= img.px[(int)floor(tex.x) + (int)floor(tex.y) * img.w];
			++pos.y;
			tex.y += inc.y;
		}
		++pos.x;
		tex.x += inc.x;
	}
}

//TODO anim time dans la struct

void	draw_hud(t_data *data)
{
	if (data->lastshot > data->map.gun.time)
		draw_gun(data, data->map.gun.frames[0]);
	else
		draw_gun(data, data->map.gun.frames[(int)((1. - data->lastshot / data->map.gun.time) * (data->map.gun.max - 1))]);
	data->mlx.px[data->set.hei / 2 * data->set.wid
		+ data->set.wid / 2] = data->set.crosscolor;
	data->mlx.px[data->set.hei / 2 * data->set.wid
		+ data->set.wid / 2 + 1] = data->set.crosscolor;
	data->mlx.px[data->set.hei / 2 * data->set.wid
		+ data->set.wid + data->set.wid / 2] = data->set.crosscolor;
	data->mlx.px[data->set.hei / 2 * data->set.wid
		+ data->set.wid + data->set.wid / 2 + 1] = data->set.crosscolor;
}
