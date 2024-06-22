/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 17:08:10 by glaguyon          #+#    #+#             */
/*   Updated: 2024/06/22 17:03:01 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <math.h>
#include "play.h"
#include "keys.h"

static inline void	check_angle(double *a)
{
	if (*a > M_PI)
		*a -= 2. * M_PI;
	else if (*a < -M_PI)
		*a += 2. * M_PI;
}

void	move(t_play *play, uint64_t keys)
{
	if (keys & KEY_W)
	{
		play->y += .05 * sin(play->a);
		play->x += .05 * cos(play->a);
	}
	if (keys & KEY_S)
	{
		play->y -= .05 * sin(play->a);
		play->x -= .05 * cos(play->a);
	}
	if (keys & KEY_A)
	{
		play->y -= .05 * cos(play->a);
		play->x -= .05 * sin(play->a);
	}
	if (keys & KEY_D)
	{
		play->y += .05 * cos(play->a);
		play->x += .05 * sin(play->a);
	}
	if (keys & KEY_LEFT)
		play->a -= .005;
	if (keys &KEY_RIGHT)
		play->a += .005;
	check_angle(&play->a);
}
