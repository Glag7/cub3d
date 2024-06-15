/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 16:32:28 by glaguyon          #+#    #+#             */
/*   Updated: 2024/06/15 18:02:22 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "map.h"

int	load_no(void *mlx, t_map *map, char *buf, size_t *i)
{
	size_t	j;
	char	c;

	j = *i + 2;
	while (buf[j] && buf[j] != '\n')
		j++;
	c = buf[j];
	buf[j] = 0;
	if (load_img(mlx, buf + *i, &map->n))
		return (1);
	buf[j] = c;
	*i = j;
	return (0);
}

int	load_so(void *mlx, t_map *map, char *buf, size_t *i)
{
	size_t	j;
	char	c;

	j = *i + 2;
	while (buf[j] && buf[j] != '\n')
		j++;
	c = buf[j];
	buf[j] = 0;
	if (load_img(mlx, buf + *i, &map->s))
		return (1);
	buf[j] = c;
	*i = j;
	return (0);
}

int	load_we(void *mlx, t_map *map, char *buf, size_t *i)
{
	size_t	j;
	char	c;

	j = *i + 2;
	while (buf[j] && buf[j] != '\n')
		j++;
	c = buf[j];
	buf[j] = 0;
	if (load_img(mlx, buf + *i, &map->w))
		return (1);
	buf[j] = c;
	*i = j;
	return (0);
}

int	load_ea(void *mlx, t_map *map, char *buf, size_t *i)
{
	size_t	j;
	char	c;

	j = *i;
	while (buf[j] && buf[j] != '\n')
		j++;
	c = buf[j];
	buf[j] = 0;
	if (load_img(mlx, buf + *i, &map->e))
		return (1);
	buf[j] = c;
	*i = j;
	return (0);
}
