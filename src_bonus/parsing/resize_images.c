/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize_images.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrave <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 18:49:22 by ttrave            #+#    #+#             */
/*   Updated: 2024/08/06 19:12:07 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "specs.h"
#include "utils.h"
#include "map.h"

inline static uint32_t	average_pixel(double *sum, double surface)
{
	return (((uint8_t)(sum[0] / surface) << 24)
		| ((uint8_t)(sum[1] / surface) << 16)
		| ((uint8_t)(sum[2] / surface) << 8)
		| (uint8_t)(sum[3] / surface));
}

inline static void	add_pixel(double *sum, uint32_t pixel, double weight)
{
	sum[0] += (double)((pixel & 0xFF000000) >> 24) *weight;
	sum[1] += (double)((pixel & 0x00FF0000) >> 16) *weight;
	sum[2] += (double)((pixel & 0x0000FF00) >> 8) *weight;
	sum[3] += (double)(pixel & 0x000000FF) *weight;
}

static uint32_t	get_resized_pixel(t_specs specs, double x, double y)
{
	double		sum[4];
	t_ulpoint	start;
	t_ulpoint	end;
	t_ulpoint	curr;

	ft_bzero(sum, 4 * sizeof(double));
	start = (t_ulpoint){.x = (size_t)floor(x), .y = (size_t)floor(y)};
	end = (t_ulpoint){.x = (size_t)ceil(x + specs.mapping.x),
		.y = (size_t)ceil(y + specs.mapping.y)};
	curr.y = start.y;
	while (curr.y < end.y)
	{
		curr.x = start.x;
		while (curr.x < end.x)
		{
			add_pixel(sum, specs.img_src[curr.y * specs.size_line + curr.x],
				(fmin(x + specs.mapping.x, (double)curr.x + 1.)
					- fmax(x, (double)curr.x))
				* (fmin(y + specs.mapping.y, (double)curr.y + 1.)
					- fmax(y, (double)curr.y)));
			curr.x++;
		}
		curr.y++;
	}
	return (average_pixel(sum, specs.mapping.x * specs.mapping.y));
}

void	resize_image(t_img *image, t_specs specs)
{
	size_t	y_dst;
	size_t	x_dst;
	double	y_src;
	double	x_src;

	y_dst = 0;
	y_src = 0.;
	while (y_dst < specs.dim_dst.h)
	{
		x_dst = 0;
		x_src = 0.;
		while (x_dst < specs.dim_dst.w)
		{
			image->px[y_dst * image->w + x_dst]
				= get_resized_pixel(specs, x_src, y_src);
			x_dst++;
			x_src += specs.mapping.x;
		}
		y_dst++;
		y_src += specs.mapping.y;
	}
}
