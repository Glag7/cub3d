/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 14:29:41 by glaguyon          #+#    #+#             */
/*   Updated: 2024/08/14 18:45:37 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# include <stdint.h>
# include <stddef.h>

//full block
# define CUBE		0b00000000000000000000000000000011
//door/glass/fence
# define SPEC		0b00000000000000000000000000001100
//side to render spec
# define SIDE		0b00000000000000000000000000010000
//special value
# define VALUE		0b11111111111111111111111111100000
# define VALUEOFF	5

# define XSIDE		0b00000000000000000000000000010000
# define XSIDE		0b00000000000000000000000000000000

# define GLASS		0b00000000000000000000000000000100
# define XGLASS		0b00000000000000000000000000010100
# define YGLASS		0b00000000000000000000000000000100

# define DOOR		0b00000000000000000000000000001000
# define XDOOR		0b00000000000000000000000000011000
# define YDOOR		0b00000000000000000000000000001000

# define FENCE		0b00000000000000000000000000001100
# define XFENCE		0b00000000000000000000000000011100
# define YFENCE		0b00000000000000000000000000001100

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
	t_img			f;
	t_img			c;
	t_img			d;
}	t_map;

void	free_map(t_map *map);

#endif
