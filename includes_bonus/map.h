/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 14:29:41 by glaguyon          #+#    #+#             */
/*   Updated: 2024/09/03 17:24:35 by glaguyon         ###   ########.fr       */
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
//is door moving
# define MOVING		0b00000000000000000000000001100000
# define CLOSING	0b00000000000000000000000000100000
# define OPENING	0b00000000000000000000000001000000
//special value (height in x/1000)
# define VALUE		0b11111111111111111111111110000000
# define VALUEOFF	7
# define VALUEONE	65536

# define YSIDE		0b00000000000000000000000000010000
# define XSIDE		0b00000000000000000000000000000000

# define IGLASS		0
# define GLASS		0b00000000000000000000000000000100
# define YGLASS		0b00000000000000000000000000010100
# define XGLASS		0b00000000000000000000000000000100

# define IDOOR		1
# define DOOR		0b00000000000000000000000000001000
# define YDOOR		0b00000000000000000000000000011000
# define XDOOR		0b00000000000000000000000000001000

# define IFENCE		2
# define FENCE		0b00000000000000000000000000001100
# define YFENCE		0b00000000000000000000000000011100
# define XFENCE		0b00000000000000000000000000001100

typedef struct s_img
{
	uint32_t	*px;
	size_t		w;
	size_t		h;
}	t_img;

typedef struct s_map
{
	uint32_t	*map;
	unsigned int	hei;
	unsigned int	wid;
	t_img			n;
	t_img			s;
	t_img			w;
	t_img			e;
	t_img			f;
	t_img			c;
	union
	{
		struct
		{
			t_img	g;
			t_img	d;
			t_img	h;
		};
		t_img	flat[3];
	};
}	t_map;

void	free_map(t_map *map);

#endif
