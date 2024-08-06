/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrave <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 12:23:10 by ttrave            #+#    #+#             */
/*   Updated: 2024/08/06 19:03:22 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "specs.h"
#include "err.h"
#include "mlx.h"
#include "utils.h"
#include "map.h"
#include "parsing.h"

static int	get_mlx_img(void *mlx, char *path, t_specs *specs)
{
	size_t	i;
	char	c;
	int		w;
	int		h;

	i = 0;
	while (path[i] != '\0')
		i++;
	while (i > 0 && (path[i] == ' ' || path[i] == '\0'))
		i--;
	if (path[i] != ' ' && path[i] != '\0')
		i++;
	c = path[i];
	if (c != '\0')
		path[i] = '\0';
	specs->img_mlx = mlx_xpm_file_to_image(mlx, path, &w, &h);
	if (c != '\0')
		path[i] = c;
	if (specs->img_mlx == NULL)
	{
		ft_perror(ERR_MLX_XPM);
		return (1);
	}
	specs->dim_src = (t_dim){.w = (size_t)w, .h = (size_t)h};
	return (0);
}

static int	init_specs(void *mlx, char *path, t_specs *specs, t_dim dim)
{
	int	null;
	int	size_line;

	if (get_mlx_img(mlx, path, specs) == 1)
		return (1);
	if (specs->dim_src.w == 0 || specs->dim_src.h == 0)
	{
		mlx_destroy_image(mlx, specs->img_mlx);
		ft_perror(ERR_IMG_SIZE);
		return (1);
	}
	specs->img_src = (uint32_t *)mlx_get_data_addr(
			specs->img_mlx, &null, &size_line, &null);
	specs->size_line = (size_t)size_line / sizeof(uint32_t);
	specs->dim_dst = dim;
	specs->mapping = (t_point){.x = (double)specs->dim_src.w
		/ (double)specs->dim_dst.w,
		.y = (double)specs->dim_src.h / (double)specs->dim_dst.h};
	return (0);
}

int	load_img(void *mlx, char *path, t_img *image, t_dim dim)
{
	t_specs	specs;

	if (init_specs(mlx, path, &specs, dim) == 1)
		return (1);
	image->w = specs.dim_dst.w;
	image->h = specs.dim_dst.h;
	image->px = malloc(image->w * image->h * sizeof(uint32_t));
	if (image->px == NULL)
	{
		mlx_destroy_image(mlx, specs.img_mlx);
		ft_perror(ERR_MALLOC);
		return (1);
	}
	resize_image(image, specs);
	mlx_destroy_image(mlx, specs.img_mlx);
	return (0);
}
