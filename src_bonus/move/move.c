/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 17:08:10 by glaguyon          #+#    #+#             */
/*   Updated: 2024/09/18 18:50:40 by glaguyon         ###   ########.fr       */
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

static inline __attribute__((always_inline)) t_point
	normvec(t_point vec)
{
	double	len;

	len = sqrt(vec.x * vec.x + vec.y * vec.y);
	if (len)
	{
		vec.x /= len;
		vec.y /= len;
	}
	return (vec);
}
static t_point	getmov(t_data *data, uint64_t keys)
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
	return (normvec(vec));
}

# define FAT .05//a changer en fonction de la direction

//check en x, bouger en x, check en y, bouger en y
void	move(t_data *data, double delta, uint64_t keys)
{
	double	speed;
	t_point	vec;
	t_point	newpos;

	vec = getmov(data, keys);
	speed = 1.5;
	if (keys & KEY_SHIFT)
		speed = 5.;
	newpos.x = data->play.x;
	newpos.y = data->play.y;
	newpos.x += speed * vec.x * delta;
	newpos.y += speed * vec.y * delta;
	//ramener a la map
	if (!data->map.map[(int)newpos.x + (int)data->play.y * data->map.wid])
		data->play.x = newpos.x;
	if (!data->map.map[(int)data->play.x + (int)newpos.y * data->map.wid])
		data->play.y = newpos.y;



	//super idol
	if (keys & KEY_SPACE)
	{
		data->play.z += 9 * delta;
	}
	if (data->play.z > 0)
		data->play.z -= 3 * delta;
	check_pos(data);
}
