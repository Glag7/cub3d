/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrave <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 11:58:59 by ttrave            #+#    #+#             */
/*   Updated: 2024/09/08 18:42:33 by ttrave           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "menu.h"

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
}
