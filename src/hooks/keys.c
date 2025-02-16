/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 15:19:12 by glaguyon          #+#    #+#             */
/*   Updated: 2024/06/28 18:41:42 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <X11/Xutil.h>
#include <math.h>
#include "keys.h"
#include "mlx.h"
#include "data.h"
#include "img.h"

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
	else if (key == XK_Left)
		data->keys |= KEY_LEFT;
	else if (key == XK_Right)
		data->keys |= KEY_RIGHT;
	else if (key == XK_Shift_L)
		data->keys |= KEY_SHIFT;
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
	else if (key == XK_Left)
		data->keys &= ~KEY_LEFT;
	else if (key == XK_Right)
		data->keys &= ~KEY_RIGHT;
	else if (key == XK_Shift_L)
		data->keys &= ~KEY_SHIFT;
	return (0);
}
