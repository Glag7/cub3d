/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 19:27:08 by glaguyon          #+#    #+#             */
/*   Updated: 2024/08/16 17:37:27 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include "err.h"
#include "utils.h"
#include "point.h"

static inline int	check_zero(t_map *map, unsigned int x, unsigned int y)
{
	unsigned int	i;

	i = map->wid * y + x;
	return (map->map[i] == '0'
		&& (!x || !y || x == map->wid - 1 || y == map->hei - 1
			|| map->map[i + 1] == ' ' || map->map[i - 1] == ' '
			|| map->map[i + map->wid] == ' '
			|| map->map[i - map->wid] == ' '));//+ ennemies
}

static void	replace_chars(t_map *map)//TODO FAIRE G ET D POUR PLACER LES PORTES ET VERRES (et clotures?)
{
	unsigned int	size;
	unsigned int	i;
	t_ipoint	pos;

	size = map->wid * map->hei;
	i = 0;
	while (i < size)
	{
		if (map->map[i] == '1')
			map->map[i] = CUBE;
		else if (map->map[i] == ' ' || map->map[i] == '0')
			map->map[i] = 0;
		//ennemis
		++i;
	}
	/*i = 0;
	pos = (t_ipoint){0, 0};
	while (i < size)
	{
		if (map->map[i] == 'G')
		{//use i + what if just 1
			if (map->map[(x + 1) % data->map.wid + y * data->map.wid]
				&& ((x > 0 && map->map[x - 1 + y * data->map.wid])
					|| (data->map.map[(y + 1) % data->map.hei * data->map.wid])))
				map->map[i] = XGLASS;
			else
				map->map[i] = YGLASS;
		}
		++i
		++pos.x;
		if (pos.x == data->map.wid)
		{
			pos.x -= data->map.wid;
			++pos.y;
		}
	}*/
}

int	check_map(t_map *map)
{//TODO PORTES ET ENNEMIS
	unsigned int	x;
	unsigned int	y;

	y = 0;
	while (y < map->hei)
	{
		x = 0;
		while (x < map->wid)
		{
			if (check_zero(map, x, y))
			{
				ft_perror(ERR_NOWALL);
				free_map(map);
				return (1);
			}
			++x;
		}
		++y;
	}
	replace_chars(map);
	return (0);
}
