/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 18:53:05 by glaguyon          #+#    #+#             */
/*   Updated: 2024/09/04 19:57:20 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdint.h>
#include <stddef.h>
#include "data.h"
#include "map.h"

static inline uint32_t	get_color(t_data *data, int i, int j)
{
	t_point		pos;
	t_ipoint	ipos;
	int			map;

	pos = (t_point){(data->play.x + (-data->play.cosa * (double)j
				+ data->play.sina * (double)i) / data->set.ratio),
		(data->play.y + (data->play.cosa * (double)i + data->play.sina
				* (double)j) / data->set.ratio)};
	ipos = (t_ipoint){(long long)floor(pos.x), (long long)floor(pos.y)};
	if (ipos.x < 0LL)
		ipos.x = ((long long)data->map.wid * -ipos.x + ipos.x) % (long long)data->map.wid;
	else if (ipos.x >= data->map.wid)
		ipos.x %= (long long)data->map.wid;
	if (ipos.y < 0LL)
		ipos.y = ((long long)data->map.hei * -ipos.y + ipos.y) % (long long)data->map.hei;
	else if (ipos.y >= data->map.hei)
		ipos.y %= (long long)data->map.hei;
	map = data->map.map[(long long)(ipos.x + ipos.y * data->map.wid)];
	pos = (t_point){pos.x - ipos.x, pos.y - ipos.y};
	if (map & CUBE)
		return (data->set.ncolor);
	if ((map & SIDE) && (map & SPEC) && pos.x > .45 && pos.x < .55)
		return (data->set.ncolor);
	if (!(map & SIDE) && (map & SPEC) && pos.y > .45 && pos.y < .55)
		return (data->set.ncolor);
	return (data->set.color);
}

void	draw_minimap(t_data *data)
{
	unsigned int			i;
	unsigned int			j;

	i = 0;
	while (i < data->set.d)
	{
		j = 0;
		while (j < data->set.d)
		{
			if (data->mini.m_curr[j * data->set.d + i])
			{
				if (i >= data->set.pstart && i <= data->set.pend
					&& j >= data->set.pstart && j <= data->set.pend)
					data->mlx.px[(j + data->set.yoffset) * data->set.wid + i
						+ data->set.xoffset] = data->set.pcolor;
				else
					data->mlx.px[(j + data->set.yoffset) * data->set.wid + i
						+ data->set.xoffset] = get_color(data,
							i - data->set.r, j - data->set.r);
			}
			++j;
		}
		++i;
	}
}
