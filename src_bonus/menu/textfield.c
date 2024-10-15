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

#include <string.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include "data.h"
#include "popup.h"
#include "menu.h"
#include "keys.h"

void	build_textfield(t_data *data, t_textfield textfield)
{
	char		buffer[TEXTFIELD_LEN + 1];
	uint32_t	colors[2];
	double		v;

	colors[0] = 0xFFDDDDDD;
	colors[1] = 0xFFDDDDDD;
	draw_rectangle(data, textfield.pos, textfield.dim, colors);
	if (textfield.type == UINT)
		v = (double)*(uint32_t *)textfield.dst;
	else
		v = *(double *)textfield.dst;
	if (textfield.state == PRESS)
	{
		strncpy(buffer, textfield.buffer, textfield.len);
		buffer[textfield.len] = '\0';
	}
	else if (textfield.precision == 0)
		snprintf(buffer, TEXTFIELD_LEN, "%u", (uint32_t)v);
	else
		snprintf(buffer, TEXTFIELD_LEN, "%.*lf", (int)textfield.precision, v);
	draw_string(data, (t_str){buffer, 0xFF000000, fmin(fmin(1.,
				(double)textfield.dim.x / (double)(strlen(buffer)
					* WIDTH_CHAR)), (double)textfield.dim.y
			/ (double)HEIGHT_CHAR)}, textfield.pos,
		(t_ulpoint){part(textfield.dim.x, 0.9), part(textfield.dim.y, 0.9)});
}

static void	add_character(t_data *data, t_textfield *textfield)
{
	uint64_t	mask;
	size_t		i;

	if ((data->keys & KEY_BACK) != 0)
	{
		textfield->buffer[textfield->len - 1] = '\0';
		textfield->len--;
		return ;
	}
	mask = KEY_0;
	i = 0;
	while (i < 10 && (data->keys & mask) == 0)
	{
		i++;
		mask <<= 1;
	}
	if (i != 10)
		textfield->buffer[textfield->len] = '0' + i;
	else if ((data->keys & KEY_MINUS) != 0)
		textfield->buffer[textfield->len] = '-';
	else if ((data->keys & KEY_DOT) != 0)
		textfield->buffer[textfield->len] = '.';
	textfield->len++;
}

void	update_textfields(t_data *data)
{
	static struct timespec	last_write = {0, 0};
	static struct timespec	new_write;
	size_t					i;

	i = 0;
	while (i < NB_TEXTFIELDS)
	{
		if (data->menu.textfields[i].state == PRESS
			&& (data->keys & KEYS_DIGITS) != 0
			&& (data->menu.textfields[i].len < TEXTFIELD_LEN
				|| (data->keys & KEY_BACK) != 0)
			&& (data->menu.textfields[i].len > 0
				|| (data->keys & KEY_BACK) == 0))
		{
			clock_gettime(CLOCK_MONOTONIC_RAW, &new_write);
			if ((new_write.tv_sec - last_write.tv_sec) * 1000000
				+ (new_write.tv_nsec - last_write.tv_nsec) / 1000 > WRITE_DELAY)
			{
				last_write = new_write;
				add_character(data, &data->menu.textfields[i]);
				build_textfield(data, data->menu.textfields[i]);
			}
		}
		i++;
	}
}
