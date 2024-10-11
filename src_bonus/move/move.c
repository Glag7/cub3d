/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 17:08:10 by glaguyon          #+#    #+#             */
/*   Updated: 2024/10/11 02:05:31 by glag             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <math.h>
#include "set.h"
#include "data.h"
#include "play.h"
#include "point.h"
#include "keys.h"
#include "move.h"

static inline __attribute__((always_inline)) t_point
	normvec(t_data *data, t_point vec, uint64_t keys, double delta)
{
	double	len;
	double	speed;

	if (data->play.z > data->play.leglen)
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

static inline void	check_pos(t_data *dat)
{
	if (dat->play.x >= (double)dat->map.wid)
		dat->play.x = dat->play.x - floor(dat->play.x)
			+ (double)((int)floor(dat->map.wid) % dat->map.wid);
	else if (dat->play.x < 0.)
		dat->play.x = dat->play.x - floor(dat->play.x) + (double)dat->map.wid
			+ (double)((int)floor(dat->map.wid) % dat->map.wid) - 1.;
	if (dat->play.y >= (double)dat->map.hei)
		dat->play.y = dat->play.y - floor(dat->play.y)
			+ (double)((int)floor(dat->map.hei) % dat->map.hei);
	else if (dat->play.y < 0.)
		dat->play.y = dat->play.y - floor(dat->play.y) + (double)dat->map.hei
			+ (double)((int)floor(dat->map.hei) % dat->map.hei) - 1.;
	if (dat->play.a > M_PI)
		dat->play.a -= 2. * M_PI;
	else if (dat->play.a < -M_PI)
		dat->play.a += 2. * M_PI;
	if (dat->play.az > MAX_ANGLE)
		dat->play.az = MAX_ANGLE;
	else if (dat->play.az < MIN_ANGLE)
		dat->play.az = MIN_ANGLE;
	if (dat->play.z > 1.)
		dat->play.z = 1.;
	dat->play.sina = sin(dat->play.a);
	dat->play.cosa = cos(dat->play.a);
}

static void	move_z(t_data *data, double delta, uint64_t keys)
{
	if (keys & KEY_CTRL && data->play.leglen > .25)
		data->play.leglen -= (.25 / .05) * delta;
	else if (!(keys & KEY_CTRL) && data->play.leglen < .5)
		data->play.leglen += (.25 / .05) * delta;
	if (data->play.leglen < .25)
		data->play.leglen = .25;
	else if (data->play.leglen > .5)
		data->play.leglen = .5;
	if (data->play.leglen > data->play.z)
	{
		data->play.z = data->play.leglen;
		data->play.vz = 0.;
	}
	if (fabs(data->play.leglen - data->play.z) < 1e-3 && (keys & KEY_SPACE))
		data->play.vz += 2.;
	else if (data->play.z > data->play.leglen)
		data->play.vz -= 5. * delta;
	data->play.z += data->play.vz * delta;
	if (data->play.leglen > data->play.z)
	{
		data->play.z = data->play.leglen;
		data->play.vz = 0.;
	}
}

void	move(t_data *data, double delta, uint64_t keys)
{
	const t_point	vec = getmov(data, keys, delta);
	const double	speed = sqrt(data->play.vx * data->play.vx
			+ data->play.vy * data->play.vy);

	move_z(data, delta, keys);
	if (((data->keys & KEY_SHIFT) && speed < data->set.speeddiff
			* data->set.speedmax)
		|| (!(data->keys & KEY_SHIFT) && speed < data->set.speedmax)
		|| data->play.z > data->play.leglen)
	{
		data->play.vx += vec.x;
		data->play.vy += vec.y;
	}
	move_xy(data, delta, (vec.x == 0. && vec.y == 0.));
	check_pos(data);
}
