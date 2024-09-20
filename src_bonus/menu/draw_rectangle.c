/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_rectangle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrave <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 18:48:27 by ttrave            #+#    #+#             */
/*   Updated: 2024/09/20 18:51:38 by ttrave           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "menu.h"

static size_t	calculate_margin(t_ulpoint dim)
{
	if (part((size_t)fmin((double)dim.x, (double)dim.y), 0.1) > OUTLINE_WIDTH)
		return (OUTLINE_WIDTH);
	return (part((size_t)fmin((double)dim.x, (double)dim.y), 0.1));
}

static double	calculate_weight(t_ulpoint pos, t_ulpoint dim, t_ulpoint curr,
	size_t margin)
{
	t_point	weight;

	if (curr.x <= pos.x - part(dim.x, 0.5) + margin)
		weight.x = fabs((double)((long)curr.x - (long)(pos.x - part(dim.x, 0.5)
						+ margin))) / (double)margin;
	else if (curr.x >= pos.x - part(dim.x, 0.5) + dim.x - margin)
		weight.x = fabs((double)((long)curr.x - (long)(pos.x - part(dim.x, 0.5)
						+ dim.x - margin))) / (double)margin;
	if (curr.y <= pos.y - part(dim.y, 0.5) + margin)
		weight.y = fabs((double)((long)curr.y - (long)(pos.y - part(dim.y, 0.5)
						+ margin))) / (double)margin;
	else if (curr.y >= pos.y - part(dim.y, 0.5) + dim.y - margin)
		weight.y = fabs((double)((long)curr.y - (long)(pos.y - part(dim.y, 0.5)
						+ dim.y - margin))) / (double)margin;
	return (fmax(weight.x, weight.y));
}

static uint32_t	apply_gradient(t_ulpoint pos, t_ulpoint dim, t_ulpoint curr,
	uint32_t *colors)
{
	uint32_t	new_color;
	double		weight;
	size_t		margin;

	margin = calculate_margin(dim) + GRADIENT_WIDTH;
	if (curr.x > pos.x - part(dim.x, 0.5) + margin
		&& curr.x + 1 < pos.x - part(dim.x, 0.5) + dim.x - margin
		&& curr.y > pos.y - part(dim.y, 0.5) + margin
		&& curr.y + 1 < pos.y - part(dim.y, 0.5) + dim.y - margin)
		return (colors[1]);
	weight = calculate_weight(pos, dim, curr, margin);
	new_color = 0;
	new_color |= 0xFF000000;
	new_color |= (uint32_t)((double)((colors[0] & 0x00FF0000) >> 16) *weight
			+ (double)((colors[1] & 0x00FF0000) >> 16) *(1. - weight)) << 16;
	new_color |= (uint32_t)((double)((colors[0] & 0x0000FF00) >> 8) *weight
			+ (double)((colors[1] & 0x0000FF00) >> 8) *(1. - weight)) << 8;
	new_color |= (uint32_t)((double)(colors[0] & 0x000000FF) *weight
			+ (double)(colors[1] & 0x000000FF) *(1. - weight));
	return (new_color);
}

void	draw_rectangle(t_data *data, t_ulpoint pos, t_ulpoint dim,
	uint32_t *colors)
{
	t_ulpoint	start;
	t_ulpoint	end;
	t_ulpoint	curr;
	size_t		margin;

	margin = calculate_margin(dim);
	start = (t_ulpoint){.x = pos.x - dim.x / 2, .y = pos.y - dim.y / 2};
	end = (t_ulpoint){.x = pos.x - dim.x / 2 + dim.x,
		.y = pos.y - dim.y / 2 + dim.y};
	curr.y = start.y;
	while (curr.y < end.y)
	{
		curr.x = start.x;
		while (curr.x < end.x)
		{
			if (curr.x + 1 < start.x + margin || curr.x > end.x - margin
				|| curr.y + 1 < start.y + margin || curr.y > end.y - margin)
				data->mlx.px[curr.y * data->set.wid + curr.x] = colors[0];
			else
				data->mlx.px[curr.y * data->set.wid + curr.x]
					= apply_gradient(pos, dim, curr, colors);
			curr.x++;
		}
		curr.y++;
	}
}
