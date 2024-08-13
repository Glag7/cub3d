/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 19:27:08 by glaguyon          #+#    #+#             */
/*   Updated: 2024/08/13 16:33:35 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include "err.h"
#include "utils.h"

static inline int	check_zero(t_map *map, unsigned int x, unsigned int y)
{
	unsigned int	i;

	i = map->wid * y + x;
	return (map->map[i] == '0'
		&& (!x || !y || x == map->wid - 1 || y == map->hei - 1
			|| map->map[i + 1] == ' ' || map->map[i - 1] == ' '
			|| map->map[i + map->wid] == ' '
			|| map->map[i - map->wid] == ' '));
}

static void	replace_chars(t_map *map)//TODO FAIRE G ET D POUR PLACER LES PORTES ET VERRES (et clotures?)
{
	unsigned int	size;
	unsigned int	i;

	size = map->wid * map->hei;
	i = 0;
	while (i < size)
	{
		if (map->map[i] == '1')
			map->map[i] = CUBE;//porte: horizontal ou vertical
		else if (map->map[i] == 'G')//? + portes + les mettres dns les ennemis
			map->map[i] = GLASS;
		else
			map->map[i] = 0;
		i++;
	}
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
