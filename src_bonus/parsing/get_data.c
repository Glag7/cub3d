/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 16:42:38 by glaguyon          #+#    #+#             */
/*   Updated: 2024/08/06 19:11:05 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stddef.h>
#include "map.h"
#include "data.h"
#include "err.h"
#include "utils.h"

static inline int	valid_char(char c)
{
	return (c == '0' || c == '1' || c == ' ' || c == 'X'
		|| c == 'U' || c == 'D' || c == 'L' || c == 'R');
}

static inline int	parse_char(char *c, double x, double y, t_data *d)
{
	if ((*c == 'N' || *c == 'S' || *c == 'W' || *c == 'E') && d->play.x != -1)
	{
		ft_perror(ERR_MOREPLAYER);
		return (1);
	}
	if (*c == 'N')
		d->play.a = M_PI_2;
	else if (*c == 'W')
		d->play.a = M_PI;
	else if (*c == 'S')
		d->play.a = -M_PI_2;
	else if (*c == 'E')
		d->play.a = 0;
	if (*c == 'N' || *c == 'S' || *c == 'W' || *c == 'E')
	{
		*c = '0';
		d->play.x = x + 0.5;
		d->play.y = y + 0.5;
	}
	else if (!valid_char(*c))
	{
		ft_perror(ERR_BADCHAR);
		return (1);
	}
	return (0);
}

int	get_data(char *buf, t_data *data)
{
	size_t	i;

	data->play.x = -1.;
	while (*buf)
	{
		i = 0;
		while (buf[i] && buf[i] != '\n')
		{
			if (parse_char(buf + i, (double)i, (double)data->map.hei, data))
				return (1);
			++i;
		}
		++(data->map.hei);
		if (i > data->map.wid)
			data->map.wid = i;
		buf += i + (buf[i] == '\n');
	}
	if (data->play.x == -1)
	{
		ft_perror(ERR_NOPLAYER);
		return (1);
	}
	return (0);
}
