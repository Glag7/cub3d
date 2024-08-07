/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 11:58:59 by glaguyon          #+#    #+#             */
/*   Updated: 2024/08/07 13:55:13 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// Structures pour les en-têtes BMP
#pragma pack(push, 1)
typedef struct {
    uint16_t bfType;
    uint32_t bfSize;
    uint16_t bfReserved1;
    uint16_t bfReserved2;
    uint32_t bfOffBits;
} BITMAPFILEHEADER;

typedef struct {
    uint32_t biSize;
    int32_t biWidth;
    int32_t biHeight;
    uint16_t biPlanes;
    uint16_t biBitCount;
    uint32_t biCompression;
    uint32_t biSizeImage;
    int32_t biXPelsPerMeter;
    int32_t biYPelsPerMeter;
    uint32_t biClrUsed;
    uint32_t biClrImportant;
} BITMAPINFOHEADER;
#pragma pack(pop)

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









*/

#include <X11/Xutil.h>
#include <stdlib.h>
#include <math.h>
#include "mlx.h"
#include "hooks.h"
#include "img.h"
#include "map.h"
#include "utils.h"
#include "parsing.h"
#include "err.h"
#include "data.h"
#include "render.h"

static void	start_game(t_data *data)
{//TODO data->status = MENU/SETTINGS/PAUSE/MAP/GAME

	//data->map.n.px = read_bmp("../chatgpt/image32bits.bmp", &data->map.n.w);
	mlx_mouse_hide(data->mlx.mlx, data->mlx.win);
	mlx_mouse_move(data->mlx.mlx, data->mlx.win, data->set.wid / 2,
		data->set.hei / 2);
	data->oldmouse.x = data->set.wid / 2;
	data->oldmouse.y = data->set.hei / 2;

	data->play.az = 0.;
	data->play.sina = sin(data->play.a);
	data->play.cosa = cos(data->play.a);
	mlx_hook(data->mlx.win, KeyPress, KeyPressMask, &key_hook, data);
	mlx_hook(data->mlx.win, KeyRelease, KeyReleaseMask, &unkey_hook, data);
	mlx_hook(data->mlx.win, DestroyNotify, 0, &win_hook, data);
	mlx_loop_hook(data->mlx.mlx, &loop, data);
	mlx_loop(data->mlx.mlx);
}

static int	init_data(t_data *data, int argc, char **argv)
{
	init_settings(&data->set);
	if (parse_map(data->mlx.mlx, data, argc, argv))
	{
		mlx_destroy_display(data->mlx.mlx);
		free(data->mlx.mlx);
		return (1);
	}
	if (init_mlx(&data->mlx, data->set.wid, data->set.hei))
	{
		free_map(&data->map);
		ft_perror(ERR_MLX);
		return (1);
	}
	if (init_mini(&data->mini, &data->set))
	{
		ft_perror(ERR_MALLOC);
		free_map(&data->map);
		free_mlx(&data->mlx);
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	ft_bzero(&data, sizeof(data));
	data.mlx.mlx = mlx_init();
	if (data.mlx.mlx == NULL)
	{
		ft_perror(ERR_MLX);
		return (1);
	}
	if (init_data(&data, argc, argv))
		return (1);
	start_game(&data);
	free_map(&data.map);
	free_mlx(&data.mlx);
	free_mini(&data.mini);
	return (0);
}
