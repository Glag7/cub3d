/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawv.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 18:06:28 by glaguyon          #+#    #+#             */
/*   Updated: 2024/06/22 17:04:03 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdint.h>
#include "data.h"

//TODO widl
void	drawv(t_data *data, uint32_t color, unsigned int x, unsigned int hei)
{
	unsigned int	i;
	unsigned int	start;
	unsigned int	end;

	if (hei > data->set.hei)
		hei = data->set.hei;
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
		data->mlx.px[x + i * data->set.wid] = color;
		i++;
	}
	while (i < data->set.hei)
	{
		data->mlx.px[x + i * data->set.wid] = data->map.floor;
		i++;
	}
}
