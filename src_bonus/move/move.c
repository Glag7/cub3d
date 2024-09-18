/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 17:08:10 by glaguyon          #+#    #+#             */
/*   Updated: 2024/09/18 17:56:06 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <math.h>
#include "set.h"
#include "data.h"
#include "play.h"
#include "point.h"
#include "keys.h"

static inline void	check_pos(t_data *data)
{
	if (data->play.x >= (double)data->map.wid)
		data->play.x -= (double)data->map.wid;
	else if (data->play.x < 0.)
		data->play.x += (double)data->map.wid;
	if (data->play.y >= (double)data->map.hei)
		data->play.y -= (double)data->map.hei;
	else if (data->play.y < 0.)
		data->play.y += (double)data->map.hei;
	if (data->play.a > M_PI)
		data->play.a -= 2. * M_PI;
	else if (data->play.a < -M_PI)
		data->play.a += 2. * M_PI;
	if (data->play.az > MAX_ANGLE)
		data->play.az = MAX_ANGLE;
	else if (data->play.az < MIN_ANGLE)
		data->play.az = MIN_ANGLE;
	if (data->play.z > .5)
		data->play.z = .5;
	else if (data->play.z < -.5)
		data->play.z = -.5;
	data->play.sina = sin(data->play.a);
	data->play.cosa = cos(data->play.a);
}

static inline void	move_pos(t_data *data, double delta,
	double speed, uint64_t keys)
{//temp fix, use angles instead
	t_point	vec;
	double	len;

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
	len = sqrt(vec.x * vec.x + vec.y * vec.y);
	if (len)
	{
	vec.x /= len;
	vec.y /= len;
	}
	data->play.x += speed * vec.x * delta;
	data->play.y += speed * vec.y * delta;
	//super idol
	if (keys & KEY_SPACE)
	{
		data->play.z += 9 * delta;
	}
	if (data->play.z > 0)
		data->play.z -= 3 * delta;
}

void	move(t_data *data, double delta, uint64_t keys)
{
	double	speed;

	speed = 1.5;
	if (keys & KEY_SHIFT)
		speed = 5.;
	move_pos(data, delta, speed, keys);
	check_pos(data);
}
