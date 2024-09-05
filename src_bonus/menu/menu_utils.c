/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrave <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 11:58:59 by ttrave            #+#    #+#             */
/*   Updated: 2024/08/27 17:27:35 by ttrave           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "menu.h"

size_t	part(size_t n, double fraction)
{
	return ((size_t)((double)n / fraction));
}

void	free_menu(t_menu *menu)
{
	free(menu->title.px);
	free(menu->background);
	free(menu->buttons[0].string.px);
	free(menu->buttons[1].string.px);
	free(menu->buttons[2].string.px);
	free(menu->buttons[3].string.px);
	free(menu->buttons[4].string.px);
	free(menu->buttons[5].string.px);
	free(menu->buttons[6].string.px);
}
