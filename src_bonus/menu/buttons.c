/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buttons.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrave <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 11:58:59 by ttrave            #+#    #+#             */
/*   Updated: 2024/08/27 17:27:35 by ttrave           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "menu.h"
#include "mlx.h"
#include "utils.h"

static int	check_button_hitbox(t_button button, size_t x, size_t y)
{
	return (x > button.pos.x - button.dim.x / 2
		&& x < button.pos.x + button.dim.x / 2
		&& y > button.pos.y - button.dim.y / 2
		&& y < button.pos.y + button.dim.y / 2);
}

static void	check_hover(t_mlx *mlx, t_set *set, t_button **active_buttons)
{
	bool	hovering;
	size_t	i;
	int	x;
	int	y;

	mlx_mouse_get_pos(mlx->mlx, mlx->win, &x, &y);
	i = 0;
	while (active_buttons[i] != NULL)
	{
		hovering = check_button_hitbox(*active_buttons[i], (size_t)x, (size_t)y);
		if (active_buttons[i]->state == IDLE && hovering == 1)
		{
			draw_button(mlx, set, *active_buttons[i], HOVER);
			active_buttons[i]->state = HOVER;
		}
		else if (active_buttons[i]->state == HOVER && hovering == 0)
		{
			draw_button(mlx, set, *active_buttons[i], IDLE);
			active_buttons[i]->state = IDLE;
		}
		i++;
	}
}

void	update_buttons(t_mlx *mlx, t_menu *menu, t_set *set)
{
	t_button	*active_buttons[3];

	ft_bzero(active_buttons, 3 * sizeof(t_button *));
	if (menu->window == MAIN)
	{
		active_buttons[0] = &menu->buttons[0];// 0 or 1 if game already started
		active_buttons[1] = &menu->buttons[2];
		active_buttons[2] = &menu->buttons[4];
	}
	else if (menu->window == SETTINGS)
	{
		active_buttons[0] = &menu->buttons[3];
		;// more for settings ?
	}
	else
	{
		active_buttons[0] = &menu->buttons[5];
		active_buttons[1] = &menu->buttons[6];
	}
	check_hover(mlx, set, active_buttons);
}
