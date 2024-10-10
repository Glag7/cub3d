/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_xy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glag <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 19:47:47 by glag              #+#    #+#             */
/*   Updated: 2024/10/10 02:54:34 by glag             ###   ########.fr       */
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

static double	check_wallsx(t_data *data, double endpos, double dir)
{
	const t_ipoint	ipos = (t_ipoint){endpos, data->play.y};
	const t_point	fpos = (t_point){endpos - ipos.x, data->play.y - ipos.y};
	const int		map = data->map.map[(long long)(ipos.x
			+ ipos.y * data->map.wid)];
	const double	mval = (double)((map & VALUE) >> VALUEOFF) / VALUEONE;

	if (map & CUBE)
		return (floor(endpos) + (dir < 0.) - dir * FAT);
	if ((map & SIDE) && (map & SPEC) && floor(data->play.x) == ipos.x
		&& ((fpos.x - .5 + dir * .05) * dir > 0.)
		^ (((data->play.x - floor(data->play.x)) - .5 + dir * .05) * dir > 0.)
		&& ((map & SPEC) == GLASS
			|| ((map & SPEC) == DOOR && fpos.y < 1. - mval)
			|| (((map & SPEC) == FENCE) && fabs(data->play.z - mval) < .75)))
		return (floor(endpos) + .5 - dir * .05 - dir * FAT);
	if (!(map & SIDE) && (map & SPEC)
		&& fpos.y >= .45 && fpos.y <= .55
		&& ((map & SPEC) == GLASS
			|| ((map & SPEC) == DOOR && fpos.x < 1. - mval)
			|| (((map & SPEC) == FENCE) && fabs(data->play.z - mval) < .75)))
		return (floor(endpos) + (dir < 0.) - dir * FAT
			- ((map & SPEC) == DOOR && dir < 0.) * mval);
	return (endpos - dir * FAT);
}

static double	check_wallsy(t_data *data, double endpos, double dir)
{
	const t_ipoint	ipos = (t_ipoint){data->play.x, endpos};
	const t_point	fpos = (t_point){data->play.x - ipos.x, endpos - ipos.y};
	const int		map = data->map.map[(long long)(ipos.x
			+ ipos.y * data->map.wid)];
	const double	mval = (double)((map & VALUE) >> VALUEOFF) / VALUEONE;

	if (map & CUBE)
		return (floor(endpos) + (dir < 0.) - dir * FAT);
	if (!(map & SIDE) && (map & SPEC) && floor(data->play.y) == ipos.y
		&& ((fpos.y - .5 + dir * .05) * dir > 0.)
		^ (((data->play.y - floor(data->play.y)) - .5 + dir * .05) * dir > 0.)
		&& ((map & SPEC) == GLASS
			|| ((map & SPEC) == DOOR && fpos.x < 1. - mval)
			|| (((map & SPEC) == FENCE) && fabs(data->play.z - mval) < .75)))
		return (floor(endpos) + .5 - dir * .05 - dir * FAT);
	if ((map & SIDE) && (map & SPEC)
		&& fpos.x >= .45 && fpos.x <= .55
		&& ((map & SPEC) == GLASS
			|| ((map & SPEC) == DOOR && fpos.y < 1. - mval)
			|| (((map & SPEC) == FENCE) && fabs(data->play.z - mval) < .75)))
		return (floor(endpos) + (dir < 0.) - dir * FAT
			- ((map & SPEC) == DOOR && dir < 0.) * mval);
	return (endpos - dir * FAT);
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
		newpos.x = check_wallsx(data, check_bounds(data, (t_point){newpos.x + dir.x * FAT, 0}).x, dir.x);
	if (!isnan(dir.y))
		newpos.y = check_wallsy(data, check_bounds(data, (t_point){0, newpos.y + dir.y * FAT}).y, dir.y);
	data->play.x = newpos.x;
	data->play.y = newpos.y;
}
