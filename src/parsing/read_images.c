/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrave <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 18:49:22 by ttrave            #+#    #+#             */
/*   Updated: 2024/06/16 18:52:56 by ttrave           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include "utils.h"
#include "specs.h"
#include "map.h"
#include "mlx.h"
#include "err.h"

static uint32_t	get_pixel(t_specs img_specs, size_t lin, size_t col)
{
	uint32_t	pixel;
	uint32_t	mem;
	uint8_t		bytes_per_px;
	uint8_t		bits_per_color;
	uint8_t		byte;

	bits_per_color = img_specs.bpp / 4;
	bytes_per_px = img_specs.bpp / 8;
	mem = 0;
	ft_memcpy((void *)&mem,
		&img_specs.img_bin[((lin * img_specs.size_line)
			+ (col * bytes_per_px))], bytes_per_px);
	mem >>= (4 - bytes_per_px) * 8;
	byte = 3;
	while ((byte >> (bits_per_color - 1)) == 0)
		byte = (byte << 1) + 1;
	pixel = 0;
	pixel |= (mem >> (3 * bits_per_color)) & byte;
	pixel |= ((mem >> (2 * bits_per_color)) & byte) << 8;
	pixel |= ((mem >> bits_per_color) & byte) << 16;
	pixel |= (mem & byte) << 24;
	if (img_specs.endian == 1)
		return ((pixel & 0x000000FF) << 24 | (pixel & 0x0000FF00) << 8
			| (pixel & 0x00FF0000) >> 8 | (pixel & 0xFF000000) >> 24);
	return (pixel);
}

static void	add_pixel(uint32_t *sum, uint32_t pixel, double weight)
{
	sum[0] += ((pixel & 0xFF000000) >> 24) * weight;
	sum[1] += ((pixel & 0x00FF0000) >> 16) * weight;
	sum[2] += ((pixel & 0x0000FF00) >> 8) * weight;
	sum[3] += (pixel & 0x000000FF) * weight;
}

static uint32_t	get_average_lin(t_specs img_specs, double lin, double col)
{
	uint32_t	sum[4];
	uint32_t	pixel;
	double		i;
	double		max;
	double		pixel_part;

	ft_bzero(sum, sizeof(uint32_t) * 4);
	i = lin;
	max = lin + img_specs.dim_rect[1];
	while ((max - i) >= 1.0)
	{
		pixel_part = (double)((size_t)i + 1) - i;
		pixel = get_pixel(img_specs, (size_t)i, (size_t)col);
		add_pixel(sum, pixel, pixel_part);
		i = (double)((size_t)(i + pixel_part));
	}
	pixel_part = max - i;
	pixel = get_pixel(img_specs, (size_t)i, (size_t)col);
	add_pixel(sum, pixel, pixel_part);
	sum[0] = (uint32_t)((double)(sum[0]) / img_specs.dim_rect[1]);
	sum[1] = (uint32_t)((double)(sum[1]) / img_specs.dim_rect[1]);
	sum[2] = (uint32_t)((double)(sum[2]) / img_specs.dim_rect[1]);
	sum[3] = (uint32_t)((double)(sum[3]) / img_specs.dim_rect[1]);
	return ((sum[3] << 24) | (sum[2] << 16) | (sum[1] << 8) | sum[0]);
}

static uint32_t	get_average_col(t_specs img_specs, double lin, double col)
{
	uint32_t	sum[4];
	uint32_t	pixel;
	double		i;
	double		max;
	double		pixel_part;

	ft_bzero(sum, sizeof(uint32_t) * 4);
	i = col;
	max = col + img_specs.dim_rect[0];
	while ((max - i) >= 1.0)
	{
		pixel_part = (double)((size_t)i + 1) - i;
		pixel = get_pixel(img_specs, (size_t)lin, (size_t)i);
		add_pixel(sum, pixel, pixel_part);
		i = (double)((size_t)(i + pixel_part));
	}
	pixel_part = max - i;
	pixel = get_pixel(img_specs, (size_t)lin, (size_t)i);
	add_pixel(sum, pixel, pixel_part);
	sum[0] = (uint32_t)((double)(sum[0]) / img_specs.dim_rect[0]);
	sum[1] = (uint32_t)((double)(sum[1]) / img_specs.dim_rect[0]);
	sum[2] = (uint32_t)((double)(sum[2]) / img_specs.dim_rect[0]);
	sum[3] = (uint32_t)((double)(sum[3]) / img_specs.dim_rect[0]);
	return ((sum[3] << 24) | (sum[2] << 16) | (sum[1] << 8) | sum[0]);
}

void	read_image(t_img *image, t_specs img_specs)
{
	size_t	i_image;
	double	lin;
	double	col;

	i_image = 0;
	lin = 0;
	while (lin + 0.9 < (double)img_specs.h)
	{
		col = 0;
		while (col + 0.9 < (double)img_specs.w)
		{
			if (img_specs.dim_rect[0] == 1)
				image->px[i_image] = get_average_lin(img_specs, lin, col);
			else
				image->px[i_image] = get_average_col(img_specs, lin, col);
			col += img_specs.dim_rect[0];
			i_image++;
		}
		lin += img_specs.dim_rect[1];
	}
}
