/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buttons.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrave <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 11:58:59 by ttrave            #+#    #+#             */
/*   Updated: 2024/09/08 18:39:30 by ttrave           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "menu.h"
#include "mlx.h"
#include "utils.h"
#include "popup.h"
#include "data.h"

int	check_button_hitbox(t_button button, size_t x, size_t y)
{
	return (x > button.pos.x - button.dim.x / 2
		&& x < button.pos.x + button.dim.x / 2
		&& y > button.pos.y - button.dim.y / 2
		&& y < button.pos.y + button.dim.y / 2);
}

void	update_buttons(t_data *data)
{
	bool	hovering;
	size_t	i;
	int	x;
	int	y;

	mlx_mouse_get_pos(data->mlx.mlx, data->mlx.win, &x, &y);
	i = 0;
	while (i < 6)
	{
		if (data->menu.buttons[i].window == data->menu.window)
		{
			hovering = check_button_hitbox(data->menu.buttons[i], (size_t)x, (size_t)y);
			if (data->menu.buttons[i].state == IDLE && hovering == 1)
			{
				draw_button(data, data->menu.buttons[i], HOVER);
				data->menu.buttons[i].state = HOVER;
			}
			else if (data->menu.buttons[i].state == HOVER && hovering == 0)
			{
				draw_button(data, data->menu.buttons[i], IDLE);
				data->menu.buttons[i].state = IDLE;
			}
		}
		i++;
	}
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->mlx.img, 0, 0);
}
