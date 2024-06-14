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

# include <stdint.h>
# include <stdlib.h>

/* ----- STRUCTURES ----- */

// Image
typedef struct s_img
{
	uint32_t	*colors;
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

/* ----- PROTOTYPES ----- */



#endif
