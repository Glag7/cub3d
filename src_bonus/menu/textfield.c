/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textfield.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrave <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 15:16:18 by ttrave            #+#    #+#             */
/*   Updated: 2024/09/22 19:11:17 by ttrave           ###   ########.fr       */
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

void	build_textfield(t_data *data, t_textfield textfield)
{
	;
}
/*	size_t		len;
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
			/ (double)(len * WIDTH_CHAR));
	scale = fmin(scale, (double)textfield.dim.y
			/ (double)HEIGHT_CHAR);
	if (textfield.type == UINT)
		print_uint(data, textfield, scale, len);
	else
		print_double(data, textfield, scale, len);
}*/
