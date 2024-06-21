/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 18:53:05 by glaguyon          #+#    #+#             */
/*   Updated: 2024/06/21 20:07:02 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stddef.h>
#include "data.h"

static inline void	draw_line(t_data *data, uint32_t *px)
{
	*(px) = 0xFFFF0000;
	*(px - data->mlx.wid) = 0xFFFF0000;
	*(px + data->mlx.wid) = 0xFFFF0000;
	*(px + 2 * data->mlx.wid) = 0xFFFF0000;
	*(px - 2 * data->mlx.wid) = 0xFFFF0000;
	*(px + 3 * data->mlx.wid) = 0xFFFF0000;
	*(px - 3 * data->mlx.wid) = 0xFFFF0000;
	*(px + 4 * data->mlx.wid) = 0xFFFF0000;
	*(px - 4 * data->mlx.wid) = 0xFFFF0000;
	*(px + 5 * data->mlx.wid) = 0xFFFF0000;
	*(px - 5 * data->mlx.wid) = 0xFFFF0000;
}

void	draw_minimap(t_data *data)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	while (i < data->mlx.mini.d)
	{
		j = 0;
		while (j < data->mlx.mini.d)
		{
			if (data->mlx.mini.mask[i * data->mlx.mini.d + j])
				data->mlx.px[(i + data->mlx.mini.offset) * data->mlx.wid + j + data->mlx.mini.offset] = 0xFFFFFFFF;
			j++;
		}
		i++;
	}
	draw_line(data, &data->mlx.px[(data->mlx.mini.d / 2 + data->mlx.mini.offset) * data->mlx.wid + data->mlx.mini.d / 2 + data->mlx.mini.offset]);
	draw_line(data, &data->mlx.px[(data->mlx.mini.d / 2 + data->mlx.mini.offset - 1) * data->mlx.wid + data->mlx.mini.d / 2 + data->mlx.mini.offset + 1]);
	draw_line(data, &data->mlx.px[(data->mlx.mini.d / 2 + data->mlx.mini.offset - 1) * data->mlx.wid + data->mlx.mini.d / 2 + data->mlx.mini.offset - 1]);
	draw_line(data, &data->mlx.px[(data->mlx.mini.d / 2 + data->mlx.mini.offset - 2) * data->mlx.wid + data->mlx.mini.d / 2 + data->mlx.mini.offset + 2]);
	draw_line(data, &data->mlx.px[(data->mlx.mini.d / 2 + data->mlx.mini.offset - 2) * data->mlx.wid + data->mlx.mini.d / 2 + data->mlx.mini.offset - 2]);
}

//TODO draw arrow
//TODO j'ai passe des trucs en unsigned enlever les size_t inutiles
