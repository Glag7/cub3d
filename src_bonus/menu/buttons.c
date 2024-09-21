/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buttons.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrave <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 11:58:59 by ttrave            #+#    #+#             */
/*   Updated: 2024/09/21 19:07:25 by ttrave           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "menu.h"
#include "mlx.h"
#include "utils.h"
#include "popup.h"
#include "data.h"

bool	check_hitbox(t_ulpoint pos, t_ulpoint dim, size_t x, size_t y)
{
	return (x > pos.x - dim.x / 2 && x < pos.x + dim.x / 2
		&& y > pos.y - dim.y / 2 && y < pos.y + dim.y / 2);
}

static void	update_state(t_data *data, t_button *button, size_t x, size_t y)
{
	bool	hovering;

	hovering = check_hitbox(button->pos, button->dim, x, y);
	if (hovering == 1 && button->state == IDLE)
	{
		button->state = HOVER;
		draw_button(data, *button, HOVER);
	}
	else if (hovering == 0 && button->state == HOVER)
	{
		button->state = IDLE;
		draw_button(data, *button, IDLE);
	}
}

void	update_buttons(t_data *data)
{
	size_t	i;
	int		x;
	int		y;

	mlx_mouse_get_pos(data->mlx.mlx, data->mlx.win, &x, &y);
	i = 0;
	while (i < NB_BUTTONS)
	{
		if (data->menu.buttons[i].window == data->menu.window)
			update_state(data, &data->menu.buttons[i], (size_t)x, (size_t)y);
		i++;
	}
}
