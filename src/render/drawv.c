/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawv.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 18:06:28 by glaguyon          #+#    #+#             */
/*   Updated: 2024/06/27 17:15:32 by ttrave           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdint.h>
#include "data.h"
#include "map.h"

void	drawv(t_data *data, t_img img, unsigned int x, unsigned int offset, unsigned int hei)
{
	float			inc;
	float			index;
	unsigned int	i;
	unsigned int	start;
	unsigned int	end;

	inc = 1. / (float) hei * (float)img.size;
	if (hei > data->set.hei)
	{
		index = (float)(hei - data->set.hei) * 0.5;
		hei = data->set.hei;
	}
	else
		index = 0.
	start = (data->set.hei - hei) / 2;
	end = (data->set.hei + hei) / 2;
	i = 0;
	while (i < start)
	{
		data->mlx.px[x + i * data->set.wid] = data->map.ceil;
		i++;
	}
	while (i < end)
	{

		data->mlx.px[x + i * data->set.wid] = img.px[offset + (int)(index) * img.size];
		index += inc;
		i++;
	}
	while (i < data->set.hei)
	{
		data->mlx.px[x + i * data->set.wid] = data->map.floor;
		i++;
	}
}
