/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textfield_itoa.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrave <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 19:33:01 by ttrave            #+#    #+#             */
/*   Updated: 2024/09/20 18:44:49 by ttrave           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"
#include "menu.h"
#include "popup.h"

void	print_uint(t_data *data, t_textfield textfield, double scale,
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

static bool	manage_sign(double *value)
{
	if (*value < 0.)
	{
		*value = -(*value);
		return (1);
	}
	return (0);
}

void	print_double(t_data *data, t_textfield textfield, double scale,
		size_t len)
{
	bool	neg;
	double	value;
	size_t	i_digit;
	size_t	i_offset;
	size_t	d_offset;

	value = *textfield.src;
	neg = manage_sign(&value);
	d_offset = part(data->menu.digits[0].w, scale);
	i_offset = textfield.pos.x + textfield.dim.x / 2 - d_offset / 2;
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
