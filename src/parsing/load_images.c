/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrave <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 12:23:10 by ttrave            #+#    #+#             */
/*   Updated: 2024/06/14 19:29:10 by ttrave           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

static void	init_dimensions(t_specs *img_specs)
{
	img_specs->img_bin = mlx_get_data_addr(img_specs->mlx_img, &(img_specs->bpp),
		&(img_specs->size_line), &(img_specs->endian));
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
}

// si bpp < 32 : pad avec 0
// sinon si bpp > 32 : trim les octets les plus significatifs
// si endian == 1 : inverser la lecture de la couleur (et eventuellement trim dans l'autre sens)
static void	read_image(t_img *image, t_specs img_specs)
{
	;// suite ici
}

static int	convert_image(t_img *image, t_specs img_specs)
{
	image->colors = malloc(image->size * sizeof(int));
	if (image->colors == NULL)
		return (1);
	read_image(image, img_specs);
	return (0);
}

int	load_img(void *mlx, char *path, t_img *img)
{
	t_specs	img_specs;

	img_specs.mlx_img = mlx_xpm_file_to_image(mlx, path, &dim.w, &dim.h);
	if (img_specs.mlx_img == NULL)
	{
		ft_perror(ERROR_MLX_XPM);
		return (1);
	}
	if (img_specs.w < img_specs.h)
		image->size = (uint64_t)img_specs.w;
	else
		image->size = (uint64_t)img_specs.h;
	init_dimensions(&img_specs);
	if (convert_image(image, img_specs) == 1)
	{
		mlx_destroy_image(mlx, img_specs.mlx_img);
		ft_perror(ERROR_MALLOC);
		return (1);
	}
	mlx_destroy_image(mlx, img_specs.mlx_img);
	return (0);
}
