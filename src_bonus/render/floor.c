/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 17:07:39 by glaguyon          #+#    #+#             */
/*   Updated: 2024/08/02 18:25:27 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "data.h"
#include "point.h"

void	draw_floor(t_data *data)
{
	const double	camheipx = (data->play.z + .5) * data->set.planwid;
	const t_point	baseinc = (t_point){(data->set.invplanwid * data->play.sina),
			-(data->set.invplanwid * data->play.cosa)};
	
	t_ipoint	pos; 
	t_point	start;
	t_point	inc;
	double	dist;

	start.x = data->play.cosa - data->set.tanfov * data->play.sina;
	start.y = data->play.sina + data->set.tanfov * data->play.cosa;
	pos.y = data->horizon - 1;
	if (pos.y < -1)
		pos.y = -1;

	t_point	cur;
	while (++pos.y < (int)data->set.hei)
	{
		dist = camheipx / (double)(pos.y - data->horizon);
		inc.x = baseinc.x * dist * (double)data->tmp.w;
		inc.y = baseinc.y * -dist * (double)data->tmp.h;
		cur.x = (data->play.x + dist * start.x) * (double)data->tmp.w;
		cur.y = (data->play.y - dist * start.y) * (double)data->tmp.h;
		pos.x = -1;
		while (++pos.x < (int)data->set.wid)
		{
			cur.x += inc.x;
			cur.y += inc.y;
			data->mlx.px[pos.x + pos.y * data->set.wid] =
				data->tmp.px[((int)cur.x & (data->tmp.w - 1))
				+ ((int)cur.y & (data->tmp.h - 1)) * data->tmp.w];
		}
	}
}
