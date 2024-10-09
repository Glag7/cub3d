/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 19:27:08 by glaguyon          #+#    #+#             */
/*   Updated: 2024/09/05 15:06:47 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include "err.h"
#include "utils.h"
#include "point.h"

static inline int	check_zero(t_map *map, int x, int y)
{
	return (map->map[map->wid * y + x] == '0'
		&& (map->map[map->wid * y + (x + 1) % map->wid] == ' '
			|| map->map[map->wid * y + x - 1 + map->wid * !x] == ' '
			|| map->map[map->wid * ((y + 1) % map->hei) + x] == ' '
			|| map->map[map->wid * (y - 1 + map->hei * !y) + x] == ' '));
}

static inline int	checky(t_map *map, int x, int y)
{
	const int	xwalls = !!map->map[map->wid * y + (x + 1) % map->wid]
		+ !!map->map[map->wid * y + x - 1 + map->wid * !x];
	const int	ywalls = !!map->map[map->wid * ((y + 1) % map->hei) + x]
		+ !!map->map[map->wid * (y - 1 + map->hei * !y) + x];

	if (ywalls >= xwalls)
		return (YSIDE);
	return (XSIDE);
}

static void	replace_flat(t_map *map)
{
	unsigned int	x;
	unsigned int	y;

	y = 0;
	while (y < map->hei)
	{
		x = 0;
		while (x < map->wid)
		{
			if (map->map[map->wid * y + x] == 'G')
				map->map[map->wid * y + x] = GLASS | checky(map, x, y);
			else if (map->map[map->wid * y + x] == 'D')
				map->map[map->wid * y + x] = DOOR | checky(map, x, y);
			else if (map->map[map->wid * y + x] == 'T')
				map->map[map->wid * y + x] = FENCE
					| VALUEONE << VALUEOFF | checky(map, x, y);
			else if (map->map[map->wid * y + x] == 'B')
				map->map[map->wid * y + x] = FENCE | checky(map, x, y);
			++x;
		}
		++y;
	}
}

static void	replace_chars(t_map *map)
{
	unsigned int	size;
	unsigned int	i;

	size = map->wid * map->hei;
	i = 0;
	while (i < size)
	{
		if (map->map[i] == '1')
			map->map[i] = CUBE;
		else if (map->map[i] == ' ' || map->map[i] == '0')
			map->map[i] = 0;
		++i;
	}
	replace_flat(map);
}

int	check_map(t_map *map)
{
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
