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

static t_img	get_char(t_img characters, char c)
{
	t_img	img_char;

	img_char = (t_img){.w = WIDTH_CHAR, .h = HEIGHT_CHAR, .px = characters.px};
	if (c >= 'A' && c <= 'Z')
		img_char.px += WIDTH_CHAR * (c - 'A');
	else if (c >= 'a' && c <= 'z')
		img_char.px += WIDTH_CHAR * (c - 'a');
	else if (c >= '0' && c <= '9')
		img_char.px += WIDTH_CHAR * (c - '0' + 26);
	else if (c == '.')
		img_char.px += WIDTH_CHAR * 36;
	else if (c == '?')
		img_char.px += WIDTH_CHAR * 37;
	else if (c == '!')
		img_char.px += WIDTH_CHAR * 38;
	else if (c == '+')
		img_char.px += WIDTH_CHAR * 39;
	else
		img_char.px += WIDTH_CHAR * 40;
	return (img_char);
}

static void	draw_char(t_data *data, t_ulpoint pos, t_str string, double scale)
{
	t_img		img_char;
	t_ulpoint	end;
	t_ulpoint	start;
	t_ulpoint	curr;

	img_char = get_char(data->menu.characters, *string.str);
	start = (t_ulpoint){.x = pos.x - part(img_char.w, scale) / 2,
		.y = pos.y - part(img_char.h, scale) / 2};
	end = (t_ulpoint){.x = pos.x + part(img_char.w, scale) / 2,
		.y = pos.y + part(img_char.h, scale) / 2};
	curr.y = start.y;
	while (curr.y < end.y)
	{
		curr.x = start.x;
		while (curr.x < end.x)
		{
			if ((img_char.px[part(img_char.h, (double)(curr.y - start.y)
						/ (double)(end.y - start.y)) * WIDTH_CHAR_IMG
				+ part(img_char.w, (double)(curr.x - start.x) / (double)(end.x
				- start.x))] & 0xFF000000) != 0)
				data->mlx.px[curr.y * data->set.wid + curr.x] = string.color;
			curr.x++;
		}
		curr.y++;
	}
}

static double	get_scale(t_ulpoint dim, size_t len, size_t spacing)
{
	return (fmin((double)dim.x / (double)(len * WIDTH_CHAR + (len - 1)
			* spacing), (double)dim.y / (double)HEIGHT_CHAR));
}

void	draw_string(t_data *data, t_str string, t_ulpoint pos, t_ulpoint dim)
{
	size_t		i;
	double		scale;
	t_ulpoint	pos_char;
	t_ulpoint	dim_char;

	scale = get_scale((t_ulpoint){dim.x, dim.y}, strlen(string.str),
			part(WIDTH_CHAR, 0.2));
	if (string.scale != 0.)
		scale = fmin((string.scale * (double)data->set.wid) / 5.,
				get_scale((t_ulpoint){.x = dim.x, .y = dim.y},
					strlen(string.str), part(WIDTH_CHAR, 0.2)));
	dim_char = (t_ulpoint){.x = part(WIDTH_CHAR, scale),
		.y = part(HEIGHT_CHAR, scale)};
	pos_char = (t_ulpoint){.x = pos.x - ((strlen(string.str) - 1) * dim_char.x
			+ (strlen(string.str) - 1) * part(part(WIDTH_CHAR, 0.2), scale))
		/ 2, .y = pos.y};
	i = 0;
	while (i < strlen(string.str) + i)
	{
		if (*string.str != ' ')
			draw_char(data, pos_char, string, scale);
		pos_char.x += dim_char.x + part(part(WIDTH_CHAR, 0.2), scale);
		string.str++;
		i++;
	}
}
