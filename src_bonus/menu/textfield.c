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
	double		scale;
	uint32_t	colors[2];

	colors[0] = 0xFFDDDDDD;
	colors[1] = 0xFFDDDDDD;
	draw_rectangle(data, textfield.pos, textfield.dim, colors);
	if (textfield.state == PRESS)
	{
		strncpy(buffer, textfield.buffer, textfield.len);
		buffer[textfield.len] = '\0';
	}
	else if (textfield.precision == 0)
		snprintf(buffer, TEXTFIELD_LEN + 1,
			"%u", (uint32_t) *(double *)textfield.dst);
	else
		snprintf(buffer, TEXTFIELD_LEN + 1,
			"%.*lf", (int)textfield.precision, *(double *)textfield.dst);
	scale = fmin(1., (double)textfield.dim.x
			/ (double)(strlen(buffer) * WIDTH_CHAR));
	scale = fmin(scale, (double)textfield.dim.y
			/ (double)HEIGHT_CHAR);
	draw_string(data, (t_str){.str = buffer, .color = 0xFF000000,
		.scale = scale}, textfield.pos, textfield.dim);
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
		mask >>= 1;
	}
	if (i != 10)
		textfield->buffer[textfield->len] = '0' + i;
/*	else if ((data->keys & KEY_0) != 0)
		textfield->buffer[textfield->len] = '0';
	else if ((data->keys & KEY_1) != 0)
		textfield->buffer[textfield->len] = '1';
	else if ((data->keys & KEY_2) != 0)
		textfield->buffer[textfield->len] = '2';
	else if ((data->keys & KEY_3) != 0)
		textfield->buffer[textfield->len] = '3';
	else if ((data->keys & KEY_4) != 0)
		textfield->buffer[textfield->len] = '4';
	else if ((data->keys & KEY_5) != 0)
		textfield->buffer[textfield->len] = '5';
	else if ((data->keys & KEY_6) != 0)
		textfield->buffer[textfield->len] = '6';
	else if ((data->keys & KEY_7) != 0)
		textfield->buffer[textfield->len] = '7';
	else if ((data->keys & KEY_8) != 0)
		textfield->buffer[textfield->len] = '8';
	else if ((data->keys & KEY_9) != 0)
		textfield->buffer[textfield->len] = '9';*/
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
