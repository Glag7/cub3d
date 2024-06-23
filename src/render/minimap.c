/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 18:53:05 by glaguyon          #+#    #+#             */
/*   Updated: 2024/06/23 15:14:17 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdint.h>
#include <stddef.h>
#include "data.h"

static inline uint32_t	get_color(t_data *data, int i, int j)
{
	float	x;
	float	y;

	x = cos(data->play.a) * (float)j - sin(data->play.a) * (float)i;
	y = cos(data->play.a) * (float)i + sin(data->play.a) * (float)j;
	if (data->map.map[(int)(data->play.x + (float)x / (data->set.ratio)
			+ floor((data->play.y) + (float)y / (data->set.ratio))
			* (float)data->map.wid)])
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
