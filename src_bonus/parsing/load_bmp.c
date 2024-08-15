/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_bmp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrave <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 13:33:24 by ttrave            #+#    #+#             */
/*   Updated: 2024/08/15 19:01:40 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "bmp.h"
#include "utils.h"
#include "err.h"
#include "specs.h"

static int	check_data(t_bmp_hdr *hdr, t_bmp_info *info)
{
	if (hdr->file_type != 0x4D42)
	{
		ft_perror(ERR_FORMAT);
		return (1);
	}
	if (info->width <= 0 || info->height <= 0)
	{
		ft_perror(ERR_IMG_SIZE);
		return (1);
	}
	if (info->bpp != 32)
	{
		ft_perror(ERR_BPP);
		return (1);
	}
	return (0);
}

static int	get_headers(char *path,
	t_bmp_hdr *hdr, t_bmp_info *info, int *fd_ptr)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		ft_perror(ERR_OPEN_IMG);
		return (1);
	}
	if (read(fd, hdr, sizeof(t_bmp_hdr)) != sizeof(t_bmp_hdr)
		|| read(fd, info, sizeof(t_bmp_info)) != sizeof(t_bmp_info))
	{
		close(fd);
		ft_perror(ERR_READ);
		return (1);
	}
	if (check_data(hdr, info) == 1)
	{
		close(fd);
		return (1);
	}
	*fd_ptr = fd;
	return (0);
}

static void	format_image(t_specs *specs)
{
	size_t		lin;
	size_t		col;
	uint32_t	pixel;

	lin = specs->dim_src.h - 1;
	while (lin >= specs->dim_src.h / 2)
	{
		col = 0;
		while (col < specs->dim_src.w)
		{
			pixel = specs->img_src[lin * specs->dim_src.w + col];
			specs->img_src[lin * specs->dim_src.w + col]
				= specs->img_src[(specs->dim_src.h - lin - 1)
				* specs->dim_src.w + col];
			specs->img_src[(specs->dim_src.h - lin - 1)
				* specs->dim_src.w + col] = pixel;
			++col;
		}
		--lin;
	}
}

static int	read_image(int fd, t_specs *specs, t_bmp_hdr *hdr)
{
	void	*null;

	null = malloc(hdr->img_offset - sizeof(t_bmp_hdr) - sizeof(t_bmp_info));
	if (null == NULL)
	{
		ft_perror(ERR_MALLOC);
		return (1);
	}
	if (read(fd, null, hdr->img_offset - sizeof(t_bmp_hdr) - sizeof(t_bmp_info))
		!= hdr->img_offset - sizeof(t_bmp_hdr) - sizeof(t_bmp_info))
	{
		free(null);
		ft_perror(ERR_READ);
		return (1);
	}
	free(null);
	if (read(fd, specs->img_src, specs->dim_src.h * specs->dim_src.w
			* sizeof(uint32_t)) != (long)(specs->dim_src.h
		* specs->dim_src.w * sizeof(uint32_t)))
	{
		ft_perror(ERR_READ);
		return (1);
	}
	format_image(specs);
	return (0);
}

int	get_bmp_img(char *path, t_specs *specs)
{
	t_bmp_hdr	hdr;
	t_bmp_info	info;
	int			fd;

	specs->img_mlx = NULL;
	if (get_headers(path, &hdr, &info, &fd) == 1)
		return (1);
	specs->dim_src = (t_dim){.w = (size_t)info.width, .h = (size_t)info.height};
	specs->size_line = info.width;
	specs->img_src = malloc(info.width * info.height * sizeof(uint32_t));
	if (specs->img_src == NULL)
	{
		close(fd);
		ft_perror(ERR_MALLOC);
		return (1);
	}
	if (read_image(fd, specs, &hdr) == 1)
	{
		free(specs->img_src);
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}
