/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrave   <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 15:04:17 by ttrave            #+#    #+#             */
/*   Updated: 2024/08/07 14:55:57 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BMP_H
# define BMP_H

/* ----- INCLUDES ----- */

# include <stdint.h>

/* ----- STRUCTURES ----- */

typedef struct __attribute__((__packed__))
{
	uint16_t	file_type;
	uint32_t	file_size;
	uint32_t	unused;
	uint32_t	img_offset;
}	t_bmp_hdr;

typedef struct __attribute__((__packed__))
{
	uint32_t	hdr_size;
	int32_t		width;
	int32_t		height;
	uint16_t	planes;
	uint16_t	bpp;
	uint32_t	compression;
	uint32_t	img_size;
	int32_t		x_ppm;
	int32_t		y_ppm;
	uint32_t	n_color_map;
	uint32_t	n_sign_colors;
}	t_bmp_info;

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

#endif
