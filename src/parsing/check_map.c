/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 19:27:08 by glaguyon          #+#    #+#             */
/*   Updated: 2024/06/16 20:25:55 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "map.h"
#include "err.h"
#include "utils.h"

static inline int	check_zero(t_map *map, size_t x, size_t y)
{
	size_t	i;

	i = map->wid * y + x;
	return (map->map[i] == '0'
		&& (!x || !y || x == map->wid - 1 || y == map->hei - 1
			|| map->map[i + 1] == ' ' || map->map[i - 1] == ' '
			|| map->map[i + map->wid] == ' '
			|| map->map[i - map->wid] == ' '));
}

static void	replace_chars(t_map *map)
{
	size_t	size;
	size_t	i;

	size = map->wid * map->hei;
	i = 0;
	while (i < size)
	{
		if (map->map[i] == ' ')
			map->map[i] = 0;
		else
			map->map[i] -= '0';
		i++;
	}
}

int	check_map(t_map *map)
{
	size_t	x;
	size_t	y;

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
