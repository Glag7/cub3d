/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 18:53:05 by glaguyon          #+#    #+#             */
/*   Updated: 2024/06/22 14:47:10 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stddef.h>
#include "data.h"

//TODO
//rayon
//couleur
//n de cases
//mask yesno
//nthread
//threadoffset

#define CASES 10
#define COLOR 0XFFFFFFCC
#define NOCOLOR 0X0

static inline uint32_t	get_color(t_data *data, int i, int j)
{
	int	index;

	index = (data->map.player.x + data->map.player.y * data->map.wid//case du joueur
		+ i * CASES / (int)data->mlx.mini.d
		+ j * CASES / (int)data->mlx.mini.d * (int)data->map.wid);
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
