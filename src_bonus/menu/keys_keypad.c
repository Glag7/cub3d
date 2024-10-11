/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_keypad.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrave <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 15:19:12 by ttrave            #+#    #+#             */
/*   Updated: 2024/09/06 17:02:31 by ttrave           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <X11/Xutil.h>
#include "data.h"
#include "keys.h"

int	key_hook_keypad(int key, t_data *data)
{
	if (key == XK_KP_0)
		data->keys |= KEY_0;
	else if (key == XK_KP_1)
		data->keys |= KEY_1;
	else if (key == XK_KP_2)
		data->keys |= KEY_2;
	else if (key == XK_KP_3)
		data->keys |= KEY_3;
	else if (key == XK_KP_4)
		data->keys |= KEY_4;
	else if (key == XK_KP_5)
		data->keys |= KEY_5;
	else if (key == XK_KP_6)
		data->keys |= KEY_6;
	else if (key == XK_KP_7)
		data->keys |= KEY_7;
	else if (key == XK_KP_8)
		data->keys |= KEY_8;
	else if (key == XK_KP_9)
		data->keys |= KEY_9;
	else if (key == XK_KP_Subtract)
		data->keys |= KEY_MINUS;
	else if (key == XK_period)
		data->keys |= KEY_DOT;
	return (0);
}

int	unkey_hook_keypad(int key, t_data *data)
{
	if (key == XK_KP_0)
		data->keys &= ~KEY_0;
	else if (key == XK_KP_1)
		data->keys &= ~KEY_1;
	else if (key == XK_KP_2)
		data->keys &= ~KEY_2;
	else if (key == XK_KP_3)
		data->keys &= ~KEY_3;
	else if (key == XK_KP_4)
		data->keys &= ~KEY_4;
	else if (key == XK_KP_5)
		data->keys &= ~KEY_5;
	else if (key == XK_KP_6)
		data->keys &= ~KEY_6;
	else if (key == XK_KP_7)
		data->keys &= ~KEY_7;
	else if (key == XK_KP_8)
		data->keys &= ~KEY_8;
	else if (key == XK_KP_9)
		data->keys &= ~KEY_9;
	else if (key == XK_KP_Subtract)
		data->keys &= ~KEY_MINUS;
	else if (key == XK_semicolon)
		data->keys &= ~KEY_DOT;
	return (0);
}
