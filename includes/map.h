/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 14:29:41 by glaguyon          #+#    #+#             */
/*   Updated: 2024/06/16 18:53:26 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# include <stddef.h>
# include <stdint.h>

typedef struct s_img
{
	uint32_t	*px;
	uint64_t	size;
}	t_img;

typedef struct s_player
{
	double	x;
	double	y;
	double	a;
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
	uint32_t	floor;
	uint32_t	ceil;
	t_player	player;
}	t_map;

void	free_map(t_map *map);

#endif
