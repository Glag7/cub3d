/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 19:26:47 by glaguyon          #+#    #+#             */
/*   Updated: 2024/06/16 20:19:36 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "map.h"

void	fill_map(t_map *map, char *buf)
{
	size_t	i;
	size_t	len;

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
