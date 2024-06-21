/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 14:29:41 by glaguyon          #+#    #+#             */
/*   Updated: 2024/06/21 16:41:13 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# include <stddef.h>
# include <stdint.h>

# define DEF_FOV 90.
# define DEF_LWID 1

typedef struct s_img
{
	uint32_t	*px;
	uint64_t	size;
}	t_img;

typedef struct s_player
{
	double		fov;
	double		x;
	double		y;
	double		a;
	unsigned int	lwid;
}	t_player;

typedef struct s_map
{
	uint8_t		*map;
	size_t		hei;
	size_t		wid;
	t_img		n;
	t_img		s;
	t_img		w;
	t_img		e;
	uint64_t	floor;
	uint64_t	ceil;
	t_player	player;
}	t_map;

void	free_map(t_map *map);

#endif
