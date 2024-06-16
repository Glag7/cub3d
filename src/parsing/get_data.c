/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 16:42:38 by glaguyon          #+#    #+#             */
/*   Updated: 2024/06/16 19:55:28 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "map.h"
#include "math.h"
#include "err.h"
#include "utils.h"

static inline int	parse_char(char *c, double x, double y, t_map *m)
{
	if ((*c == 'N' || *c == 'S' || *c == 'W' || *c == 'E') && m->player.x != -1)
	{
		ft_perror(ERR_MOREPLAYER);
		return (1);
	}
	if (*c == 'N' || *c == 'S' || *c == 'W' || *c == 'E')
	{
		*c = '0';
		m->player.x = x;
		m->player.y = y;
	}
	if (*c == 'N')
		m->player.a = 0.;
	else if (*c == 'E')
		m->player.a = M_PI_2;
	else if (*c == 'S')
		m->player.a = M_PI;
	else if (*c == 'E')
		m->player.a = -M_PI_2;
	else if (!(*c == '0' || *c == '1' || *c == ' '))
	{
		ft_perror(ERR_BADCHAR);
		return (1);
	}
	return (0);
}

int	get_data(char *buf, t_map *map)
{
	size_t	i;

	map->player.x = -1.;
	while (*buf)
	{
		i = 0;
		while (buf[i] && buf[i] != '\n')
		{
			if (parse_char(buf + i, (double)i, (double)map->hei, map))
				return (1);
			i++;
		}
		++map->hei;
		if (i > map->wid)
			map->wid = i;
		buf += i + (buf[i] == '\n');
	}
	if (map->player.x == -1)
	{
		ft_perror(ERR_NOPLAYER);
		return (1);
	}
	return (0);
}
