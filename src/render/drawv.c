/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawv.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 18:06:28 by glaguyon          #+#    #+#             */
/*   Updated: 2024/06/21 18:48:08 by glaguyon         ###   ########.fr       */
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

	if (hei > data->mlx.hei)
		hei = data->mlx.hei;
	start = (data->mlx.hei - hei) / 2;
	end = (data->mlx.hei + hei) / 2;
	i = 0;
	while (i < start)
	{
		data->mlx.px[x + i * data->mlx.wid] = data->map.ceil;
		i++;
	}
	while (i < end)
	{
		data->mlx.px[x + i * data->mlx.wid] = color;
		i++;
	}
	while (i < data->mlx.hei)
	{
		data->mlx.px[x + i * data->mlx.wid] = data->map.floor;
		i++;
	}
}
