/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 19:26:47 by glaguyon          #+#    #+#             */
/*   Updated: 2024/06/28 17:52:53 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "map.h"

void	fill_map(t_map *map, char *buf)
{
	unsigned int	i;
	unsigned int	len;

	i = 0;
	while (*buf)
	{
		len = 0;
		while (buf[len] && buf[len] != '\n')
		{
			map->map[i + len] = buf[len];
			++len;
		}
		buf += len + (buf[len] == '\n');
		while (len < map->wid)
			map->map[i + len++] = ' ';
		i += len;
	}
}
