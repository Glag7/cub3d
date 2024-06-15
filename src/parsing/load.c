/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 15:34:19 by glaguyon          #+#    #+#             */
/*   Updated: 2024/06/15 15:58:15 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "map.h"

int	try_load(void *mlx, t_map *map, char *buf, size_t *i_)
{
	size_t	i;

	i = *i_;
	if (buf[i] == 'N' && buf[i + 1] == 'O' && load_no(mlx, map, buf, &i))
		return (1);
	else if (buf[i] == 'S' && buf[i + 1] == 'O' && load_so(mlx, map, buf, &i))
		return (1);
	else if (buf[i] == 'W' && buf[i + 1] == 'E' && load_we(mlx, map, buf, &i))
		return (1);
	else if (buf[i] == 'E' && buf[i + 1] == 'A' && load_ea(mlx, map, buf, &i))
		return (1);
	else if (buf[i] == 'F' && load_floor(mlx, map, buf, &i))
		return (1);
	else if (buf[i] == 'C' && load_ceil(mlx, map, buf, &i))
		return (1);
	return (0);
}
