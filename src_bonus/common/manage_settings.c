/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_settings.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 16:35:17 by glaguyon          #+#    #+#             */
/*   Updated: 2024/10/11 02:03:46 by glag             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include "set.h"
#include "mini.h"

static int	compute_settings(t_set *set)
{
	set_diameter(set, set->d);
	set->invwid = 1. / (double)(set->wid - 1);
	return (setfov(set, set->fov_deg));
}

static int	init_def(t_set *set)
{
	set->wid = DEF_WID;
	set->hei = DEF_HEI;
	set->ncase = DEF_NCASE;
	set->xoffset = DEF_OFFSET;
	set->yoffset = DEF_OFFSET;
	set->d = DEF_D;
	set->ncolor = DEF_NCOLOR;
	set->color = DEF_COLOR;
	set->pcolor = DEF_PCOLOR;
	set->crosscolor = DEF_CROSSCOLOR;
	set->view = DEF_VIEW;
	set->sensi = DEF_SENSI;
	set->texsiz = DEF_TEXSIZ;
	set->skysiz = DEF_SKYSIZ;
	set->accel = DEF_ACCEL;
	set->accelair = DEF_ACCELAIR;
	set->acceldiff = DEF_ACCELDIFF;
	set->speeddiff = DEF_SPEEDDIFF;
	set->speedmax = DEF_SPEEDMAX;
	set->faster = DEF_FASTER;
	set->slower = DEF_SLOWER;
	set->slowerair = DEF_SLOWERAIR;
	set->fov_deg = DEF_FOV;
	return (compute_settings(set));
}

int	init_settings(t_set *set)
{
	if (load_settings(set) == 0)
		return (compute_settings(set));
	return (init_def(set));
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
	if (set->invlen == NULL)
		set->invlen = malloc(set->wid * sizeof(*set->invlen));
	if (set->invlen == NULL)
		return (1);
	free(set->coslen);
	if (set->coslen == NULL)
		set->coslen = malloc(set->wid * sizeof(*set->coslen));
	if (set->coslen == NULL)
	{
		free(set->invlen);
		return (1);
	}
	get_raylen(set);
	return (0);
}
