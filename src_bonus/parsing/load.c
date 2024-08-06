/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 15:34:19 by glaguyon          #+#    #+#             */
/*   Updated: 2024/08/06 18:35:51 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"
#include "map.h"
#include "parsing.h"

int	try_load(void *mlx, t_data *data, char *buf, unsigned int *i_)
{
	unsigned int	i;

	i = *i_;
	if (buf[i] == 'N' && buf[i + 1] == 'O' && load_no(mlx, data, buf, &i))
		return (1);
	else if (buf[i] == 'S' && buf[i + 1] == 'O' && load_so(mlx, data, buf, &i))
		return (1);
	else if (buf[i] == 'W' && buf[i + 1] == 'E' && load_we(mlx, data, buf, &i))
		return (1);
	else if (buf[i] == 'E' && buf[i + 1] == 'A' && load_ea(mlx, data, buf, &i))
		return (1);
	else if (buf[i] == 'F' && load_floor(data, buf, &i))
		return (1);
	else if (buf[i] == 'C' && load_ceil(data, buf, &i))
		return (1);
	else if (buf[i] == 'D' && load_door(mlx, data, buf, &i))
		return (1);
	*i_ = i;
	return (0);
}
