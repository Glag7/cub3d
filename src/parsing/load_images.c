/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrave <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 12:23:10 by ttrave            #+#    #+#             */
/*   Updated: 2024/06/14 15:53:10 by ttrave           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

static	()
{
	;
}

static int32_t	get_image_data(void *mlx, t_img *image, char *path)
{
	void		*mlx_img;
	int32_t		dim_img[2];
	int32_t		dim_rect[2];
	int32_t		nb_rect[2];

	mlx_img = mlx_xpm_file_to_image(mlx, path, &dim_img[0], &dim_img[1]);
	if (mlx_img == NULL)
	{
		ft_perror(ERROR_MLX_XPM);
		return (1);
	}
	if (dim_img[0] < dim_img[1])
		image->size = dim_img[0];
	else
		image->size = dim_img[1];
	compress_image(mlx, mlx_img, dim_img, dim_rect);
	return (0);
}

t_img	*load_img(void *mlx, char *path)//path est considere comme valide (erreur mlx sinon)
{
	t_img		*image;
	uint64_t	size;

	image = malloc(sizeof(t_image));
	if (image == NULL)
	{
		ft_perror(ERROR_MALLOC);
		return (NULL);
	}
	if (get_image_data(mlx, image, path))
	{
		free(image);
		return (NULL);
	}
	if (image->colors == NULL)
	{
		free(image);
		ft_perror(ERROE_MALLOC);
		return (NULL);
	}
	return (image)
}
