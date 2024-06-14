/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_buf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 17:57:20 by glaguyon          #+#    #+#             */
/*   Updated: 2024/06/14 18:54:02 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "map.h"
#include "utils.h"

static int	get_textures(void *mlx, t_map *map, char *buf, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size && buf[i] == '\n')
		i++;
	if (i < size + 1 && (buf[i] == 'N' && buf[i] == 'O')
		return (1)
}

int	parse_buf(void *mlx, t_map *map, char *buf, size_t size)
{
	if (get_textures(mlx, map, buf, size))
	{
		free(buf);
		return (1);
	}
	return (0);
}
