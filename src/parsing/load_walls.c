/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 16:32:28 by glaguyon          #+#    #+#             */
/*   Updated: 2024/06/15 20:01:42 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "map.h"
#include "err.h"
#include "utils.h"
#include "parsing.h"

int	load_no(void *mlx, t_map *map, char *buf, size_t *i)
{
	size_t	j;
	char	c;

	if (map->n.px)
	{
		ft_perror(ERR_DUP_NO);
		return (1);
	}
	*i += 2;
	while (buf[*i] == ' ')
		(*i)++;
	j = *i;
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

	if (map->s.px)
	{
		ft_perror(ERR_DUP_SO);
		return (1);
	}
	*i += 2;
	while (buf[*i] == ' ')
		(*i)++;
	j = *i;
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

	if (map->w.px)
	{
		ft_perror(ERR_DUP_WE);
		return (1);
	}
	*i += 2;
	while (buf[*i] == ' ')
		(*i)++;
	j = *i;
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

	if (map->e.px)
	{
		ft_perror(ERR_DUP_EA);
		return (1);
	}
	*i += 2;
	while (buf[*i] == ' ')
		(*i)++;
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
