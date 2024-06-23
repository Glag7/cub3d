/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 17:08:10 by glaguyon          #+#    #+#             */
/*   Updated: 2024/06/23 16:02:06 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <math.h>
#include "play.h"
#include "keys.h"

static inline void	check_angle(t_play *play)
{
	if (play->a > M_PI)
		play->a -= 2. * M_PI;
	else if (play->a < -M_PI)
		play->a += 2. * M_PI;
	play->sina = sin(play->a);
	play->cosa = cos(play->a);
}

void	move(t_play *play, uint64_t keys)
{
	if (keys & KEY_W)
	{
		play->y -= .005 * sin(play->a);
		play->x += .005 * cos(play->a);
	}
	if (keys & KEY_S)
	{
		play->y += .005 * sin(play->a);
		play->x -= .005 * cos(play->a);
	}
	if (keys & KEY_A)
	{
		play->y -= .005 * cos(play->a);
		play->x -= .005 * sin(play->a);
	}
	if (keys & KEY_D)
	{
		play->y += .005 * cos(play->a);
		play->x += .005 * sin(play->a);
	}
	if (keys & KEY_LEFT)
		play->a += .005;
	if (keys & KEY_RIGHT)
		play->a -= .005;
	check_angle(play);
}
