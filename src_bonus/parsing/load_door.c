/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_door.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 16:03:40 by glaguyon          #+#    #+#             */
/*   Updated: 2024/08/06 16:14:39 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tex.h"
#include "map.h"
#include "err.h"
#include "utils.h"
#include "parsing.h"

int	load_door(void *mlx, t_data *data, char *buf, unsigned int *i)
{
	unsigned int	j;
	char			c;

	if (data->map.d.px)
		ft_perror(ERR_DUP_DOOR);
	if (data->map.d.px)
		return (1);
	if (i)
	{
		*i += 2;
		while (buf[*i] == ' ')
			(*i)++;
		j = *i;
		while (buf[j] && buf[j] != '\n')
			j++;
		c = buf[j];
		buf[j] = 0;
		if (load_img(mlx, buf + *i, &data->map.d,
				(t_dim){data->set.texsiz, data->set.texsiz}))
			return (1);
		buf[j] = c;
		*i = j;
	}
	else if (load_img(mlx, TEX_DOOR, &data->map.d,
				(t_dim){data->set.texsiz, data->set.texsiz}))
		return (1);
	return (0);
}
