/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 18:53:05 by glaguyon          #+#    #+#             */
/*   Updated: 2024/06/28 18:55:52 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdint.h>
#include <stddef.h>
#include "data.h"

static inline uint32_t	get_color(t_data *data, int i, int j)
{
	long long	x;
	long long	y;

	x = (long long)floor(data->play.x + (-data->play.cosa
				* (double)j + data->play.sina * (double)i) / data->set.ratio);
	y = (long long)floor(data->play.y + (data->play.cosa
				* (double)i + data->play.sina * (double)j) / data->set.ratio);
	if (x < 0LL)
		x = ((long long)data->map.wid * -x + x) % (long long)data->map.wid;
	else if (x >= data->map.wid)
		x %= (long long)data->map.wid;
	if (y < 0LL)
		y = ((long long)data->map.hei * -y + y) % (long long)data->map.hei;
	else if (y >= data->map.hei)
		y %= (long long)data->map.hei;
	if (data->map.map[(long long)(x + y * data->map.wid)])
		return (data->set.ncolor);
	return (data->set.color);
}

void	draw_minimap(t_data *data)
{
	unsigned int			i;
	unsigned int			j;

	i = data->set.offthread;
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
		i += data->set.nthread;
	}
}
