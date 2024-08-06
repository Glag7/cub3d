/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_floorceil.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 16:53:12 by glaguyon          #+#    #+#             */
/*   Updated: 2024/08/06 18:59:08 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdint.h>
#include "map.h"
#include "err.h"
#include "utils.h"
#include "parsing.h"

#define FLOOR 0
#define CEIL 1

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

static int	load_floorceil_img(t_data *data,
	char *buf, unsigned int *i, int floorceil)
{
	unsigned int	j;
	char			c;
	size_t			size;
	t_img			*img;

	j = *i;
	while (buf[j] && buf[j] != '\n')
		j++;
	c = buf[j];
	buf[j] = 0;
	if (floorceil == CEIL)
	{
		size = data->set.skysiz;
		img = &data->map.c;
	}
	else
	{
		size = data->set.texsiz;
		img = &data->map.f;
	}
	if (load_img(data->mlx.mlx, buf + *i, img, (t_dim){size, size}))
		return (1);
	buf[j] = c;
	*i = j;
	return (0);
}

int	load_ceil(t_data *data, char *buf, unsigned int *i)
{
	uint32_t		rgb;
	unsigned int	j;

	if (data->map.c.px)
		ft_perror(ERR_DUP_CEIL);
	if (data->map.c.px)
		return (1);
	while (buf[*i + 1] == ' ')
		(*i)++;
	j = ++(*i);
	while (buf[j] && buf[j] != '\n' && buf[j] != '/')
		j++;
	if (buf[j] == '/')
		return (load_floorceil_img(data, buf, i, CEIL));
	if (atorgb(buf, &rgb, i))
	{
		ft_perror(ERR_BAD_CEIL);
		return (1);
	}
	data->map.c = (t_img){malloc(sizeof(uint32_t)), 1, 1};
	if (data->map.c.px == NULL)
		ft_perror(ERR_MALLOC);
	else
		data->map.c.px[0] = rgb;
	return (data->map.c.px == NULL);
}

int	load_floor(t_data *data, char *buf, unsigned int *i)
{
	uint32_t		rgb;
	unsigned int	j;

	if (data->map.f.px)
		ft_perror(ERR_DUP_FLOOR);
	if (data->map.f.px)
		return (1);
	while (buf[*i + 1] == ' ')
		(*i)++;
	j = ++(*i);
	while (buf[j] && buf[j] != '\n' && buf[j] != '/')
		j++;
	if (buf[j] == '/')
		return (load_floorceil_img(data, buf, i, FLOOR));
	if (atorgb(buf, &rgb, i))
	{
		ft_perror(ERR_BAD_CEIL);
		return (1);
	}
	data->map.f = (t_img){malloc(sizeof(uint32_t)), 1, 1};
	if (data->map.f.px == NULL)
		ft_perror(ERR_MALLOC);
	else
		data->map.f.px[0] = rgb;
	return (data->map.f.px == NULL);
}
