/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrave <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 12:23:10 by ttrave            #+#    #+#             */
/*   Updated: 2024/06/15 18:47:38 by glaguyon         ###   ########.fr       */
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

static int	init_dimensions(t_specs *img_specs)
{
	int32_t	endian;

	img_specs->img_bin = mlx_get_data_addr(img_specs->mlx_img,
		&(img_specs->bpp), &(img_specs->size_line), &endian);
	if (img_specs->bpp > 32 || (img_specs->bpp & 3) != 0)
	{
		ft_perror(ERR_BPP);
		return (1);
	}
	img_specs->endian = (bool)endian;
	if (img_specs->w > img_specs->h)
	{
		img_specs->dim_rect[0] = (double)img_specs->w / (double)img_specs->h;
		img_specs->dim_rect[1] = 1;
	}
	else
	{
		img_specs->dim_rect[0] = 1;
		img_specs->dim_rect[1] = (double)img_specs->h / (double)img_specs->w;
	}
	return (0);
}

/*
// gerer endianess et bpp ici
static uint32_t	get_pixel(t_specs img_specs, size_t lin, size_t col, double intensity)
{
	uint32_t	pixel;

	;
	return (pixel);
}

static uint32_t	get_average_col(t_specs img_specs, double lin, double col)//lin = 1, col > 1
{
	uint32_t	sum[4];
	double		i;
	double		max;

	i = col;
	max = col + ;
	while (i < max)
	{
		;
	}
}

static uint32_t	get_average_lin(t_specs img_specs, double lin, double col)//col = 1, lin > 1
{
	while ()
	{
		;
	}
}

static void	read_image(t_img *image, t_specs img_specs, size_t size)
{
	size_t	i_image;
	double	lin;
	double	col;

	i_image = 0;
	lin = 0;
	while (lin < (double)img_specs.h)
	{
		col = 0;
		while (col < (double)img_specs.w)
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
}*/

static uint32_t	get_pixel(t_specs img_specs, size_t i)
{
	uint32_t	pixel;

	//pixel = 0;
	pixel = img_specs.img_bin[i];
	return (pixel);
}

static void	read_image(t_img *image, t_specs img_specs)
{
	size_t	i;

	i = 0;
	while (i < image->size)
	{
		image->px[i] = get_pixel(img_specs, i);
		i++;
	}
}

static int	convert_image(t_img *image, t_specs img_specs)
{
	image->px = malloc((image->size * image->size) * sizeof(int));
	if (image->px == NULL)
	{
		ft_perror(ERR_MALLOC);
		return (1);
	}
	read_image(image, img_specs);
	return (0);
}

int	load_img(void *mlx, char *path, t_img *image)// path finit pt par un \n au lieu de \0
{
	t_specs	img_specs;

	img_specs.mlx_img = mlx_xpm_file_to_image(mlx, path, &img_specs.w, &img_specs.h);
	if (img_specs.mlx_img == NULL)
	{
		ft_perror(ERR_MLX_XPM);
		return (1);
	}
	if (img_specs.w == 0 || img_specs.h == 0)
	{
		mlx_destroy_image(mlx, img_specs.mlx_img);
		ft_perror(ERR_IMG_SIZE);
		return (1);
	}
	if (img_specs.w < img_specs.h)
		image->size = (uint64_t)img_specs.w;
	else
		image->size = (uint64_t)img_specs.h;
	if (init_dimensions(&img_specs) == 1 || convert_image(image, img_specs) == 1)
	{
		mlx_destroy_image(mlx, img_specs.mlx_img);
		return (1);
	}
	mlx_destroy_image(mlx, img_specs.mlx_img);
	return (0);
}
