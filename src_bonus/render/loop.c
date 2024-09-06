/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 19:04:21 by glaguyon          #+#    #+#             */
/*   Updated: 2024/09/06 17:59:28 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <time.h>
#include <stdlib.h>
#include "render.h"
#include "move.h"
#include "mlx.h"
#include "data.h"
#include "fps.h"
#include "status.h"
#include "keys.h"

static void	drawfps(t_mlx *mlx, int fps)
{
	static char	num[16] = "fps:    ";
	static int	color[9] = {RED, ORE, ORA, YEL, YGR, LGR, GRE, GRE, GRE};
	int			i;

	i = 0;
	if (fps > 999)
		num[i++] = (fps / 1000) % 10 + '0';
	if (fps > 99)
		num[i++] = (fps / 100) % 10 + '0';
	if (fps > 9)
		num[i++] = (fps / 10) % 10 + '0';
	num[i++] = fps % 10 + '0';
	num[i++] = ' ';
	*(unsigned long long *)(num + i) = FPS;
	if (fps > 80)
		fps = 80;
	mlx_string_put(mlx->mlx, mlx->win, 0, 10, color[fps / 10], num);
}

static void	compute_values(t_data *data)
{
	double	yend_cur;

	data->horizon = data->set.hei / 2 + (int)(data->set.planwid
			* data->play.az / M_PI * 4.);
	yend_cur = 1. / ((double)data->set.hei / 2. + ((double)data->set.wid
				/ (data->set.tanfov * 2.) * MAX_ANGLE / M_PI * 4.));
	data->px.x = (((-.5 * data->set.fov - data->play.a)
				* (.5 / M_PI) - .25) + 1.) * (double)data->map.c.w;
	data->px.y = ((double)(-data->horizon) * yend_cur + 1.)
		* (double)data->map.c.h;
	data->pxinc.x = (((1. / (double)data->set.wid) * data->set.fov)
			* (.5 / M_PI)) * (double)data->map.c.w;
	data->pxinc.y = 1. * yend_cur *(double)data->map.c.h;
}

static double	get_delta(int *newsec)
{
	static struct timespec	old = {0, 0};
	struct timespec			curr;
	double					delta;

	clock_gettime(CLOCK_MONOTONIC_RAW, &curr);
	delta = curr.tv_sec - old.tv_sec + (curr.tv_nsec - old.tv_nsec) * 1.e-9;
	if (delta > 1.)
		delta = 1.;
	*newsec = (old.tv_sec < curr.tv_sec);
	old = curr;
	return (delta);
}

#define TIME 1.
void	open_doors(t_data *data, double delta)
{
	int			i;
	uint32_t	*cur;
	int32_t	value;
	int	stop;

	stop = 0;
	i = 0;
	while (i < 32)
	{
		if (cur == data->opening[i])
		{
			data->opening[i++] = NULL;
			continue ;
		}
		cur = data->opening[i];
		if (cur)
		{
			value = (*cur & VALUE) >> VALUEOFF;
			if (*cur & OPENING)
				value += (int32_t)(delta / TIME * (double)VALUEONE);
			else if (*cur & CLOSING)
			{
				value -= (int32_t)(delta / TIME * (double)VALUEONE);
			}
			else
				data->opening[i] = 0;
			if (value > VALUEONE * 9 / 10)
			{
				value = VALUEONE * 9 / 10;
				*cur &= ~MOVING;
				stop = 1;
			}
			else if (value < 0)
			{
				value = 0;
				*cur &= ~MOVING;
				stop = 1;
			}
			*cur = (*cur & ~VALUE) | value << VALUEOFF;
			if (stop)
				data->opening[i] = 0;
			
		}
		++i;
	}
}//FIXME door can be added twice

static void	manage_game(t_data *data, double delta)
{
	if (!(data->status & INWINDOW))
		return ;
	//TODO make this a func
	//open door + open activated doors
	if (data->keys & KEY_E && data->cross && data->cross_dist < ARM_LEN
		&& (*data->cross & SPEC) == DOOR)
	{
		if ((*data->cross & MOVING))
			*data->cross = (*data->cross & ~MOVING) | (~(*data->cross & MOVING) & MOVING);
		else if (!(*data->cross & VALUE))
			*data->cross |= OPENING;
		else
			*data->cross |= CLOSING;
		data->opening[data->i_open] = data->cross;
		data->i_open = (data->i_open + 1) % 31 + 1;
		data->keys &= ~KEY_E;
	}

	//shoot
	if (data->keys & KEY_LM)
	{
		if (data->cross)
			*data->cross = 0;
		//raycast chokbar qui tag l'objet, il fait l'anim puis il explose
		data->keys &= ~KEY_LM;
	}
	data->cross = NULL;
	move_angle(data, delta, data->keys);
	move(data, delta, data->keys);
	open_doors(data, delta);//
	compute_values(data);
	draw_floor(data);
	raycast(data);
	draw_minimap(data);
	draw_hud(data);
	data->lastshot += delta;
}

int	loop(void *data_)
{
	static int	fps = 0;
	static int	oldfps = 0;
	int			newsec;
	double		delta;
	t_data		*data;

	data = data_;
	delta = get_delta(&newsec);
	manage_game(data, delta);
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->mlx.img, 0, 0);
	if (newsec)
	{
		oldfps = fps;
		fps = 0;
	}
	drawfps(&data->mlx, oldfps);
	++fps;
	return (0);
}
