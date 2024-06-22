/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_settings.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 16:35:17 by glaguyon          #+#    #+#             */
/*   Updated: 2024/06/22 16:45:22 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "set.h"
#include <math.h>

void	init_settings(t_set *set)
{
	set->d = DEF_D;
	set->r = set->d / 2;
	set->offset = DEF_OFFSET;
	set->ncase = DEF_NCASE;
	set->ncolor = DEF_NCOLOR;
	set->color = DEF_COLOR;
	set->pcolor = DEF_PCOLOR;
	set->fov = DEF_FOV * M_PI / 180.;
	set->view = DEF_VIEW;
	set->lwid = DEF_LWID;
	set->wid = DEF_WID;
	set->hei = DEF_HEI;
}
