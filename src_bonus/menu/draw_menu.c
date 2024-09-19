/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_menu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrave <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 11:58:59 by ttrave            #+#    #+#             */
/*   Updated: 2024/09/19 18:05:42 by ttrave           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "set.h"
#include "menu.h"
#include "img.h"
#include "popup.h"

inline static uint32_t	darken(uint32_t pixel)
{
	uint32_t	darker_pixel;

	darker_pixel = pixel & 0xFF000000;
	darker_pixel |= (uint32_t)part((pixel & 0x00FF0000) >> 16, 0.5) << 16;
	darker_pixel |= (uint32_t)part((pixel & 0x0000FF00) >> 8, 0.5) << 8;
	darker_pixel |= (uint32_t)part((pixel & 0x000000FF), 0.5);
	return (darker_pixel);
}

void	save_background(t_data *data)
{
	size_t	x;
	size_t	y;

	y = 0;
	while (y < data->set.hei)
	{
		x = 0;
		while (x < data->set.wid)
		{
			data->menu.background[y * data->set.wid + x]
				= darken(data->mlx.px[y * data->set.wid + x]);
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
	size_t	x;
	size_t	y;
	size_t	margin;

	if (fmin(dim.x, dim.y) < 10 * OUTLINE_WIDTH)
		margin = part(fmin(dim.x, dim.y), 0.1);
	else
		margin = OUTLINE_WIDTH;
	y = pos.y - dim.y / 2;
	while (y < pos.y + dim.y / 2)
	{
		x = pos.x - dim.x / 2;
		while (x < pos.x + dim.x / 2)
		{
			if (x < pos.x - dim.x / 2 + margin || x > pos.x + dim.x / 2 - margin
				|| y < pos.y - dim.y / 2 + margin
				|| y > pos.y + dim.y / 2 - margin)
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
			data->mlx.px[y_px * data->set.wid + x_px] = get_pixel(data->mlx.px[y_px
				* data->set.wid + x_px], image.px[y_img * image.w + x_img]);
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
