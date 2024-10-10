/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 15:19:12 by glaguyon          #+#    #+#             */
/*   Updated: 2024/09/24 17:10:48 by glag             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <X11/Xutil.h>
#include <math.h>
#include "keys.h"
#include "mlx.h"
#include "data.h"
#include "img.h"

static int	key_hook2(int key, t_data *data)
{
	if (key == XK_Left)
		data->keys |= KEY_LEFT;
	else if (key == XK_Right)
		data->keys |= KEY_RIGHT;
	else if (key == XK_Up)
		data->keys |= KEY_UP;
	else if (key == XK_Down)
		data->keys |= KEY_DOWN;
	return (0);
}

int	key_hook(int key, void *data_)
{
	t_data	*data;

	data = data_;
	if (key == XK_Escape)
		mlx_loop_end(data->mlx.mlx);
	else if (key == XK_w)
		data->keys |= KEY_W;
	else if (key == XK_s)
		data->keys |= KEY_S;
	else if (key == XK_a)
		data->keys |= KEY_A;
	else if (key == XK_d)
		data->keys |= KEY_D;
	else if (key == XK_Shift_L)
		data->keys |= KEY_SHIFT;
	else if (key == XK_e)
		data->keys |= KEY_E;
	else if (key == XK_space)
		data->keys |= KEY_SPACE;
	else if (key == XK_Control_L)
		data->keys |= KEY_CTRL;
	else
		return (key_hook2(key, data));
	return (0);
}

static int	unkey_hook2(int key, t_data *data)
{
	if (key == XK_Left)
		data->keys &= ~KEY_LEFT;
	else if (key == XK_Right)
		data->keys &= ~KEY_RIGHT;
	else if (key == XK_Up)
		data->keys &= ~KEY_UP;
	else if (key == XK_Down)
		data->keys &= ~KEY_DOWN;
	return (0);
}

int	unkey_hook(int key, void *data_)
{
	t_data	*data;

	data = data_;
	if (key == XK_w)
		data->keys &= ~KEY_W;
	else if (key == XK_s)
		data->keys &= ~KEY_S;
	else if (key == XK_a)
		data->keys &= ~KEY_A;
	else if (key == XK_d)
		data->keys &= ~KEY_D;
	else if (key == XK_Shift_L)
		data->keys &= ~KEY_SHIFT;
	else if (key == XK_e)
		data->keys &= ~KEY_E;
	else if (key == XK_space)
		data->keys &= ~KEY_SPACE;
	else if (key == XK_Control_L)
		data->keys &= ~KEY_CTRL;
	else
		return (unkey_hook2(key, data));
	return (0);
}
