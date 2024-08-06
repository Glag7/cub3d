/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_floorceil.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 16:53:12 by glaguyon          #+#    #+#             */
/*   Updated: 2024/08/06 17:14:58 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdint.h>
#include "map.h"
#include "err.h"
#include "utils.h"
#include "parsing.h"

static uint32_t	atocolor(char *buf, int *err, unsigned int *i_glob)
{
	unsigned int	i;
	uint32_t		color;

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

static int	atorgb(char *buf, uint32_t *rgb, unsigned int *i)
{
	int	err;

	err = 0;
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

int	load_floor(void *mlx, t_data *data, char *buf, unsigned int *i)
{
	uint32_t	rgb;
	unsigned int	j;
	char			c;

	if (data->map.f.px)
	{
		ft_perror(ERR_DUP_FLOOR);
		return (1);
	}
	(*i)++;
	while (buf[*i] == ' ')
		(*i)++;
	j = *i;
	while (buf[j] && buf[j] != '\n' && buf[j] != '/')
		j++;
	if (buf[j] == '/')
	{
		j = *i;
		while (buf[j] && buf[j] != '\n')
			j++;
		c = buf[j];
		buf[j] = 0;
		if (load_img(mlx, buf + *i, &data->map.f,
				(t_dim){data->set.texsiz, data->set.texsiz}))
			return (1);
		buf[j] = c;
		*i = j;
		return (0);
	}
	if (atorgb(buf, &rgb, i))
	{
		ft_perror(ERR_BAD_CEIL);
		return (1);
	}
	data->map.f.px = malloc(sizeof(uint32_t));
	if (data->map.f.px == NULL)
	{
		ft_perror(ERR_MALLOC);
		return (1);
	}
	data->map.f.px[0] = rgb;
	data->map.f.w = 1;
	data->map.f.h = 1;
	return (0);
}

int	load_ceil(void *mlx, t_data *data, char *buf, unsigned int *i)
{
	uint32_t	rgb;
	unsigned int	j;
	char			c;

	if (data->map.c.px)
	{
		ft_perror(ERR_DUP_CEIL);
		return (1);
	}
	(*i)++;
	while (buf[*i] == ' ')
		(*i)++;
	j = *i;
	while (buf[j] && buf[j] != '\n' && buf[j] != '/')
		j++;
	if (buf[j] == '/')
	{
		j = *i;
		while (buf[j] && buf[j] != '\n')
			j++;
		c = buf[j];
		buf[j] = 0;
		if (load_img(mlx, buf + *i, &data->map.c,
				(t_dim){data->set.texsiz, data->set.texsiz}))
			return (1);
		buf[j] = c;
		*i = j;
		return (0);
	}
	if (atorgb(buf, &rgb, i))
	{
		ft_perror(ERR_BAD_CEIL);
		return (1);
	}
	data->map.c.px = malloc(sizeof(uint32_t));
	if (data->map.c.px == NULL)
	{
		ft_perror(ERR_MALLOC);
		return (1);
	}
	data->map.c.px[0] = rgb;
	data->map.c.w = 1;
	data->map.c.h = 1;
	return (0);
}
