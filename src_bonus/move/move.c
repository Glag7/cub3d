/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 17:08:10 by glaguyon          #+#    #+#             */
/*   Updated: 2024/09/24 18:18:18 by glag             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <math.h>
#include "set.h"
#include "data.h"
#include "play.h"
#include "point.h"
#include "keys.h"

static inline __attribute__((always_inline)) t_point
	normvec(t_data *data, t_point vec, uint64_t keys, double delta)
{
	double	len;
	double	speed;

	if (keys & KEY_SPACE)
		speed = data->set.accelair;
	else
		speed = data->set.accel;
	if (keys & KEY_SHIFT)
		speed *= data->set.acceldiff;
	len = sqrt(vec.x * vec.x + vec.y * vec.y);
	if (len)
	{
		vec.x = vec.x / len * delta * speed;
		vec.y = vec.y / len * delta * speed;
	}
	return (vec);
}

static t_point	getmov(t_data *data, uint64_t keys, double delta)
{
	t_point	vec;

	vec = (t_point){0., 0.};
	if (keys & KEY_W)
	{
		vec.y -= data->play.sina;
		vec.x += data->play.cosa;
	}
	if (keys & KEY_S)
	{
		vec.y += data->play.sina;
		vec.x -= data->play.cosa;
	}
	if (keys & KEY_A)
	{
		vec.y -= data->play.cosa;
		vec.x -= data->play.sina;
	}
	if (keys & KEY_D)
	{
		vec.y += data->play.cosa;
		vec.x += data->play.sina;
	}
	return (normvec(data, vec, keys, delta));
}


static inline void	check_pos(t_data *data)
{
	if (data->play.x >= (double)data->map.wid)
		data->play.x = data->play.x - floor(data->play.x)
			+ (double)((int)floor(data->map.wid) % data->map.wid);
	else if (data->play.x < 0.)
		data->play.x = data->play.x - floor(data->play.x) + (double)data->map.wid
			+ (double)((int)floor(data->map.wid) % data->map.wid) -1.;
	if (data->play.y >= (double)data->map.hei)
		data->play.y = data->play.y - floor(data->play.y)
			+ (double)((int)floor(data->map.hei) % data->map.hei);
	else if (data->play.y < 0.)
		data->play.y = data->play.y - floor(data->play.y) + (double)data->map.hei
			+ (double)((int)floor(data->map.hei) % data->map.hei) -1.;
	if (data->play.a > M_PI)
		data->play.a -= 2. * M_PI;
	else if (data->play.a < -M_PI)
		data->play.a += 2. * M_PI;
	if (data->play.az > MAX_ANGLE)
		data->play.az = MAX_ANGLE;
	else if (data->play.az < MIN_ANGLE)
		data->play.az = MIN_ANGLE;
	if (data->play.z > 1.)
		data->play.z = 1.;
	else if (data->play.z < 0.)
		data->play.z = 0.;
	data->play.sina = sin(data->play.a);
	data->play.cosa = cos(data->play.a);
}

void	move(t_data *data, double delta, uint64_t keys)
{
	const t_point	vec = getmov(data, keys, delta);
	t_point		newpos;
	double		speed;

	speed = sqrt(data->play.vx * data->play.vx + data->play.vy * data->play.vy);
	if (data->keys & KEY_SHIFT)
		speed /= data->set.speeddiff;
	if (speed < data->set.speedmax || data->play.z > data->play.leglen)
	{
		data->play.vx += vec.x;
		data->play.vy += vec.y;
	}
	newpos.x = data->play.x;
	newpos.y = data->play.y;
	speed = sqrt(data->play.vx * data->play.vx + data->play.vy * data->play.vy);
	if (data->keys & KEY_SHIFT)
		speed /= data->set.speeddiff;
	if (newpos.x >= (double)data->map.wid)
		newpos.x -= (double)data->map.wid;
	else if (newpos.x < 0.)
		newpos.x += (double)data->map.wid;
	if (newpos.y >= (double)data->map.hei)
		newpos.y -= (double)data->map.hei;
	else if (newpos.y < 0.)
		newpos.y += (double)data->map.hei;
	speed = sqrt(data->play.vx * data->play.vx + data->play.vy * data->play.vy);
	if (((speed && vec.x == 0. && vec.y == 0.) || speed > data->set.speedmax))
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
	newpos.x += data->play.vx * delta;
	newpos.y += data->play.vy * delta;
	data->play.x = newpos.x;
	data->play.y = newpos.y;

	//TODO accel air
	//FIXME jump is weird
	//XXX use leglen everywhere
	//garder espace appuyer pour sauter plus longtemps
	if (keys & KEY_CTRL && data->play.leglen > .25)
		data->play.leglen -= (.25 / .05) * delta;
	else if (!(keys & KEY_CTRL) && data->play.leglen < .5)
		data->play.leglen += (.25 / .05) * delta;
	if (data->play.leglen < .25)
		data->play.leglen = .25;
	if (data->play.leglen > .5)
		data->play.leglen = .5;
	if (data->play.leglen > data->play.z)
	{
		data->play.z = data->play.leglen;
		data->play.vz = 0.;
	}
	if (fabs(data->play.leglen - data->play.z) < 1e-3 && (keys & KEY_SPACE))
	{
		data->play.vz += .05;//delta ?
	}
	else if (data->play.z > data->play.leglen)
		data->play.vz -= .1 * delta;
	data->play.z += data->play.vz;
	if (data->play.leglen > data->play.z)
	{
		data->play.z = data->play.leglen;
		data->play.vz = 0.;
	}
	check_pos(data);
}
