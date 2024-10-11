/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_menu.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrave <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 19:06:46 by ttrave            #+#    #+#             */
/*   Updated: 2024/09/22 15:27:15 by ttrave           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "status.h"
#include "keys.h"
#include "data.h"
#include "render.h"
#include "menu.h"

void	manage_menu(t_data *data)
{
	if (data->menu.first_render == 1)
	{
		data->menu.first_render = 0;
		draw_floor(data);
		raycast(data);
		draw_minimap(data);
		draw_hud(data);
		build_menu(data);
	}
	else
	{
		update_buttons(data);
		if (data->menu.window == WIN_SETTINGS)
		{
			update_sliders(data);
			update_textfields(data);
		}
	}
}

void	manage_menu_hooks(t_data *data)
{
	if ((data->menu.prev_keys & PREV_TAB) == 0 && (data->keys & KEY_TAB) != 0)
	{
		data->menu.prev_keys |= PREV_TAB;
		if ((data->status & MENU) == 0)
			build_menu(data);
		else
			close_menu(data);
	}
	else if ((data->menu.prev_keys & PREV_TAB) == 1
		&& (data->keys & KEY_TAB) == 0)
		data->menu.prev_keys &= ~PREV_TAB;
}
