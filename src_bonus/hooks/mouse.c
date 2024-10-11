/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 18:15:50 by glaguyon          #+#    #+#             */
/*   Updated: 2024/09/22 15:27:02 by ttrave           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"
#include "menu.h"
#include "status.h"
#include "keys.h"

#define LEFT 1
#define MIDDLE 2
#define RIGHT 3

int	unmouse_hook(int click, int x, int y, void *data_)
{
	t_data	*data;

	data = (t_data *)data_;
	if ((data->status & MENU) != 0)
	{
		if (click == LEFT)
			menu_unmouse_hook(x, y, data);
		return (0);
	}
	return (0);
}

int	mouse_hook(int click, int x, int y, void *data_)
{
	t_data	*data;

	data = data_;
	if ((data->status & MENU) != 0)
	{
		if (click == LEFT)
			menu_mouse_hook(x, y, data);
		return (0);
	}
	if (click == LEFT)
	{
		data->lastshot = 0.;
		data->keys |= KEY_LM;
	}
	return (0);
}
