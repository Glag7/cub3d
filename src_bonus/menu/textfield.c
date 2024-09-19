/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textfield.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrave <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 15:16:18 by ttrave            #+#    #+#             */
/*   Updated: 2024/09/19 19:14:57 by ttrave           ###   ########.fr       */
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

static void	draw_digit(t_data *data, t_ulpoint pos, double scale, t_img digit)
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

static void	print_uint(t_data *data, t_textfield textfield, double scale,
		size_t len)
{
	uint32_t	value;
	size_t		i_digit;
	size_t		i_offset;
	size_t		d_offset;

	value = (uint32_t)(*textfield.src);
	i_digit = 0;
	d_offset = part(data->menu.digits[0].w, scale);
	i_offset = textfield.pos.x + part(textfield.dim.x, 0.5)
		- part(d_offset, 0.5);
	while (i_digit < len)
	{
		draw_digit(data, (t_ulpoint){.x = i_offset, .y = textfield.pos.y},
			scale, data->menu.digits[value % 10]);
		value /= 10;
		i_digit++;
		i_offset -= d_offset;
	}
}

static void	print_decimals(t_data *data, t_ulpoint pos, double scale,
		double value)
{
	double	d_offset;

	d_offset = part(data->menu.digits[0].w, scale);
	value -= floor(value);
	value *= 100.;
	draw_digit(data, pos, scale, data->menu.digits[(size_t)fmod(value, 10.)]);
	pos.x -= d_offset;
	value /= 10.;
	draw_digit(data, pos, scale, data->menu.digits[(size_t)fmod(value, 10.)]);
	pos.x -= d_offset;
	value /= 10.;
	draw_digit(data, pos, scale, data->menu.digits[11]);
}

static void	print_double(t_data *data, t_textfield textfield, double scale,
		size_t len)
{
	bool	neg;
	double	value;
	size_t	i_digit;
	size_t	i_offset;
	size_t	d_offset;

	value = *textfield.src;
	if (value < 0.)
	{
		neg = 1;
		value = -value;
	}
	else
		neg = 0;
	d_offset = part(data->menu.digits[0].w, scale);
	i_offset = textfield.pos.x + part(textfield.dim.x, 0.5)
		- part(d_offset, 0.5);
	print_decimals(data, (t_ulpoint){.x = i_offset, .y = textfield.pos.y},
		scale, value);
	i_offset -= 3 * d_offset;
	i_digit = 3 + neg;
	while (i_digit < len)
	{
		draw_digit(data, (t_ulpoint){.x = i_offset, .y = textfield.pos.y},
			scale, data->menu.digits[(size_t)floor(fmod(value, 10.))]);
		i_offset -= d_offset;
		i_digit++;
		value /= 10.;
	}
	if (neg == 1)
		draw_digit(data, (t_ulpoint){.x = i_offset, .y = textfield.pos.y},
			scale, data->menu.digits[10]);
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
