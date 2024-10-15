/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrave <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 11:58:59 by ttrave            #+#    #+#             */
/*   Updated: 2024/09/22 19:08:10 by ttrave           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "menu.h"

uint32_t	get_pixel(uint32_t src_px, uint32_t add_px)
{
	uint32_t	new_px;
	double		transparency;

	transparency = (double)((add_px & 0xFF000000) >> 24) / 255.;
	new_px = 0;
	new_px |= 0xFF000000;
	new_px |= ((uint32_t)((double)((src_px & 0x00FF0000) >> 16)
				*(1. - transparency)) << 16)
		+ ((uint32_t)((double)((add_px & 0x00FF0000) >> 16)
				*transparency) << 16);
	new_px |= ((uint32_t)((double)((src_px & 0x0000FF00) >> 8)
				*(1. - transparency)) << 8)
		+ ((uint32_t)((double)((add_px & 0x0000FF00) >> 8) *transparency) << 8);
	new_px |= ((uint32_t)((double)(src_px & 0x000000FF) *(1. - transparency)))
		+ ((uint32_t)((double)(add_px & 0x000000FF) *transparency));
	return (new_px);
}

size_t	part(size_t n, double fraction)
{
	return ((size_t)((double)n * fraction));
}

void	free_menu(t_menu *menu)
{
	free(menu->background);
	free(menu->characters.px);
}
