/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_xy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glag <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 19:47:47 by glag              #+#    #+#             */
/*   Updated: 2024/10/10 01:16:02 by glag             ###   ########.fr       */
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

static t_point	check_bounds(t_data *data, t_point pos)
{
	if (pos.x >= (double)data->map.wid)
		pos.x = pos.x - floor(pos.x)
			+ (double)((int)floor(data->map.wid) % data->map.wid);
	else if (pos.x < 0.)
		pos.x = pos.x - floor(pos.x) + (double)data->map.wid
			+ (double)((int)floor(data->map.wid) % data->map.wid) - 1.;
	if (pos.y >= (double)data->map.hei)
		pos.y = pos.y - floor(pos.y)
			+ (double)((int)floor(data->map.hei) % data->map.hei);
	else if (pos.y < 0.)
		pos.y = pos.y - floor(pos.y) + (double)data->map.hei
			+ (double)((int)floor(data->map.hei) % data->map.hei) - 1.;
	return (pos);
}

static double	check_wallsx(t_data *data, double newpos, double dir)
{
	double	endpos;
	t_ipoint	ipos;
	t_point		fpos;
	int		map;

	endpos = newpos + dir * FAT;
	endpos = check_bounds(data, (t_point){endpos, 0}).x;
	ipos = (t_ipoint){endpos, data->play.y};
	fpos = (t_point){endpos - ipos.x, data->play.y - ipos.y};
	map = data->map.map[(long long)(ipos.x + ipos.y * data->map.wid)];
	if (map & CUBE)
		newpos = floor(endpos) + (dir < 0.) - dir * FAT;
	else if ((map & SIDE) && (map & SPEC) && floor(data->play.x) == ipos.x 
		&& ((fpos.x - .5 + dir * .05) * dir > 0.) ^ (((data->play.x - floor(data->play.x)) - .5 + dir * .05) * dir > 0.)
		&& ((map & SPEC) == GLASS
			|| ((map & SPEC) == DOOR && fpos.y < 1. - (double)((map & VALUE) >> VALUEOFF) / VALUEONE)
			|| (((map & SPEC) == FENCE) && fabs(data->play.z - (double)((map & VALUE) >> VALUEOFF) / VALUEONE) < .75)))
		newpos = floor(endpos) + .5 - dir * .05 - dir * FAT;
	else if (!(map & SIDE) && (map & SPEC)
		&& fpos.y >= .45 && fpos.y <= .55
		&& ((map & SPEC) == GLASS
			|| ((map & SPEC) == DOOR && fpos.x < 1. - (double)((map & VALUE) >> VALUEOFF) / VALUEONE)
			|| (((map & SPEC) == FENCE) && fabs(data->play.z - (double)((map & VALUE) >> VALUEOFF) / VALUEONE) < .75)))
		newpos = floor(endpos) + (dir < 0.) - dir * FAT - ((map & SPEC) == DOOR && dir < 0.) * (double)((map & VALUE) >> VALUEOFF) / VALUEONE;
	return (newpos);
}

void	move_xy(t_data *data, double delta, int stopped)
{
	const double	speed = sqrt(data->play.vx * data->play.vx
			+ data->play.vy * data->play.vy);
	t_point			newpos;
	t_point			dir;

	if ((stopped || speed > data->set.speedmax))
		friction(data, speed, delta);
	newpos.x = data->play.x;
	newpos.y = data->play.y;
	newpos.x += data->play.vx * delta;
	newpos.y += data->play.vy * delta;
	newpos = check_bounds(data, newpos);
	dir = (t_point){(data->play.vx)
		/ fabs(data->play.vx),
		(data->play.vy)
		/ fabs(data->play.vy)};
	if (!isnan(dir.x))
		newpos.x = check_wallsx(data, newpos.x, dir.x);//yutiliser nouveau x ?
	data->play.x = newpos.x;
	data->play.y = newpos.y;
}
