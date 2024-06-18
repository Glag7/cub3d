/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrave <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 18:49:22 by ttrave            #+#    #+#             */
/*   Updated: 2024/06/18 16:53:25 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <math.h>
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

static uint32_t	get_average_lin(void *img_specs_ptr, double lin, double col,
		double offset)
{
	uint32_t	sum[4];
	uint32_t	pixel;
	double		max;
	double		pixel_part;

	ft_bzero(sum, 4 * sizeof(uint32_t));
	max = lin + offset;
	while ((max - lin) >= 1.0)
	{
		pixel_part = floor(lin) + 1.0 - lin;
		pixel = get_pixel(*((t_specs *)img_specs_ptr), (size_t)lin,
				(size_t)col);
		add_pixel(sum, pixel, pixel_part);
		lin = floor(lin + pixel_part);
	}
	pixel_part = max - lin;
	pixel = get_pixel(*((t_specs *)img_specs_ptr), (size_t)lin, (size_t)col);
	add_pixel(sum, pixel, pixel_part);
	sum[0] = (uint32_t)((double)(sum[0]) / offset);
	sum[1] = (uint32_t)((double)(sum[1]) / offset);
	sum[2] = (uint32_t)((double)(sum[2]) / offset);
	sum[3] = (uint32_t)((double)(sum[3]) / offset);
	return ((sum[3] << 24) | (sum[2] << 16) | (sum[1] << 8) | sum[0]);
}

static uint32_t	get_average_col(void *img_specs_ptr, double lin, double col,
		double offset)
{
	uint32_t	sum[4];
	uint32_t	pixel;
	double		max;
	double		pixel_part;

	ft_bzero(sum, 4 * sizeof(uint32_t));
	max = col + offset;
	while ((max - col) >= 1.0)
	{
		pixel_part = floor(col) + 1.0 - col;
		pixel = get_pixel(*((t_specs *)img_specs_ptr), (size_t)lin,
				(size_t)col);
		add_pixel(sum, pixel, pixel_part);
		col = floor(col + pixel_part);
	}
	pixel_part = max - col;
	pixel = get_pixel(*((t_specs *)img_specs_ptr), (size_t)lin, (size_t)col);
	add_pixel(sum, pixel, pixel_part);
	sum[0] = (uint32_t)((double)(sum[0]) / offset);
	sum[1] = (uint32_t)((double)(sum[1]) / offset);
	sum[2] = (uint32_t)((double)(sum[2]) / offset);
	sum[3] = (uint32_t)((double)(sum[3]) / offset);
	return ((sum[3] << 24) | (sum[2] << 16) | (sum[1] << 8) | sum[0]);
}

//what the fuck, norminette ?
typedef double	t_d;
typedef size_t	t_s;

void	read_image(t_img *image, t_specs img_specs)
{
	t_d	lin;
	t_d	col;
	t_d	offset;
	t_s	i_image;
	uint32_t
		(*f)(void *, double, double, double);

	offset = img_specs.dim_rect[img_specs.dim_rect[0] == 1.0];
	if (img_specs.dim_rect[0] == 1.0)
		f = get_average_lin;
	else
		f = get_average_col;
	i_image = 0;
	lin = 0;
	while (lin + 0.9 < (double)img_specs.h)
	{
		col = 0;
		while (col + 0.9 < (double)img_specs.w)
		{
			image->px[i_image] = f(&img_specs, lin, col, offset);
			col += img_specs.dim_rect[0];
			i_image++;
		}
		lin += img_specs.dim_rect[1];
	}
}
