/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textfield.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrave <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 15:16:18 by ttrave            #+#    #+#             */
/*   Updated: 2024/09/20 18:39:44 by ttrave           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "data.h"
#include "popup.h"
#include "menu.h"

static size_t	get_len_double(double n)
{
	size_t	len;

	len = 4;
	if (n < 0.)
	{
		n = -n;
		len++;
	}
	while (n >= 10.)
	{
		n /= 10.;
		len++;
	}
	return (len);
}

static size_t	get_len_uint(uint32_t n)
{
	size_t	len;

	len = 1;
	while (n > 9)
	{
		n /= 10;
		len++;
	}
	return (len);
}

void	draw_digit(t_data *data, t_ulpoint pos, double scale, t_img digit)
{
	t_ulpoint	end;
	t_ulpoint	start;
	size_t		x;
	size_t		y;

	start.y = pos.y - part(digit.h, scale) / 2;
	start.x = pos.x - part(digit.w, scale) / 2;
	end.y = pos.y + part(digit.h, scale) / 2;
	end.x = pos.x + part(digit.w, scale) / 2;
	y = start.y;
	while (y < end.y)
	{
		x = start.x;
		while (x < end.x)
		{
			data->mlx.px[y * data->set.wid + x] = get_pixel(data->mlx.px[y
					* data->set.wid + x], digit.px[part(digit.h, (double)(y
							- start.y) / (double)(end.y - start.y)) * digit.w
					+ part(digit.w, (double)(x - start.x) / (double)(end.x
							- start.x))]);
			x++;
		}
		y++;
	}
}

void	build_textfield(t_data *data, t_textfield textfield)
{
	size_t		len;
	double		scale;
	uint32_t	colors[2];

	colors[0] = 0xFFDDDDDD;
	colors[1] = 0xFFDDDDDD;
	draw_rectangle(data, textfield.pos, textfield.dim, colors);
	if (textfield.type == UINT)
		len = get_len_uint((uint32_t)(*textfield.src));
	else
		len = get_len_double(*textfield.src);
	scale = fmin(1., (double)textfield.dim.x
			/ (double)(len * data->menu.digits[0].w));
	scale = fmin(scale, (double)textfield.dim.y
			/ (double)data->menu.digits[0].h);
	if (textfield.type == UINT)
		print_uint(data, textfield, scale, len);
	else
		print_double(data, textfield, scale, len);
}
