/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_menu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrave <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 11:58:59 by ttrave            #+#    #+#             */
/*   Updated: 2024/09/20 15:46:50 by ttrave           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "set.h"
#include "menu.h"
#include "img.h"
#include "popup.h"

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
				| ((uint32_t)part((pixel & 0x00FF0000) >> 16, 0.5) << 16)
				| ((uint32_t)part((pixel & 0x0000FF00) >> 8, 0.5) << 8)
				| ((uint32_t)part((pixel & 0x000000FF), 0.5));
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

void	draw_rectangle(t_data *data, t_ulpoint pos, t_ulpoint dim,
	uint32_t *colors)
{
	t_ulpoint	start;
	t_ulpoint	end;
	size_t	x;
	size_t	y;
	size_t	margin;

	if (part((size_t)fmin((double)dim.x, (double)dim.y), 0.1) > OUTLINE_WIDTH)
		margin = OUTLINE_WIDTH;
	else
		margin = part((size_t)fmin((double)dim.x, (double)dim.y), 0.1);
	start = (t_ulpoint){.x = pos.x - part(dim.x, 0.5),
		.y = pos.y - part(dim.y, 0.5)};
	end = (t_ulpoint){.x = pos.x - part(dim.x, 0.5) + dim.x,
		.y = pos.y - part(dim.y, 0.5) + dim.y};
	y = start.y;
	while (y < end.y)
	{
		x = start.x;
		while (x < end.x)
		{
			if (x + 1 < start.x + margin || x > end.x - margin
				|| y + 1 < start.y + margin || y > end.y - margin)
				data->mlx.px[y * data->set.wid + x] = colors[0];
			else
				data->mlx.px[y * data->set.wid + x] = colors[1];
			x++;
		}
		y++;
	}
}

void	draw_image(t_data *data, t_ulpoint pos, t_img image)
{
	size_t		x_img;
	size_t		y_img;
	size_t		x_px;
	size_t		y_px;

	y_img = 0;
	y_px = pos.y - image.h / 2;
	while (y_img < image.h)
	{
		x_img = 0;
		x_px = pos.x - image.w / 2;
		while (x_img < image.w)
		{
			data->mlx.px[y_px * data->set.wid + x_px]
				= get_pixel(data->mlx.px[y_px * data->set.wid + x_px],
					image.px[y_img * image.w + x_img]);
			x_img++;
			x_px++;
		}
		y_img++;
		y_px++;
	}
}

void	draw_button(t_data *data, t_button button, uint8_t state)
{
	uint32_t	*colors;

	if (state == IDLE)
		colors = button.color_idle;
	else
		colors = button.color_hover;
	draw_rectangle(data, button.pos, button.dim, colors);
	draw_image(data, button.pos, button.string);
}
