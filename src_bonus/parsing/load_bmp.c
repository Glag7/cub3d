/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_bmp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrave <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 13:33:24 by ttrave            #+#    #+#             */
/*   Updated: 2024/08/07 14:54:44 by glaguyon         ###   ########.fr       */
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
	if (((hdr->file_type >> 8) & 255) != 'M' || (hdr->file_type & 255) != 'B')// bizarre l'ordre
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
	if (0 && info->compression != 0)
	{
		ft_perror(ERR_COMPRESS);
		return (1);
	}
	return (0);
}

static int	get_headers(char *path, t_bmp_hdr *hdr, t_bmp_info *info, int *fd_ptr)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		ft_perror(ERR_OPEN);
		return (1);
	}
	if (read(fd, hdr, sizeof(t_bmp_hdr)) != sizeof(t_bmp_hdr) || read(fd, info, sizeof(t_bmp_info)) != sizeof(t_bmp_info))
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
	info->bpp /= 8;
	*fd_ptr = fd;
	return (0);
}

static void	format_image(t_specs *specs)//, t_bmp_info *info)
{
//	size_t	size_line;
	size_t	lin;
	size_t	col;
	uint32_t	pixel;

//	size_line = info->width * info->bpp;
//	if (size_line % 4 != 0)
//		size_line += 4 - ((info->width * info->bpp) % 4);
	lin = specs->dim_src.h;
	while (lin > 0)
	{
		lin--;
		col = 0;
		while (col < specs->dim_src.w)
		{
			pixel = specs->img_src[lin * specs->dim_src.w + col];
			specs->img_src[lin * specs->dim_src.w + col] = specs->img_src[(specs->dim_src.h - lin - 1) * specs->dim_src.w + col];
			specs->img_src[(specs->dim_src.h - lin - 1) * specs->dim_src.w + col] = pixel;
			col++;
		}
	}
}

static int	read_image(int fd, t_specs *specs, t_bmp_hdr *hdr)//, t_bmp_info *info)
{
	void	*null;

	null = malloc(hdr->img_offset - sizeof(t_bmp_hdr) - sizeof(t_bmp_info));
	if (null == NULL)
	{
		ft_perror(ERR_MALLOC);
		return (1);
	}
	if (read(fd, null, hdr->img_offset - sizeof(t_bmp_hdr) - sizeof(t_bmp_info)) == -1)
	{
		free(null);
		ft_perror(ERR_READ);
		return (1);
	}
	free(null);
	if (read(fd, specs->img_src, specs->dim_src.h * specs->size_line) == -1)
	{
		ft_perror(ERR_MALLOC);
		return (1);
	}
	format_image(specs);//, info);
	return (0);
}

int	get_bmp_img(char *path, t_specs *specs)
{
	t_bmp_hdr	hdr;
	t_bmp_info	info;
	int		fd;

	specs->img_mlx = NULL;
	if (get_headers(path, &hdr, &info, &fd) == 1)
		return (1);
	specs->dim_src = (t_dim){.w = (size_t)info.width, .h = (size_t)info.height};
	specs->size_line = info.width * sizeof(uint32_t);
	specs->img_src = malloc(info.width * info.height * sizeof(uint32_t));
	if (specs->img_src == NULL)
	{
		close(fd);
		ft_perror(ERR_MALLOC);
		return (1);
	}
	if (read_image(fd, specs, &hdr) == 1)//, &info) == 1)
	{
		free(specs->img_src);
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}


int *read_bmp(const char *file_path, size_t *yes) {
    FILE *file = fopen(file_path, "rb");
    if (!file) {
        perror("Erreur lors de l'ouverture du fichier");
        return 0;
    }

    BITMAPFILEHEADER fileHeader;
    fread(&fileHeader, sizeof(BITMAPFILEHEADER), 1, file);

    if (fileHeader.bfType != 0x4D42) {
        fprintf(stderr, "Ce n'est pas un fichier BMP valide.\n");
        fclose(file);
        return 0;
    }

    BITMAPINFOHEADER infoHeader;
    fread(&infoHeader, sizeof(BITMAPINFOHEADER), 1, file);

    if (infoHeader.biBitCount != 32) {
        fprintf(stderr, "Ce fichier BMP n'est pas en 32 bits.\n");
        fclose(file);
        return 0;
    }

    *yes =  infoHeader.biWidth;
    printf("Largeur: %d pixels\n", infoHeader.biWidth);
    printf("Hauteur: %d pixels\n", infoHeader.biHeight);

    // Allocation de mémoire pour les pixels
    uint32_t *pixels = (uint32_t *)malloc(infoHeader.biWidth * infoHeader.biHeight * sizeof(uint32_t));
    if (!pixels) {
        fprintf(stderr, "Erreur d'allocation de mémoire.\n");
        fclose(file);
        return 0;
    }

    fseek(file, fileHeader.bfOffBits, SEEK_SET);
    fread(pixels, sizeof(uint32_t), infoHeader.biWidth * infoHeader.biHeight, file);

    // Affichage de la valeur RGBA du premier pixel
    uint32_t firstPixel = pixels[0];
    uint8_t r = (firstPixel >> 16) & 0xFF;
    uint8_t g = (firstPixel >> 8) & 0xFF;
    uint8_t b = firstPixel & 0xFF;
    uint8_t a = (firstPixel >> 24) & 0xFF;

    printf("Premier pixel - R: %d, G: %d, B: %d, A: %d\n", r, g, b, a);

    return (pixels);
    fclose(file);
}
