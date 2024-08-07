/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrave   <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 15:04:17 by ttrave            #+#    #+#             */
/*   Updated: 2024/08/07 16:11:34 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BMP_H
# define BMP_H

/* ----- INCLUDES ----- */

# include <stdint.h>

/* ----- STRUCTURES ----- */

typedef struct __attribute__((__packed__)) s_hdr
{
	uint16_t	file_type;
	uint32_t	file_size;
	uint32_t	unused;
	uint32_t	img_offset;
}	t_bmp_hdr;

typedef struct __attribute__((__packed__)) s_info
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

#endif
