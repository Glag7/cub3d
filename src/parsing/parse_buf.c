/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_buf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 17:57:20 by glaguyon          #+#    #+#             */
/*   Updated: 2024/06/15 16:06:09 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "map.h"
#include "utils.h"

static int	check_textures(t_map *map, int hasfloor, int hasceil)
{
	if (!map->n.px)
		ft_perror("Missing north texture\n");
	else if (!map->s.px)
		ft_perror("Missing south texture\n");
	else if (!map->w.px)
		ft_perror("Missing west texture\n");
	else if (!map->e.px)
		ft_perror("Missing east texture\n");
	else if (!hasceil)
		ft_perror("Missing ceiling color\n");
	else if (!hasfloor)
		ft_perror("Missing floor color\n");
	return (!hasfloor || !hasceil || !map->n.px || !map->s.px
		|| !map->w.px || !map->e.px);
}

static char	*get_textures(void *mlx, t_map *map, char *buf)
{
	size_t	i;
	int		hasfloor;
	int		hasceil;

	i = 0;
	hasfloor = 0;
	hasceil = 0;
	while (buf[i] == '\n')
	{
		i++;
		hasfloor += buf[i] == 'F';
		hasceil += buf[i] == 'C';
		if (hasfloor > 1)
			ft_perror("Duplicate floor color\n");
		if (hasceil > 1)
			ft_perror("Duplicate ceiling color\n");
		if (hasfloor > 1 || hasceil > 1)
			return (NULL);
		if (try_load(mlx, map, buf, &i))
			return (NULL);
	}
	if (check_textures(map, hasfloor, hasceil))
		return (NULL);
	return (buf + i);
}

int	parse_buf(void *mlx, t_map *map, char *buf, size_t size)
{
	char	*start;

	start = get_textures(mlx, map, buf);
	if (start == NULL)
	{
		free(map->n.px);
		free(map->s.px);
		free(map->w.px);
		free(map->e.px);
		free(buf);
		return (1);
	}
	size -= (size_t)buf - (size_t)start;
	return (0);
}
