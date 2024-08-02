/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_settings.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 16:35:17 by glaguyon          #+#    #+#             */
/*   Updated: 2024/08/02 17:15:04 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "set.h"
#include "mini.h"
#include <math.h>

void	init_settings(t_set *set)
{
	set->wid = DEF_WID;//
	set->hei = DEF_HEI;//
	set->ncase = DEF_NCASE;
	set_diameter(set, DEF_D);
	set->xoffset = DEF_OFFSET;
	set->yoffset = DEF_OFFSET;
	set->ncolor = DEF_NCOLOR;
	set->color = DEF_COLOR;
	set->pcolor = DEF_PCOLOR;
	setfov(set, DEF_FOV);
	set->view = DEF_VIEW;//increase ?
	set->sensi = DEF_SENSI;
	set->offthread = 0;
	set->nthread = 1;
}

//wid and hei must be set
int	setfov(t_set *set, double fov_deg)
{
	set->fov_deg = fov_deg;
	set->fov = fov_deg * M_PI / 180.;
	set->tanfov = tan(set->fov * .5);
	set->planwid = (double)set->wid / (set->tanfov * 2.);
	return (0);
}
