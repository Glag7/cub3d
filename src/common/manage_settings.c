/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_settings.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 16:35:17 by glaguyon          #+#    #+#             */
/*   Updated: 2024/06/23 17:27:05 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "set.h"
#include "mini.h"
#include <math.h>

void	init_settings(t_set *set)
{
	set->ncase = DEF_NCASE;
	set_diameter(set, DEF_D);
	set->xoffset = DEF_OFFSET;
	set->yoffset = DEF_OFFSET;
	set->ncolor = DEF_NCOLOR;
	set->color = DEF_COLOR;
	set->pcolor = DEF_PCOLOR;
	set->fov = DEF_FOV * M_PI / 180.;
	set->view = DEF_VIEW;
	set->wid = DEF_WID;
	set->hei = DEF_HEI;
	set->offthread = 0;
	set->nthread = 1;
}
