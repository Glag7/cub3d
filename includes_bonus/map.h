/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 14:29:41 by glaguyon          #+#    #+#             */
/*   Updated: 2024/06/22 15:52:26 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# include <stdint.h>
# include <stddef.h>

typedef struct s_img
{
	uint32_t	*px;
	size_t		w;
	size_t		h;
}	t_img;

typedef struct s_map
{
	uint8_t			*map;
	unsigned int	hei;
	unsigned int	wid;
	t_img			n;
	t_img			s;
	t_img			w;
	t_img			e;
	uint32_t		floor;
	uint32_t		ceil;
}	t_map;

void	free_map(t_map *map);

#endif
