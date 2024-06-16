/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_floorceil.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 16:53:12 by glaguyon          #+#    #+#             */
/*   Updated: 2024/06/15 19:43:30 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stddef.h>
#include "map.h"
#include "err.h"
#include "utils.h"

static uint8_t	atocolor(char *buf, int *err, size_t *i_glob)
{
	size_t		i;
	uint32_t	color;

	i = 0;
	color = 0;
	while (buf[i] >= '0' && buf[i] <= '9')
	{
		color = color * 10 + buf[i] - '0';
		if (color > 255)
		{
			*err = 1;
			break ;
		}
		i++;
	}
	if (i == 0)
		*err = 1;
	*i_glob += i;
	return (color);
}

static int	atorgb(char *buf, uint32_t *rgb, size_t *i)
{
	int	err;

	err = 0;
	while (buf[*i] == ' ')
		(*i)++;
	*rgb = atocolor(buf + *i, &err, i) << 16;
	while (buf[*i] == ' ')
		(*i)++;
	if (buf[(*i)++] != ',' || err)
		return (1);
	while (buf[*i] == ' ')
		(*i)++;
	*rgb |= atocolor(buf + *i, &err, i) << 8;
	while (buf[*i] == ' ')
		(*i)++;
	if (buf[(*i)++] != ',' || err)
		return (1);
	while (buf[*i] == ' ')
		(*i)++;
	*rgb |= atocolor(buf + *i, &err, i);
	while (buf[*i] == ' ')
		(*i)++;
	if (buf[*i] != '\n' || err)
		return (1);
	return (0);
}

int	load_floor(void *mlx, t_map *map, char *buf, size_t *i)
{
	uint32_t	rgb;

	(void)mlx;
	(*i)++;
	if (atorgb(buf, &rgb, i))
	{
		ft_perror(ERR_BAD_FLOOR);
		return (1);
	}
	map->floor = rgb;
	return (0);
}

int	load_ceil(void *mlx, t_map *map, char *buf, size_t *i)
{
	uint32_t	rgb;

	(void)mlx;
	(*i)++;
	if (atorgb(buf, &rgb, i))
	{
		ft_perror(ERR_BAD_CEIL);
		return (1);
	}
	map->ceil = rgb;
	return (0);
}
