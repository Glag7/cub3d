/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_buf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 17:57:20 by glaguyon          #+#    #+#             */
/*   Updated: 2024/06/28 18:01:24 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <stddef.h>
#include <stdlib.h>
#include "map.h"
#include "utils.h"
#include "parsing.h"
#include "err.h"

static int	check_textures(t_map *map, int hasfloor, int hasceil)
{
	if (!map->n.px)
		ft_perror(ERR_MISS_NO);
	else if (!map->s.px)
		ft_perror(ERR_MISS_SO);
	else if (!map->w.px)
		ft_perror(ERR_MISS_WE);
	else if (!map->e.px)
		ft_perror(ERR_MISS_EA);
	else if (!hasceil)
		ft_perror(ERR_MISS_CEIL);
	else if (!hasfloor)
		ft_perror(ERR_MISS_FLOOR);
	return (!hasfloor || !hasceil || !map->n.px || !map->s.px
		|| !map->w.px || !map->e.px);
}

static char	*get_textures(void *mlx, t_map *map, char *buf)
{
	unsigned int	i;
	int				hasfloor;
	int				hasceil;

	i = 0;
	hasfloor = 0;
	hasceil = 0;
	while (buf[i] == '\n' || (i == 0 && buf[i]))
	{
		i += buf[i] == '\n';
		hasfloor += buf[i] == 'F';
		hasceil += buf[i] == 'C';
		if (hasfloor > 1)
			ft_perror(ERR_DUP_FLOOR);
		if (hasceil > 1)
			ft_perror(ERR_DUP_CEIL);
		if (hasfloor > 1 || hasceil > 1)
			return (NULL);
		if (try_load(mlx, map, buf, &i))
			return (NULL);
	}
	if (check_textures(map, hasfloor, hasceil))
		return (NULL);
	return (buf + i);
}

int	parse_buf(void *mlx, t_data *data, char *buf, size_t size)
{
	char	*start;

	start = NULL;
	if (size > UINT_MAX)
		ft_perror(ERR_TOOLARGE);
	else
		start = get_textures(mlx, &data->map, buf);
	if (start == NULL || get_data(start, data))
	{
		free_map(&data->map);
		free(buf);
		return (1);
	}
	data->map.map = malloc(data->map.hei * data->map.wid);
	if (data->map.map == NULL)
	{
		ft_perror(ERR_MALLOC);
		free_map(&data->map);
		free(buf);
		return (1);
	}
	fill_map(&data->map, start);
	free(buf);
	return (check_map(&data->map));
}
