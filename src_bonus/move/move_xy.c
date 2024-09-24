/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_xy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glag <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 19:47:47 by glag              #+#    #+#             */
/*   Updated: 2024/09/24 20:11:14 by glag             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "set.h"
#include "data.h"
#include "play.h"
#include "point.h"
#include "keys.h"

static void	friction(t_data *data, double speed, double delta)
{
	if (data->play.z > data->play.leglen)
	{
		data->play.vx = data->play.vx * pow(data->set.slowerair, delta / pow(speed / data->set.speedmax, .1));
		data->play.vy = data->play.vy * pow(data->set.slowerair, delta / pow(speed / data->set.speedmax, .1));
	}
	else
	{
		data->play.vx = data->play.vx * pow(data->set.slower, delta / pow(speed / data->set.speedmax, .1));
		data->play.vy = data->play.vy * pow(data->set.slower, delta / pow(speed / data->set.speedmax, .1));
	}
}

void	move_xy(t_data *data, double delta, int stopped)
{
	t_point	newpos;
	double		speed = sqrt(data->play.vx * data->play.vx
			+ data->play.vy * data->play.vy);

	if ((stopped || speed > data->set.speedmax))
		friction(data, speed, delta);
	newpos.x = data->play.x;
	newpos.y = data->play.y;
	newpos.x += data->play.vx * delta;
	newpos.y += data->play.vy * delta;
	if (newpos.x >= (double)data->map.wid)
		newpos.x = newpos.x - floor(newpos.x)
			+ (double)((int)floor(data->map.wid) % data->map.wid);
	else if (newpos.x < 0.)
		newpos.x = newpos.x - floor(newpos.x) + (double)data->map.wid
			+ (double)((int)floor(data->map.wid) % data->map.wid) - 1.;
	if (newpos.y >= (double)data->map.hei)
		newpos.y = newpos.y - floor(newpos.y)
			+ (double)((int)floor(data->map.hei) % data->map.hei);
	else if (newpos.y < 0.)
		newpos.y = newpos.y - floor(newpos.y) + (double)data->map.hei
			+ (double)((int)floor(data->map.hei) % data->map.hei) - 1.;
	data->play.x = newpos.x;
	data->play.y = newpos.y;
}
