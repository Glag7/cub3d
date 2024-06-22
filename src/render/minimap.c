/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 18:53:05 by glaguyon          #+#    #+#             */
/*   Updated: 2024/06/22 18:51:09 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdint.h>
#include <stddef.h>
#include "data.h"

static inline uint32_t	get_color(t_data *data, int i, int j)
{
	float	test;
	int	index;

	test = data->play.x + (float)i / ((float)data->set.d / (float)data->set.ncase)
			+ floor((data->play.y) + (float)j / ((float)data->set.d / (float)data->set.ncase)) * (float)data->map.wid;
	index = (int)test;
	if (data->map.map[index])
		return (data->set.ncolor);
	else
		return (data->set.color);
}

//TODO passer le ratio a getcolor
void	draw_minimap(t_data *data)
{
	unsigned int			i;
	unsigned int			j;
	const unsigned int		half = data->set.d / (data->set.ncase * 10);

	i = data->set.offthread;
	while (i < data->set.d)
	{
		j = data->set.offthread;
		while (j < data->set.d)
		{
			if (data->mini.m_curr[j * data->set.d + i])
			{
				if (i >= data->set.r - half && i <= data->set.r + half
					&& j >= data->set.r - half && j <= data->set.r + half)
					data->mlx.px[(j + data->set.offset) * data->set.wid + i
						+ data->set.offset] = data->set.pcolor;
				else
					data->mlx.px[(j + data->set.offset) * data->set.wid + i
						+ data->set.offset] = get_color(data,
							i - data->set.r, j - data->set.r);
			}
			++j;
		}
		i += data->set.nthread;
	}
}
