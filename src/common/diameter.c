/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diameter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 19:04:15 by glaguyon          #+#    #+#             */
/*   Updated: 2024/06/22 19:16:45 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"
#include "set.h"

void	set_diameter(t_set *set, unsigned int d)
{
	set->d = d;
	set->r = d / 2;
	set->pstart = set->r - set->d / (set->ncase * 10);
	set->pend = set->r + set->d / (set->ncase * 10);
	set->ratio = (double)set->d / (double)set->ncase;
}
