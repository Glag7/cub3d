/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrave <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 12:23:10 by ttrave            #+#    #+#             */
/*   Updated: 2024/08/07 17:33:05 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "specs.h"
#include "err.h"
#include "mlx.h"
#include "utils.h"
#include "map.h"
#include "parsing.h"

static int	get_mlx_img(void *mlx, char *path, t_specs *specs)
{
	int	w;
	int	h;

	specs->img_mlx = mlx_xpm_file_to_image(mlx, path, &w, &h);
	if (specs->img_mlx == NULL)
	{
		ft_perror(ERR_MLX_XPM);
		return (1);
	}
	specs->dim_src = (t_dim){.w = (size_t)w, .h = (size_t)h};
	return (0);
}

static int	get_xpm_img(void *mlx, char *path, t_specs *specs)
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
	specs->img_src = (uint32_t *)mlx_get_data_addr(specs->img_mlx,
			&null, &size_line, &null);
	specs->size_line = (size_t)size_line / sizeof(uint32_t);
	return (0);
}

static int	check_format(char *filename, char *format)
{
	int	i_filename;
	int	i_format;

	i_filename = 0;
	while (filename[i_filename] != '\0')
		i_filename++;
	i_format = 0;
	while (format[i_format] != '\0')
		i_format++;
	while (i_filename >= 0 && i_format >= 0
		&& filename[i_filename] == format[i_format])
	{
		i_filename--;
		i_format--;
	}
	return (i_format == -1 && i_filename >= 0 && filename[i_filename] == '.');
}

static int	img_resize(t_img *image, t_specs *specs, void *mlx, t_dim dim)
{
	specs->dim_dst = dim;
	specs->mapping = (t_point){.x = (double)specs->dim_src.w
		/ (double)specs->dim_dst.w,
		.y = (double)specs->dim_src.h / (double)specs->dim_dst.h};
	image->w = specs->dim_dst.w;
	image->h = specs->dim_dst.h;
	image->px = malloc(image->w * image->h * sizeof(uint32_t));
	if (image->px == NULL)
	{
		if (specs->img_mlx != NULL)
			mlx_destroy_image(mlx, specs->img_mlx);
		else
			free(specs->img_src);
		ft_perror(ERR_MALLOC);
		return (1);
	}
	resize_image(image, *specs);
	if (specs->img_mlx != NULL)
		mlx_destroy_image(mlx, specs->img_mlx);
	else
		free(specs->img_src);
	return (0);
}

int	load_img(void *mlx, char *path, t_img *image, t_dim dim)
{
	t_specs	specs;
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
	if (c != '\0')
		path[i] = '\0';
	if (check_format(path, "xpm") == 1 && get_xpm_img(mlx, path, &specs) == 1)
		return (1);
	else if (check_format(path, "bmp") == 1 && get_bmp_img(path, &specs) == 1)
		return (1);
	else if (check_format(path, "xpm") == 0 && check_format(path, "bmp") == 0)
		ft_perror(ERR_IMG_EXT);
	if (check_format(path, "xpm") == 0 && check_format(path, "bmp") == 0)
		return (1);
	if (c != '\0')
		path[i] = c;
	return (img_resize(image, &specs, mlx, dim));
}
