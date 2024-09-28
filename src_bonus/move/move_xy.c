/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_xy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glag <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 19:47:47 by glag              #+#    #+#             */
/*   Updated: 2024/09/26 04:34:50 by glag             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "set.h"
#include "data.h"
#include "play.h"
#include "point.h"
#include "keys.h"
#include "move.h"

static void	friction(t_data *data, double speed, double delta)
{
	if (data->play.z > data->play.leglen)
	{
		data->play.vx = data->play.vx * pow(data->set.slowerair,
				delta / pow(speed / data->set.speedmax, .1));
		data->play.vy = data->play.vy * pow(data->set.slowerair,
				delta / pow(speed / data->set.speedmax, .1));
	}
	else
	{
		data->play.vx = data->play.vx * pow(data->set.slower,
				delta / pow(speed / data->set.speedmax, .1));
		data->play.vy = data->play.vy * pow(data->set.slower,
				delta / pow(speed / data->set.speedmax, .1));
	}
}

void	move_xy(t_data *data, double delta, int stopped)
{
	const double	speed = sqrt(data->play.vx * data->play.vx
			+ data->play.vy * data->play.vy);
	t_point			newpos;

	if ((stopped || speed > data->set.speedmax))
		friction(data, speed, delta);
	newpos = raycast_newpos(data);
	data->play.x = newpos.x;
	data->play.y = newpos.y;
}
