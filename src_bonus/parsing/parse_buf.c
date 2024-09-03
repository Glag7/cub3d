/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_buf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 17:57:20 by glaguyon          #+#    #+#             */
/*   Updated: 2024/09/03 17:31:25 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <stddef.h>
#include <stdlib.h>
#include "data.h"
#include "map.h"
#include "utils.h"
#include "parsing.h"
#include "err.h"

static int	check_textures(void *mlx, t_map *map, t_data *data)
{
	if (!map->n.px)
		ft_perror(ERR_MISS_NO);
	else if (!map->s.px)
		ft_perror(ERR_MISS_SO);
	else if (!map->w.px)
		ft_perror(ERR_MISS_WE);
	else if (!map->e.px)
		ft_perror(ERR_MISS_EA);
	else if (!map->c.px)
		ft_perror(ERR_MISS_CEIL);
	else if (!map->f.px)
		ft_perror(ERR_MISS_FLOOR);
	return (!map->f.px || !map->c.px || !map->n.px || !map->s.px
		|| !map->w.px || !map->e.px
		|| (!map->d.px && load_door(mlx, data, NULL, NULL))
		|| (!map->h.px && load_topbottom(mlx, data, NULL, NULL))
		|| (!map->g.px && load_glass(mlx, data, NULL, NULL)));
}

static char	*get_textures(t_data *data, void *mlx, t_map *map, char *buf)
{
	unsigned int	i;

	i = 0;
	while (buf[i] == '\n' || (i == 0 && buf[i]))
	{
		i += buf[i] == '\n';
		if (try_load(mlx, data, buf, &i))
			return (NULL);
	}
	if (check_textures(mlx, map, data))
		return (NULL);
	return (buf + i);
}

int	parse_buf(void *mlx, t_data *data, char *buf, size_t size)
{
	char	*start;

	start = NULL;
	if (size >= INT_MAX - 2)
		ft_perror(ERR_TOOLARGE);
	else
		start = get_textures(data, mlx, &data->map, buf);
	if (start == NULL || get_data(start, data))
	{
		free_map(&data->map);
		free(buf);
		return (1);
	}
	data->map.map = malloc(data->map.hei * data->map.wid
			* sizeof(*data->map.map));
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
