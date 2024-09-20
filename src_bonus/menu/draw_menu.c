/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_menu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrave <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 11:58:59 by ttrave            #+#    #+#             */
/*   Updated: 2024/09/20 18:52:24 by ttrave           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "data.h"
#include "menu.h"
#include "popup.h"

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
