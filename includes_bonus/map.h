/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 14:29:41 by glaguyon          #+#    #+#             */
/*   Updated: 2024/08/09 12:43:30 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# include <stdint.h>
# include <stddef.h>
# include "entity.h"

# define CUBE 1
# define ENTITY 2

typedef struct s_img
{
	uint32_t	*px;
	size_t		w;
	size_t		h;
}	t_img;

typedef struct s_map
{
	uint8_t			*map;
	t_ent			**entmap;
	t_ent			*entities;
	unsigned int	hei;
	unsigned int	wid;
	t_img			n;
	t_img			s;
	t_img			w;
	t_img			e;
	t_img			f;
	t_img			c;
	t_img			d;
	unsigned int	nentities;
}	t_map;

void	free_map(t_map *map);

#endif
