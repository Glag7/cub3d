/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newpos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glag <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 04:13:42 by glag              #+#    #+#             */
/*   Updated: 2024/09/26 04:41:39 by glag             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "set.h"
#include "data.h"
#include "play.h"
#include "point.h"
#include "ray.h"
#include "render.h"

#define BOUNCE .01
#define FAT .05

static inline __attribute__((always_inline)) t_point
	norm(t_point vec)
{
	const double	invlen = 1. / sqrt(vec.x * vec.x + vec.y * vec.y);

	vec.x *= invlen;
	vec.y *= invlen;
	return (vec);
}

//regarder de cb il bouge sur x et y, quand on atteint la bonne distance c bon
//ou alors faire un seul mouvement et rappeler la fonction avec le vec de vitesse change (enlever ce qui a deja ete parcouru)
//le placer si il touche un bloc ou si il a fini et return 1 ou 0
t_point	raycast_newpos(t_data *data)
{
	t_ray	ray;
	t_point	moved;

	ray.pos = (t_point){data->play.x, data->play.y};
	ray.ipos = (t_ipoint){ray.pos.x, ray.pos.y};
	ray.vec = (t_point){data->play.vx, data->play.vy};//'-'?
	init_ray(&ray);
	//check si porte sur la case
	
	ray.pos.x += ray.len * ray.vec.x;
	ray.pos.y += ray.len * ray.vec.y;
	return pos;
}
