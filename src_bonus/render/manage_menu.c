/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_menu.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrave <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 19:06:46 by ttrave            #+#    #+#             */
/*   Updated: 2024/09/08 19:22:46 by ttrave           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		update_buttons(data);
}
