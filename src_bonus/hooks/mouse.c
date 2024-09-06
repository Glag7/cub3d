/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrave <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 11:58:59 by ttrave            #+#    #+#             */
/*   Updated: 2024/08/27 17:27:35 by ttrave           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"
#include "menu.h"

int	manage_mouse_hook(int button, int x, int y, void *data_ptr)
{
	t_data	*data;

	data = (t_data *)data_ptr;
	if (data->game_state == MENU)
		menu_mouse_hook(button, x, y, data);
	else
		;// ingame mouse events
	return (0);
}
