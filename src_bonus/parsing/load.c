/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 15:34:19 by glaguyon          #+#    #+#             */
/*   Updated: 2024/09/03 17:26:45 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"
#include "map.h"
#include "parsing.h"

int	try_load(void *mlx, t_data *dat, char *buf, unsigned int *i_)
{
	unsigned int	i;

	i = *i_;
	if (buf[i] == 'N' && buf[i + 1] == 'O' && load_no(mlx, dat, buf, &i))
		return (1);
	else if (buf[i] == 'S' && buf[i + 1] == 'O' && load_so(mlx, dat, buf, &i))
		return (1);
	else if (buf[i] == 'W' && buf[i + 1] == 'E' && load_we(mlx, dat, buf, &i))
		return (1);
	else if (buf[i] == 'E' && buf[i + 1] == 'A' && load_ea(mlx, dat, buf, &i))
		return (1);
	else if (buf[i] == 'F' && load_floor(dat, buf, &i))
		return (1);
	else if (buf[i] == 'C' && load_ceil(dat, buf, &i))
		return (1);
	else if (buf[i] == 'D' && buf[i + 1] == 'O' && load_door(mlx, dat, buf, &i))
		return (1);
	else if (buf[i] == 'G' && buf[i + 1] == 'L'
		&& load_glass(mlx, dat, buf, &i))
		return (1);
	else if (buf[i] == 'T' && buf[i + 1] == 'B'
		&& load_topbottom(mlx, dat, buf, &i))
		return (1);
	*i_ = i;
	return (0);
}
