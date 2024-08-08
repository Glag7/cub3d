/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_settings.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 16:35:17 by glaguyon          #+#    #+#             */
/*   Updated: 2024/08/08 13:44:19 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include "set.h"
#include "mini.h"
#include "point.h"

int	init_settings(t_set *set)
{
	set->wid = DEF_WID;//
	set->invwid = 1. / (double)(set->wid - 1);
	set->hei = DEF_HEI;//
	set->ncase = DEF_NCASE;
	set_diameter(set, DEF_D);
	set->xoffset = DEF_OFFSET;
	set->yoffset = DEF_OFFSET;
	set->ncolor = DEF_NCOLOR;
	set->color = DEF_COLOR;
	set->pcolor = DEF_PCOLOR;
	set->view = DEF_VIEW;//increase ?
	set->sensi = DEF_SENSI;
	set->texsiz = DEF_TEXSIZ;
	set->skysiz = DEF_SKYSIZ;
	
	return (setfov(set, DEF_FOV));//TODO FUNC DE FREE
}

static void	get_raylen(t_set *set)
{
	size_t	i;
	t_point	cur;
	t_point	end;
	t_point	inc;
	t_point	vec;

	cur.x = 1.;
	cur.y = set->tanfov;
	end.x = 1.;
	end.y = -set->tanfov;
	inc = (t_point){(end.x - cur.x) * set->invwid,
		(end.y - cur.y) * set->invwid};
	cur = (t_point){cur.x + inc.x,
		cur.y + inc.y};
	i = 0;
	while (i < set->wid)
	{
		vec = (t_point){cur.x - 0, cur.y - 0};
		set->invlen[i] = 1. / sqrt(vec.x * vec.x + vec.y * vec.y);
		++i;
		cur.x += inc.x;
		cur.y += inc.y;
	}
}

//wid and hei must be set
int	setfov(t_set *set, double fov_deg)
{
	set->fov_deg = fov_deg;
	set->fov = fov_deg * M_PI / 180.;
	set->tanfov = tan(set->fov * .5);
	set->planwid = (double)set->wid / (set->tanfov * 2.);
	set->invplanwid = 1. / set->planwid;
	set->invlen = malloc(set->wid * sizeof(*set->invlen));
	if (set->invlen == NULL)
		return (1);
	get_raylen(set);
	return (0);
}
