/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_settings.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 16:35:17 by glaguyon          #+#    #+#             */
/*   Updated: 2024/10/09 21:24:01 by glag             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include "set.h"
#include "mini.h"

int	init_settings(t_set *set)
{
	set->wid = DEF_WID;
	set->invwid = 1. / (double)(set->wid - 1);
	set->hei = DEF_HEI;
	set->ncase = DEF_NCASE;
	set_diameter(set, DEF_D);
	set->xoffset = DEF_OFFSET;
	set->yoffset = DEF_OFFSET;
	set->ncolor = DEF_NCOLOR;
	set->color = DEF_COLOR;
	set->pcolor = DEF_PCOLOR;
	set->crosscolor = DEF_CROSSCOLOR;
	set->view = DEF_VIEW;
	set->sensi = DEF_SENSI;
	set->texsiz = DEF_TEXSIZ;
	set->skysiz = DEF_SKYSIZ;
	return (setfov(set, DEF_FOV));
}

static void	get_raylen(t_set *set)
{
	size_t	i;
	double	cur;
	double	inc;

	cur = set->tanfov;
	inc = -2. * set->tanfov * set->invwid;
	i = 0;
	while (i < set->wid)
	{
		set->invlen[i] = 1. / sqrt(1. + cur * cur);
		set->coslen[i] = cos(atan2(cur * set->invlen[i], set->invlen[i]));
		++i;
		cur += inc;
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
	free(set->invlen);
	set->invlen = malloc(set->wid * sizeof(*set->invlen));
	if (set->invlen == NULL)
		return (1);
	free(set->coslen);
	set->coslen = malloc(set->wid * sizeof(*set->coslen));
	if (set->coslen == NULL)
	{
		free(set->invlen);
		return (1);
	}
	get_raylen(set);
	return (0);
}

void	free_settings(t_set *set)
{
	free(set->invlen);
	free(set->coslen);
}
