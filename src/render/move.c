/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 17:08:10 by glaguyon          #+#    #+#             */
/*   Updated: 2024/06/27 15:26:24 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <math.h>
#include "data.h"
#include "play.h"
#include "keys.h"

static inline void	check_pos(t_data *data)
{
	if (data->play.x >= (double)data->map.wid)
		data->play.x -= (double)data->map.wid;
	else if (data->play.x < 0.)
		data->play.x += (double)data->map.wid;
	if (data->play.y >= (double)data->map.hei)
		data->play.x -= (double)data->map.hei;
	else if (data->play.y < 0.)
		data->play.y += (double)data->map.hei;
	if (data->play.a > M_PI)
		data->play.a -= 2. * M_PI;
	else if (data->play.a < -M_PI)
		data->play.a += 2. * M_PI;
	data->play.sina = sin(data->play.a);
	data->play.cosa = cos(data->play.a);
}

void	move(t_data *data, float delta, uint64_t keys)
{
	if (keys & KEY_W)
	{
		data->play.y -= 1. * sin(data->play.a) * delta;
		data->play.x += 1. * cos(data->play.a) * delta;
	}
	if (keys & KEY_S)
	{
		data->play.y += 1. * sin(data->play.a) * delta;
		data->play.x -= 1. * cos(data->play.a) * delta;
	}
	if (keys & KEY_A)
	{
		data->play.y -= 1. * cos(data->play.a) * delta;
		data->play.x -= 1. * sin(data->play.a) * delta;
	}
	if (keys & KEY_D)
	{
		data->play.y += 1. * cos(data->play.a) * delta;
		data->play.x += 1. * sin(data->play.a) * delta;
	}
	if (keys & KEY_LEFT)
		data->play.a += 1. * delta;
	if (keys & KEY_RIGHT)
		data->play.a -= 1. * delta;
	check_pos(data);
}
