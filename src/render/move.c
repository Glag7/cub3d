/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 17:08:10 by glaguyon          #+#    #+#             */
/*   Updated: 2024/06/21 17:52:41 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <math.h>
#include "map.h"
#include "keys.h"

static inline void	check_angle(double *a)
{
	if (*a > M_PI)
		*a -= 2. * M_PI;
	else if (*a < -M_PI)
		*a += 2. * M_PI;
}

void	move(t_map *map, uint64_t keys)
{
	if (keys & KEY_W)
	{
		map->player.y += .05 * sin(map->player.a);
		map->player.x += .05 * cos(map->player.a);
	}
	if (keys & KEY_S)
	{
		map->player.y -= .05 * sin(map->player.a);
		map->player.x -= .05 * cos(map->player.a);
	}
	if (keys & KEY_A)
	{
		map->player.y -= .05 * cos(map->player.a);
		map->player.x -= .05 * sin(map->player.a);
	}
	if (keys & KEY_D)
	{
		map->player.y += .05 * cos(map->player.a);
		map->player.x += .05 * sin(map->player.a);
	}
	if (keys & KEY_LEFT)
		map->player.a -= .005;
	if (keys &KEY_RIGHT)
		map->player.a += .005;
	check_angle(&map->player.a);
}
