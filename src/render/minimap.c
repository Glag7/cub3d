/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 18:53:05 by glaguyon          #+#    #+#             */
/*   Updated: 2024/06/22 15:40:39 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stddef.h>
#include "data.h"

#define CASES 5
#define COLOR 0XFFFFFFCC
#define NOCOLOR 0X0

static inline uint32_t	get_color(t_data *data, int i, int j)
{
	int	index;

	index = (int)((double)data->map.player.x + ((double)data->map.player.y * (double)data->map.wid)
		+ ((double)i * (double)CASES) / (double)data->mlx.mini.d
		+ (int)(((double)j * (double)CASES) / (double)data->mlx.mini.d) * (double)data->map.wid);
	if (data->map.map[index])
		return (NOCOLOR);
	else
		return (COLOR);
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
			if (data->mlx.mini.mask[j * data->mlx.mini.d + i])
				data->mlx.px[(j + data->mlx.mini.offset) * data->mlx.wid + i
					+ data->mlx.mini.offset] = get_color(data, (i - data->mlx.mini.d / 2), j - data->mlx.mini.d / 2);
			j++;
		}
		i++;
	}
	//carre a l'echelle
}

/*\

		while (j < data->mlx.mini.d)//FIXME dont look twice
		{//TODO baser sur ncase (faire 1 dixieme de case)
			if (i >= data->mlx.mini.d * 45 / 100 && i <= data->mlx.mini.d * 55 / 100 &&  j >= data->mlx.mini.d * 45 / 100 && j <= data->mlx.mini.d * 55 / 100 && data->mlx.mini.mask[j * data->mlx.mini.d + i])
*/