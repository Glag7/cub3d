/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrave <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 11:58:59 by ttrave            #+#    #+#             */
/*   Updated: 2024/09/19 19:22:02 by ttrave           ###   ########.fr       */
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
	free(menu->title.px);
	free(menu->confirm.px);
	if (menu->first_start == 1)
		free(menu->resume.px);
	free(menu->background);
	free(menu->buttons[BUT_START].string.px);
	free(menu->buttons[BUT_SETTINGS].string.px);
	free(menu->buttons[BUT_BACK].string.px);
	free(menu->buttons[BUT_EXIT].string.px);
	free(menu->buttons[BUT_YES].string.px);
	free(menu->buttons[BUT_NO].string.px);
	free(menu->digits[0].px);
	free(menu->digits[1].px);
	free(menu->digits[2].px);
	free(menu->digits[3].px);
	free(menu->digits[4].px);
	free(menu->digits[5].px);
	free(menu->digits[6].px);
	free(menu->digits[7].px);
	free(menu->digits[8].px);
	free(menu->digits[9].px);
	free(menu->digits[10].px);
	free(menu->digits[11].px);
	free(menu->res.string[0].px);
	free(menu->res.string[1].px);
	free(menu->res.string[2].px);
	free(menu->res.string[3].px);
	free(menu->res.string[4].px);
}
