/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buttons.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrave <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 11:58:59 by ttrave            #+#    #+#             */
/*   Updated: 2024/09/19 16:38:48 by ttrave           ###   ########.fr       */
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

static bool	update_button_state(t_data *data, t_button *button, size_t x,
	size_t y)
{
	bool	refresh;
	bool	hovering;

	refresh = 0;
	hovering = check_hitbox(button->pos, button->dim, x, y);
	if (button->state == IDLE && hovering == 1)
	{
		draw_button(data, *button, HOVER);
		button->state = HOVER;
		refresh = 1;
	}
	else if (button->state == HOVER && hovering == 0)
	{
		draw_button(data, *button, IDLE);
		button->state = IDLE;
		refresh = 1;
	}
	return (refresh);
}

void	update_buttons(t_data *data)
{
	bool	refresh;
	size_t	i;
	int		x;
	int		y;

	mlx_mouse_get_pos(data->mlx.mlx, data->mlx.win, &x, &y);
	refresh = 0;
	i = 0;
	while (i < NB_BUTTONS)
	{
		if (data->menu.buttons[i].window == data->menu.window)
			refresh |= update_button_state(data,
					&data->menu.buttons[i], (size_t)x, (size_t)y);
		i++;
	}
	if (refresh == 1)
		mlx_put_image_to_window(data->mlx.mlx,
			data->mlx.win, data->mlx.img, 0, 0);
}
