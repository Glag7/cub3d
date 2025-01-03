/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrave <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 18:49:22 by ttrave            #+#    #+#             */
/*   Updated: 2024/06/28 18:30:27 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <math.h>
#include "epic_norminette_fail.h"
#include "utils.h"
#include "specs.h"
#include "map.h"
#include "mlx.h"
#include "err.h"

static inline void	add_pixel(uint32_t *sum, uint32_t pixel, double weight)
{
	sum[3] += ((pixel & 0xFF000000) >> 24) * weight;
	sum[2] += ((pixel & 0x00FF0000) >> 16) * weight;
	sum[1] += ((pixel & 0x0000FF00) >> 8) * weight;
	sum[0] += (pixel & 0x000000FF) * weight;
}

static uint32_t	get_average_lin(void *img_specs_ptr, double lin, double col,
		double offset)
{
	const t_specs	*img = (t_specs *)img_specs_ptr;
	uint32_t		sum[4];
	uint32_t		pixel;
	double			max;
	double			pixel_part;

	ft_bzero(sum, 4 * sizeof(uint32_t));
	max = lin + offset;
	while ((max - lin) >= 1.0)
	{
		pixel_part = floor(lin) + 1.0 - lin;
		pixel = *(uint32_t *)(img->img_bin + (size_t)lin * img->size_line
				+ (size_t)col * sizeof(uint32_t));
		add_pixel(sum, pixel, pixel_part);
		lin = floor(lin + pixel_part);
	}
	pixel = *(uint32_t *)&(((t_specs *)img_specs_ptr)->img_bin[((size_t)lin
				* ((t_specs *)img_specs_ptr)->size_line)
			+ ((size_t)col * sizeof(uint32_t))]);
	add_pixel(sum, pixel, max - lin);
	sum[0] = (uint32_t)((double)(sum[0]) / offset);
	sum[1] = (uint32_t)((double)(sum[1]) / offset);
	sum[2] = (uint32_t)((double)(sum[2]) / offset);
	sum[3] = (uint32_t)((double)(sum[3]) / offset);
	return ((sum[3] << 24) | (sum[2] << 16) | (sum[1] << 8) | sum[0]);
}

static uint32_t	get_average_col(void *img_specs_ptr, double lin, double col,
		double offset)
{
	const t_specs	*img = (t_specs *)img_specs_ptr;
	uint32_t		sum[4];
	uint32_t		pixel;
	double			max;
	double			pixel_part;

	ft_bzero(sum, 4 * sizeof(uint32_t));
	max = col + offset;
	while ((max - col) >= 1.0)
	{
		pixel_part = floor(col) + 1.0 - col;
		pixel = *(uint32_t *)(img->img_bin + (size_t)lin * img->size_line
				+ (size_t)col * sizeof(uint32_t));
		add_pixel(sum, pixel, pixel_part);
		col = floor(col + pixel_part);
	}
	pixel = *(uint32_t *)&(((t_specs *)img_specs_ptr)->img_bin[((size_t)lin
				* ((t_specs *)img_specs_ptr)->size_line)
			+ ((size_t)col * sizeof(uint32_t))]);
	add_pixel(sum, pixel, max - col);
	sum[0] = (uint32_t)((double)(sum[0]) / offset);
	sum[1] = (uint32_t)((double)(sum[1]) / offset);
	sum[2] = (uint32_t)((double)(sum[2]) / offset);
	sum[3] = (uint32_t)((double)(sum[3]) / offset);
	return ((sum[3] << 24) | (sum[2] << 16) | (sum[1] << 8) | sum[0]);
}

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
	lin = 0.;
	while (lin + 0.5 < (double)img_specs.h)
	{
		col = 0.;
		while (col + 0.5 < (double)img_specs.w)
		{
			image->px[i_image] = f(&img_specs, lin, col, offset);
			col += img_specs.dim_rect[0];
			i_image++;
		}
		lin += img_specs.dim_rect[1];
	}
}
