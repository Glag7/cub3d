/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_background.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrave <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 18:25:03 by ttrave            #+#    #+#             */
/*   Updated: 2024/09/20 18:31:10 by ttrave           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"
#include "menu.h"

void	save_background(t_data *data)
{
	size_t		x;
	size_t		y;
	uint32_t	pixel;

	y = 0;
	while (y < data->set.hei)
	{
		x = 0;
		while (x < data->set.wid)
		{
			pixel = data->mlx.px[y * data->set.wid + x];
			pixel = (pixel & 0xFF000000)
				| ((uint32_t)part((pixel & 0x00FF0000) >> 16, 0.6) << 16)
				| ((uint32_t)part((pixel & 0x0000FF00) >> 8, 0.6) << 8)
				| ((uint32_t)part((pixel & 0x000000FF), 0.6));
			data->menu.background[y * data->set.wid + x] = pixel;
			x++;
		}
		y++;
	}
}

void	draw_background(t_data *data)
{
	size_t	x;
	size_t	y;

	y = 0;
	while (y < data->set.hei)
	{
		x = 0;
		while (x < data->set.wid)
		{
			data->mlx.px[y * data->set.wid + x]
				= data->menu.background[y * data->set.wid + x];
			x++;
		}
		y++;
	}
}
