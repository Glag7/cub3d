/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrave <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 12:23:10 by ttrave            #+#    #+#             */
/*   Updated: 2024/06/16 19:12:43 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include "parsing.h"
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

static int	convert_image(t_img *image, t_specs img_specs)
{
	image->px = malloc((image->size * image->size) * sizeof(uint32_t));
	if (image->px == NULL)
	{
		ft_perror(ERR_MALLOC);
		return (1);
	}
	read_image(image, img_specs);
	return (0);
}

static int	get_mlx_img(void *mlx, char *path, t_specs *img_specs)
{
	size_t	i;
	char	c;

	i = 0;
	while (path[i] != '\0')
		i++;
	while (i > 0 && (path[i] == ' ' || path[i] == '\0'))
		i--;
	if (path[i] != ' ' && path[i] != '\0')
		i++;
	c = path[i];
	path[i] = '\0';
	img_specs->mlx_img = mlx_xpm_file_to_image(mlx, path, &(img_specs->w),
			&(img_specs->h));
	path[i] = c;
	if (img_specs->mlx_img == NULL)
		return (1);
	return (0);
}

int	load_img(void *mlx, char *path, t_img *image)
{
	t_specs	img_specs;

	if (get_mlx_img(mlx, path, &img_specs) == 1)
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
	if (init_dimensions(&img_specs) == 1
		|| convert_image(image, img_specs) == 1)
	{
		mlx_destroy_image(mlx, img_specs.mlx_img);
		return (1);
	}
	mlx_destroy_image(mlx, img_specs.mlx_img);
	return (0);
}
