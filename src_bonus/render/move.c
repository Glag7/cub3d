/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 17:08:10 by glaguyon          #+#    #+#             */
/*   Updated: 2024/07/25 20:39:19 by glag             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <math.h>
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
	if (data->play.az > M_PI)
		data->play.az -= 2. * M_PI;
	else if (data->play.az < -M_PI)
		data->play.az += 2. * M_PI;
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
		vec.y -= sin(data->play.a);
		vec.x += cos(data->play.a);
	}
	if (keys & KEY_S)
	{
		vec.y += sin(data->play.a);
		vec.x -= cos(data->play.a);
	}
	if (keys & KEY_A)
	{
		vec.y -= cos(data->play.a);
		vec.x -= sin(data->play.a);
	}
	if (keys & KEY_D)
	{
		vec.y += cos(data->play.a);
		vec.x += sin(data->play.a);
	}
	len = sqrt(vec.x * vec.x + vec.y * vec.y);
	if (len)
	{
	vec.x /= len;
	vec.y /= len;
	}
	data->play.x += speed * vec.x * delta;
	data->play.y += speed * vec.y * delta;
}

void	move(t_data *data, double delta, uint64_t keys)
{
	double	speed;

	speed = 1.5;
	if (keys & KEY_SHIFT)
		speed = 5.;
	move_pos(data, delta, speed, keys);
	if (keys & KEY_LEFT)
		data->play.a += 1. * delta;
	if (keys & KEY_RIGHT)
		data->play.a -= 1. * delta;
	if (keys & KEY_UP)
		data->play.az += 1. * delta;
	if (keys & KEY_DOWN)
		data->play.az -= 1. * delta;
	check_pos(data);
}
