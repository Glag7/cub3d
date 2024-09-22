/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_string.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrave <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 15:47:10 by ttrave            #+#    #+#             */
/*   Updated: 2024/09/22 19:51:37 by ttrave           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <math.h>
#include "data.h"
#include "menu.h"

static uint32_t	map_pixel(t_img img_char, t_ulpoint dim, t_ulpoint curr, double scale)
{
	long		x;
	long		y;

	x = (long)curr.x - (long)dim.x / 2;
	y = (long)curr.y - (long)dim.y / 2;
	x = (long)((double)x / scale);
	y = (long)((double)y / scale);
	x += (long)img_char.w / 2;
	y += (long)img_char.h / 2;
	return (img_char.px[(size_t)y * WIDTH_CHAR_IMG + (size_t)x]);
}

static void	draw_char(t_data *data, t_ulpoint pos, t_img img_char, double scale, uint32_t color)
{
	t_ulpoint	end;
	t_ulpoint	start;
	size_t		x;
	size_t		y;
	t_ulpoint	dim;

	dim = (t_ulpoint){.x = part(img_char.w, scale), .y = part(img_char.h, scale)};
	start = (t_ulpoint){.x = pos.x - dim.x / 2, .y = pos.y - dim.y / 2};
	end = (t_ulpoint){.x = pos.x + dim.x / 2, .y = pos.y + dim.y / 2};
	y = start.y;
	while (y < end.y)
	{
		x = start.x;
		while (x < end.x)
		{
			if ((map_pixel(img_char, dim,
				(t_ulpoint){.x = x - start.x, .y = y - start.y}, scale)
				& 0xFF000000) != 0)
				data->mlx.px[y * data->set.wid + x] = color;
			x++;
		}
		y++;
	}
}

static double	get_scale(t_ulpoint dim, size_t len, size_t spacing)
{
	return (fmin((double)dim.x / (double)(len * WIDTH_CHAR + (len - 1) * spacing),
		(double)dim.y / (double)HEIGHT_CHAR));
}

static t_img	get_char(t_img characters, char c)
{
	t_img	img_char;

	img_char = (t_img){.w = WIDTH_CHAR, .h = HEIGHT_CHAR, .px = characters.px};
	if (c >= 'A' && c <= 'Z')
		img_char.px += WIDTH_CHAR * (c - 'A');
	else if (c >= 'a' && c <= 'z')
		img_char.px += WIDTH_CHAR * (c - 'a');
	else if (c >= '0' && c <= '9')
		img_char.px += WIDTH_CHAR * ((c - '0') + 26);
	else if (c == '.')
		img_char.px += WIDTH_CHAR * 36;
	else if (c == '!')
		img_char.px += WIDTH_CHAR * 37;
	else if (c == '?')
		img_char.px += WIDTH_CHAR * 38;
	else if (c == '+')
		img_char.px += WIDTH_CHAR * 39;
	else
		img_char.px += WIDTH_CHAR * 40;
	return (img_char);
}

void	draw_string(t_data *data, char *str, uint32_t color, t_ulpoint pos, t_ulpoint dim)
{
	size_t		i;
	size_t		len;
	size_t		spacing;
	double		scale;
	t_ulpoint	pos_char;
	t_ulpoint	dim_char;

	len = strlen(str);
	spacing = part(WIDTH_CHAR, 0.2);
	scale = get_scale((t_ulpoint){.x = part(dim.x, 0.9), .y = part(dim.y, 0.9)}, len, spacing);
	spacing *= scale;
	dim_char = (t_ulpoint){.x = part(WIDTH_CHAR, scale), .y = part(HEIGHT_CHAR, scale)};
	pos_char = (t_ulpoint){.x = pos.x - (len * (dim_char.x / 2) + (len - 1) * spacing / 2), .y = pos.y};
	i = 0;
	while (i < len)
	{
		draw_char(data, pos_char, get_char(data->menu.characters, str[i]), scale, color);
		pos_char.x += dim_char.x + spacing;
		i++;
	}
}
