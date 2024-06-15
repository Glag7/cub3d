/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 14:29:41 by glaguyon          #+#    #+#             */
/*   Updated: 2024/06/14 14:33:41 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

/* ----- INCLUDES ----- */

# include "mlx.h"
# include "utils.h"
# include <stdint.h>
# include <stdlib.h>
# include <stdbool.h>

/* ----- STRUCTURES ----- */

// Raw image caracteristics
typedef struct s_specs
{
	void	*mlx_img;
	char	*img_bin;
	int32_t	bpp;
	int32_t	size_line;
	bool	endian;
	int32_t	w;
	int32_t	h;
	double	dim_rect[2];
}	t_specs;

// Final resized image
typedef struct s_image
{
	uint32_t	*px;
	uint64_t	size;
}	t_img;

// Map
typedef struct s_map
{
	uint8_t		*map;
	t_img		*n;
	t_img		*s;
	t_img		*w;
	t_img		*e;
	uint32_t	floor;
	uint32_t	ceil;
}	t_map;

/* ----- MACROS ----- */

// Error strings
# define ERROR_MLX_XPM	"mlx_xpm_file_to_image(): failed to initialize image\n"
# define ERROR_MALLOC	"malloc(): failed memory allocation\n"
# define ERROR_BPP	"Too many bits per pixel in an image (32 maximum)\n"
# define ERROR_IMG_SIZE	"Image has a size of 0\n"

/* ----- PROTOTYPES ----- */

// load_images.c
int		load_img(void *mlx, char *path, t_img *img);

#endif
